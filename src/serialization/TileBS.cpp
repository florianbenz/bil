/**
* \file TileBS.cpp
* \brief Contains binary serialization functions for Tile class.
*/

#include <serialization/TileBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/Tile.hpp>

using namespace bil;


void bil::writeBinary(const Tile& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_primitiveSites, outputStream);
    writeBinary(data.m_row, outputStream);
    writeBinary(data.m_column, outputStream);
    writeBinary(data.m_siteX, outputStream);
    writeBinary(data.m_siteY, outputStream);
    writeBinary(data.m_typeIndex, outputStream);
}


void bil::readBinary(Tile& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_primitiveSites, inputStream);
    readBinary(data.m_row, inputStream);
    readBinary(data.m_column, inputStream);
    readBinary(data.m_siteX, inputStream);
    readBinary(data.m_siteY, inputStream);
    readBinary(data.m_typeIndex, inputStream);
}