/**
* \file DeviceCfgDb.cpp
* \brief Contains definition of DeviceCfgDb class.
*/

#include <mappingdb/DeviceCfgDb.hpp>

using namespace bil;


DeviceCfgDb::DeviceCfgDb():
  m_tileTypeDbs()
{

}


TileTypeCfgDbs& DeviceCfgDb::tileTypeDbs()
{
    return m_tileTypeDbs;
}


const TileTypeCfgDbs& DeviceCfgDb::tileTypeDbs() const
{
    return m_tileTypeDbs;
}


void DeviceCfgDb::clear()
{
    m_tileTypeDbs.clear();
}