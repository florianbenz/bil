/**
* \file Correlator.cpp
* \brief Contains definition of Correlator class.
*/

#include <algorithm>
#include <utility>
#include <correlation/Correlator.hpp>
#include <mappingdb/DeviceCfgDbFiller.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void Correlator::run(DeviceCfgDb& db, const Design& design,
  const Device& device, CfgExtractor& cfgExtractor)
{   
    // init data base
    {
        DeviceCfgDbFiller dbFiller;
        dbFiller.initDeviceDb(db, device);
    }
    // get tile type database entries
    TileTypeCfgDbs& tileTypeDbs = db.tileTypeDbs();

    // loop over all entries
    size_t tileTypeDBCount = tileTypeDbs.size();
    for (size_t i = 0; i < tileTypeDBCount; ++i)
    {
        // get tile type database
        TileTypeCfgDb& tileTypeDb = tileTypeDbs[i];

        // Gather correlation units for that tile type. If there are no units
        // available, skip this type and continue with next.
        gatherCorrelationUnits(tileTypeDb.typeIndex(), design, device, cfgExtractor);
        if (m_tileUnits.size() == 0) continue;

        // Build PIP control set map. It will map the index of a PIP to its
        // corresponding control set.
        buildPIPControlSetMap(tileTypeDb.pipControlSets());

        // Init PIP result states. Use first tile correlation unit for
        // determining the pip and configuration bit size (all units are
        // required to have the same sizes).
        const CorrelationUnit& firstUnit = m_tileUnits[0];
        initPIPStates(firstUnit.pipBitSize(), firstUnit.cfgBitSize());

        // Do PIP isolation. Walks over the correlation units extracted from
        // XDL, and writes the results to the PIP result states.
        isolatePIPs(m_tileUnits);

        // Write the PIP result states into the data base.
        writePIPsToDb(tileTypeDb);
    }
}


void Correlator::gatherCorrelationUnits(size_t tileTypeIndex,
  const Design& design, const Device& device, CfgExtractor& cfgExtractor)
{
    // gather correlation units from XDL
    m_tileUnits.clear();
    m_tileIndices.clear();
    XDLExtractor xdlExtractor(design, device);
    xdlExtractor.getTileTypeUnits(m_tileUnits, m_tileIndices, tileTypeIndex);

    // loop over gathered units
    size_t unitIndex = 0;
    size_t tileIndicesIndex = 0;
    const Tiles& tiles = device.tiles();
    while (unitIndex < (m_tileUnits.size()))
    {
        // get current unit
        CorrelationUnit& unit = m_tileUnits[unitIndex];
        // get corresponding tile and its position
        size_t tileIndex = m_tileIndices[tileIndicesIndex++];
        const Tile& tile = tiles.at(tileIndex);
        unsigned tileRow = tile.row();
        unsigned tileColumn = tile.column();

        // get configuration data size of this tile
        size_t dataWordCount = cfgExtractor.getDataWordCount(tileRow, tileColumn);
        // if there is no data for it, delete current unit (this happens when
        // the configuration extractor does not know where to find the data and
        // returns zero)
        if (0 != dataWordCount) ++unitIndex;
        else
        {
            m_tileUnits.erase(m_tileUnits.begin() + unitIndex);
            continue;
        }

        // enlarge buffer to hold this data
        if (m_buffer.size() < dataWordCount) m_buffer.resize(dataWordCount);
        // copy configuration data into buffer
        cfgExtractor.getDataWords(tileRow, tileColumn, &(m_buffer[0]), dataWordCount);
        // set unit's configuration bits accordingly
        unit.appendCfgBits(&(m_buffer[0]), dataWordCount);
    }

    // clear temporary data
    m_buffer.clear();
    m_tileIndices.clear();
}


void Correlator::buildPIPControlSetMap(const PIPControlSets& pipControlSets)
{
    // clear old data
    m_pipControlSetMap.clear();

    // loop over all given PIP control sets
    size_t controlSetCount = pipControlSets.size();
    for (size_t i = 0; i < controlSetCount; ++i)
    {
        // get current PIP control set
        const PIPControlSet& controlSet = pipControlSets[i];

        // loop over all its PIPs and their values
        const PIPBitValues& pipBitValues = controlSet.pipBitValues();
        size_t pipCount = pipBitValues.size();
        for (size_t j = 0; j < pipCount; ++j)
        {
            // get current PIP index
            size_t pipIndex = (pipBitValues[j]).pipIndex();

            // check if every PIP index is used only one time
            pipControlSetMap_t::iterator lb = m_pipControlSetMap.lower_bound(pipIndex);
            if ((m_pipControlSetMap.end() != lb) && (pipIndex == lb->first))
                throw Exception();
            // insert PIP index with its corresponding control set into map
            m_pipControlSetMap.insert(lb, std::make_pair(pipIndex, &controlSet));
        }
    }
}


void Correlator::initPIPStates(size_t pipCount, size_t cfgBitCount)
{
    // create as many PIP states as we have got PIPs and init them
    m_pipStates.resize(pipCount);
    for (size_t i = 0; i < pipCount; ++i)
    {
        CorrelationUnit& pipState = m_pipStates[i];
        pipState.pipBitSize(pipCount);
        pipState.setPIPBits();
        pipState.cfgBitSize(cfgBitCount);
        pipState.setCfgBits();
    }
}


void Correlator::isolatePIPs(CorrelationUnits& correlationUnits)
{
    // loop over all PIPs
    size_t pipCount = m_pipStates.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get PIP state for current PIP
        CorrelationUnit& state = m_pipStates[i];

        // get control set the current PIP is in
        pipControlSetMap_t::const_iterator it = m_pipControlSetMap.find(i);
        if (m_pipControlSetMap.end() == it) throw Exception();
        const PIPControlSet& controlSet = *(it->second);
        // get the control set's PIPs
        const PIPBitValues& pipBitValues = controlSet.pipBitValues();
        size_t pipCountCs = pipBitValues.size();

        // loop over all given correlation units
        size_t unitCount = correlationUnits.size();
        for (size_t j = 0; j < unitCount; ++j)
        {
            // Get current unit and intersect state with it if compatible. An
            // unit is compatible, if the current PIP is active in it, or if the
            // current PIP and all other PIPs of its control set are inactive.
            const CorrelationUnit& unit = correlationUnits[j];
            if (unit.testPIPBit(i)) state.intersect(unit);
            else
            {
                // check if all PIPs in control set are also inactive
                bool compatible = true;
                for (size_t k = 0; k < pipCountCs; ++k)
                    if (unit.testPIPBit((pipBitValues[k]).pipIndex()))
                    {
                        compatible = false;
                        break;
                    }
                // if compatible do intersection with the inverse
                if (compatible) state.intersectInverted(unit);
            }
        }
    }
}


void Correlator::writePIPsToDb(TileTypeCfgDb& tileTypeDb)
{
    // loop over all control sets of this type
    PIPControlSets& controlSets = tileTypeDb.pipControlSets();
    size_t controlSetCount = controlSets.size();
    for (size_t i = 0; i < controlSetCount; ++i)
    {
        // get current control set and its sub objects
        PIPControlSet& controlSet = controlSets[i];
        BitPositions& bitPositions = controlSet.bitPositions();
        PIPBitValues& pipBitValues = controlSet.pipBitValues();

        // read out the correlation results into them
        getCfgBitPositions(bitPositions, pipBitValues);
        getCfgBitValues(pipBitValues, bitPositions);

        // sort the retrieved values, eases later usage
        PIPBitValues::iterator itBegin = pipBitValues.begin();
        PIPBitValues::iterator itEnd = pipBitValues.end();
        std::sort(itBegin, itEnd);
    }
}


void Correlator::getCfgBitPositions(BitPositions &bitPositions,
  const PIPBitValues& pipBitValues) const
{
    // clear old data
    bitPositions.clear();

    // loop over all given PIPs
    size_t pipCount = pipBitValues.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get index of current PIP and its correlation state
        size_t pipIndex = (pipBitValues[i]).pipIndex();
        const CorrelationUnit& pipState = m_pipStates.at(pipIndex);

        // take only isolated PIPs in account
        if (!pipState.isIsolated()) continue;

        // get positions of all set bits in state and insert it ordered
        size_t bitIndex = pipState.firstCfgBit();
        while (CorrelationUnit::INVALID_BIT_INDEX != bitIndex)
        {
            // get insertion point
            BitPositions::iterator itBegin = bitPositions.begin();
            BitPositions::iterator itEnd = bitPositions.end();
            BitPositions::iterator it = std::lower_bound(itBegin, itEnd, bitIndex);
            // insert it, if its not in list
            if ((it == itEnd) || (*it != bitIndex))
                bitPositions.insert(it, bitIndex);
            // get next set bit
            bitIndex = pipState.nextCfgBit(bitIndex);
        }
    }
}


void Correlator::getCfgBitValues(PIPBitValues& pipBitValues,
  const BitPositions &bitPositions) const
{
    // Get number of bits/bit positions and check, that it fits into the bit
    // value entries (highest bit is used for encoding if PIP is isolated).
    size_t bitPositionCount = bitPositions.size();
    if (PIPBitValue::MAX_BIT_COUNT <= bitPositionCount) throw Exception();

    // loop over all given PIPs and their cfg values
    size_t pipCount = pipBitValues.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get value object of current PIP
        PIPBitValue& pipBitValue = pipBitValues[i];

        // get corresponding correlation result
        size_t pipIndex = pipBitValue.pipIndex();
        const CorrelationUnit& pipState = m_pipStates.at(pipIndex);

        // loop over given bit positions and read out these result bits
        boost::uint32_t value = 0;
        for (size_t j = bitPositionCount; j-- > 0;)
        {
            value <<= 1;
            size_t bitPosition = bitPositions[j];
            if (pipState.testCfgBit(bitPosition)) value |= 1;
        }

        // flag PIPs that are not isolated
        if (!pipState.isIsolated()) value |= PIPBitValue::VALUE_UNUSED;

        // write new value
        pipBitValue.bitValue(value);
    }
}