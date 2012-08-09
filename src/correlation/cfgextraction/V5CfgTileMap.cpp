/**
* \file V5CfgTileMap.cpp
* \brief Contains definition of V5CfgTileMap class.
*/

#include <correlation/cfgextraction/V5CfgTileMap.hpp>
#include <exception/Exception.hpp>

using namespace bil;


V5CfgTileMap::V5CfgTileMap():
  m_rowCount(0),
  m_columnCount(0),
  m_entries()
{

}


unsigned V5CfgTileMap::rowCount() const
{
    return m_rowCount;
}


unsigned V5CfgTileMap::columnCount() const
{
    return m_columnCount;
}


V5CfgTileMapEntry& V5CfgTileMap::entries(unsigned row, unsigned column)
{
    if (row >= m_rowCount) throw Exception();
    if (column >= m_columnCount) throw Exception();
    return m_entries[(row * m_columnCount) + column];
}


const V5CfgTileMapEntry& V5CfgTileMap::entries(unsigned row, unsigned column) const
{
    if (row >= m_rowCount) throw Exception();
    if (column >= m_columnCount) throw Exception();
    return m_entries[(row * m_columnCount) + column];
}


void V5CfgTileMap::resize(unsigned rowCount, unsigned columnCount)
{
    // resize entries
    m_entries.resize(rowCount * columnCount);
    m_rowCount = rowCount;
    m_columnCount = columnCount;
    // clear out entries
    size_t entryCount = m_entries.size();
    for (size_t i = 0; i < entryCount; ++i)
        (m_entries[i]).clear();
}


void V5CfgTileMap::clear()
{
    m_rowCount = 0;
    m_columnCount = 0;
    m_entries.clear();
}