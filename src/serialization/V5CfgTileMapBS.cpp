/**
* \file V5CfgTileMapBS.cpp
* \brief Contains binary serialization functions for V5CfgTileMap class.
*/

#include <serialization/V5CfgTileMapBS.hpp>
#include <util/BinarySerialization.hpp>
#include <correlation/cfgextraction/V5CfgTileMap.hpp>

using namespace bil;


void bil::writeBinary(const V5CfgTileMap& data, std::ostream& outputStream)
{
    writeBinary(data.m_rowCount, outputStream);
    writeBinary(data.m_columnCount, outputStream);
    writeBinary(data.m_entries, outputStream);
}


void bil::readBinary(V5CfgTileMap& data, std::istream& inputStream)
{
    readBinary(data.m_rowCount, inputStream);
    readBinary(data.m_columnCount, inputStream);
    readBinary(data.m_entries, inputStream);
}