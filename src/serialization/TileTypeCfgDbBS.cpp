/**
* \file TileTypeCfgDbBS.cpp
* \brief Contains binary serialization functions for TileTypeCfgDb class.
*/

#include <serialization/TileTypeCfgDbBS.hpp>
#include <util/BinarySerialization.hpp>
#include <mappingdb/TileTypeCfgDb.hpp>

using namespace bil;


void bil::writeBinary(const TileTypeCfgDb& data, std::ostream& outputStream)
{
    writeBinary(data.m_tileTypeIndex, outputStream);
    writeBinary(data.m_pipControlSets, outputStream);
}


void bil::readBinary(TileTypeCfgDb& data, std::istream& inputStream)
{
    readBinary(data.m_tileTypeIndex, inputStream);
    readBinary(data.m_pipControlSets, inputStream);
}