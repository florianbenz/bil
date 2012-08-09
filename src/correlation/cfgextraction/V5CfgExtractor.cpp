/**
* \file V5CfgExtractor.cpp
* \brief Contains definition of V5CfgExtractor class.
*/

#include <correlation/cfgextraction/V5CfgExtractor.hpp>
#include <correlation/cfgextraction/V5CfgTileMap.hpp>

using namespace bil;


V5CfgExtractor::V5CfgExtractor(const V5Configuration& configuration,
  const V5CfgTileMap& cfgTileMap):
  m_configuration(&configuration),
  m_cfgTileMap(&cfgTileMap)
{

}


size_t V5CfgExtractor::getDataWordCount(unsigned row, unsigned column) const
{
    const V5CfgTileMapEntry& entry = m_cfgTileMap->entries(row, column);
    return getCfgDataWordCount(entry);
}


size_t V5CfgExtractor::getDataWords(unsigned row, unsigned column,
  boost::uint32_t* data, size_t dataWordCount) const
{
    const V5CfgTileMapEntry& entry = m_cfgTileMap->entries(row, column);
    return getCfgData(data, dataWordCount, *m_configuration, entry);
}