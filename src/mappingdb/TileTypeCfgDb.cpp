/**
* \file TileTypeCfgDb.cpp
* \brief Contains definition of TileTypeCfgDb class.
*/

#include <mappingdb/TileTypeCfgDb.hpp>

using namespace bil;


TileTypeCfgDb::TileTypeCfgDb():
  m_pipControlSets(),
  m_tileTypeIndex(0)
{

}


void TileTypeCfgDb::typeIndex(size_t index)
{
    m_tileTypeIndex = index;
}


size_t TileTypeCfgDb::typeIndex() const
{
    return m_tileTypeIndex;
}


PIPControlSets& TileTypeCfgDb::pipControlSets()
{
    return m_pipControlSets;
}


const PIPControlSets& TileTypeCfgDb::pipControlSets() const
{
    return m_pipControlSets;
}


void TileTypeCfgDb::clear()
{
    m_tileTypeIndex = 0;
    m_pipControlSets.clear();
}