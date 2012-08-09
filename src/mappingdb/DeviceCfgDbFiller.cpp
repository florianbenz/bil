/**
* \file DeviceCfgDbFiller.cpp
* \brief Contains definition of DeviceCfgDbFiller class.
*/

#include <utility>
#include <mappingdb/DeviceCfgDbFiller.hpp>
#include <xdlrc/model/Device.hpp>

using namespace bil;


void DeviceCfgDbFiller::initDeviceDb(DeviceCfgDb& deviceDb,
  const Device& device)
{
    // clear device database
    deviceDb.clear();

    // get tile types from device
    const TileTypes& tileTypes = device.tileTypes();
    size_t tileTypeCount = tileTypes.size();

    // create one tile type database for every tile type
    TileTypeCfgDbs& tileTypeDbs = deviceDb.tileTypeDbs();
    tileTypeDbs.resize(tileTypeCount);

    // loop over all tile type databases and fill them
    for (size_t i = 0; i < tileTypeCount; ++i)
        initTileTypeDb(tileTypeDbs[i], tileTypes[i], i);
}


void DeviceCfgDbFiller::initTileTypeDb(TileTypeCfgDb& tileTypeDb,
  const TileType& tileType, size_t tileTypeIndex)
{
    // clear tile type database
    tileTypeDb.clear();

    // set its tile type
    tileTypeDb.typeIndex(tileTypeIndex);

    // clear map and copy pointer to control sets
    m_pipControlSetMap.clear();
    m_pipControlSets = &(tileTypeDb.pipControlSets());

    // loop over all PIPs and sort them into control sets
    const PIPs& pips = tileType.pips();
    size_t pipCount = pips.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get current PIP and create/find its control set
        const PIP& pip = pips[i];
        PIPControlSet& controlSet = addPIPControlSet(pip.endWireIndex());

        // add new PIPBitValue entry to control set
        PIPBitValues& pipBitValues = controlSet.pipBitValues();
        size_t count = pipBitValues.size();
        pipBitValues.push_back(PIPBitValue());
        PIPBitValue& pipBitValue = pipBitValues[count];

        // set its properties
        pipBitValue.pipIndex(i);
        pipBitValue.bitValue(PIPBitValue::VALUE_UNUSED);
    }

    // empty map
    m_pipControlSetMap.clear();

    // collapse all control sets with only one PIP into one
    // collapsePIPControlSets(); // Not sure if that's a good idea

    // empty control sets pointer again
    m_pipControlSets = 0;
}


PIPControlSet& DeviceCfgDbFiller::addPIPControlSet(size_t endWireIndex)
{
    // check, if control set for given end wire exists: if not, create it.
    pipControlSetMap_t::iterator lb = m_pipControlSetMap.lower_bound(endWireIndex);
    if ((m_pipControlSetMap.end() == lb) || (endWireIndex != lb->first))
    {
        // create a new control set
        size_t count = m_pipControlSets->size();
        m_pipControlSets->push_back(PIPControlSet());
        PIPControlSet& controlSet = (*m_pipControlSets)[count];

        // create a new entry in map
        pipControlSetMap_t::iterator it =
            m_pipControlSetMap.insert(lb, std::make_pair(endWireIndex, count));

        // return it
        return controlSet;
    }
    else
    {
        // fetch control set index from map
        size_t controlSetIndex = lb->second;
        return (*m_pipControlSets)[controlSetIndex];
    }
}


void DeviceCfgDbFiller::collapsePIPControlSets()
{
    // loop over all control sets of a tile type and find first control set,
    // that has only one PIP
    size_t pipControlSetCount = m_pipControlSets->size();
    size_t pipControlSetIndex = pipControlSetCount;
    for (size_t i = 0; i < pipControlSetCount; ++i)
    {
        const PIPControlSet& pipControlSet = (*m_pipControlSets)[i];
        const PIPBitValues& pipBitValues = pipControlSet.pipBitValues();
        if (pipBitValues.size() <= 1)
        {
            pipControlSetIndex = i;
            break;
        }
    }

    // If not found, return. Else use this to collapse further single PIP
    // control sets into it.
    if (pipControlSetIndex >= pipControlSetCount) return;
    PIPControlSet& dstPIPControlSet = (*m_pipControlSets)[pipControlSetIndex];
    PIPBitValues& dstPIPBitValues = dstPIPControlSet.pipBitValues();

    // loop over control sets again, but start behind found one
    size_t i = pipControlSetIndex + 1;
    while (i < m_pipControlSets->size())
    {
        // get current control set and its PIPs
        const PIPControlSet& pipControlSet = (*m_pipControlSets)[i];
        const PIPBitValues& pipBitValues = pipControlSet.pipBitValues();
        size_t pipCount = pipBitValues.size();
        // if it has less than 2 PIPs, copy it to first one, and delete it
        if (1 >= pipCount)
        {
            if (1 == pipCount) dstPIPBitValues.push_back(pipBitValues[0]);
            m_pipControlSets->erase(m_pipControlSets->begin() + i);
        }
        else ++i;
    }
}