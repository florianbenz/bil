/**
* \file CfgDecoder.cpp
* \brief Contains definition of CfgDecoder class.
*/

#include <cfgdecode/CfgDecoder.hpp>

using namespace bil;


void CfgDecoder::decode(CfgExtractor& extractor, const DeviceCfgDb& db,
  const Device& device)
{
    // clear out old results
    m_pipRefs.clear();

    // cache pointers to tiles
    const Tiles& tiles = device.tiles();

    // loop over all tile type data bases
    const TileTypeCfgDbs& tileTypeDbs = db.tileTypeDbs();
    size_t tileTypeDbCount = tileTypeDbs.size();
    for (size_t i = 0; i < tileTypeDbCount; ++i)
    {
        // get current data base and do decoding for that tile type
        const TileTypeCfgDb& tileTypeDb = tileTypeDbs[i];
        decodeTileType(extractor, tileTypeDb, tiles);
    }
}


void CfgDecoder::decodeTileType(CfgExtractor& extractor,
  const TileTypeCfgDb& tileTypeDb, const Tiles& tiles)
{
    // get PIP control sets for that tile type
    const PIPControlSets& pipControlSets = tileTypeDb.pipControlSets();

    // loop over all tiles
    size_t tileCount = tiles.size();
    for (size_t i = 0; i < tileCount; ++i)
    {
        // get current tile, check its type, and gets its position
        const Tile& tile = tiles[i];
        if (tile.typeIndex() != tileTypeDb.typeIndex()) continue;
        unsigned tileRow = tile.row();
        unsigned tileColumn = tile.column();

        // get configuration data size of this tile
        size_t dataWordCount = extractor.getDataWordCount(tileRow, tileColumn);
        if (0 == dataWordCount) continue;

        // enlarge buffer to hold this data and copy data into it
        if (m_buffer.size() < dataWordCount) m_buffer.resize(dataWordCount);
        extractor.getDataWords(tileRow, tileColumn, &(m_buffer[0]), dataWordCount);

        // decode PIPs on current tile
        decodeTilePIPs(pipControlSets, i);
    }
}


void CfgDecoder::decodeTilePIPs(const PIPControlSets& pipControlSets,
  size_t tileIndex)
{
    // loop over all control sets
    size_t pipControlSetCount = pipControlSets.size();
    for (size_t i = 0; i < pipControlSetCount; ++i)
    {
        // get current control set and its sub objects
        const PIPControlSet& pipControlSet = pipControlSets[i];
        const BitPositions& bitPositions = pipControlSet.bitPositions();
        const PIPBitValues& pipBitValues = pipControlSet.pipBitValues();

        // get value from configuration data consisting of all designated bits
        boost::uint32_t cfgValue = 0;
        size_t bitPositionCount = bitPositions.size();
        for (size_t j = bitPositionCount; j-- > 0;)
        {
            // get bit position
            size_t bitPosition = bitPositions[j];

            // get bit value on that position
            size_t wordIndex = bitPosition >> 5;
            boost::uint32_t wordBits = m_buffer.at(wordIndex);
            size_t wordBitIndex = bitPosition & 0x1f;
            wordBits = (wordBits >> wordBitIndex) & 1;

            // shift this bit into value
            cfgValue = (cfgValue << 1) | wordBits;
        }

        // a null value always corresponds to no PIPs
        if (0 == cfgValue) continue;

        // search for matches of this value
        size_t pipBitValuesCount = pipBitValues.size();
        for (size_t j = 0; j < pipBitValuesCount; ++j)
        {
            // get values of all PIPs
            const PIPBitValue& pipBitValue = pipBitValues[j];

            // compare them to extracted value
            boost::uint32_t value = pipBitValue.bitValue();
            if (cfgValue < value) break;
            if (cfgValue != value) continue;
            if (0 != (value & PIPBitValue::VALUE_UNUSED)) continue;

            // if they match, add a PIPRef for this found PIP
            size_t count = m_pipRefs.size();
            m_pipRefs.push_back(PIPRef());
            PIPRef& pipRef = m_pipRefs[count];
            // fill it
            pipRef.tileIndex(tileIndex);
            pipRef.pipIndex(pipBitValue.pipIndex());
        }
    }
}


const PIPRefs& CfgDecoder::pipRefs() const
{
    return m_pipRefs;
}