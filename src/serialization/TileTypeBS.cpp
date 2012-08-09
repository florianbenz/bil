/**
* \file TileTypeBS.cpp
* \brief Contains binary serialization functions for TileType class.
*/

#include <serialization/TileTypeBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/TileType.hpp>

using namespace bil;


void bil::writeBinary(const TileType& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_siteTypes, outputStream);
    writeBinary(data.m_wires, outputStream);
    writeBinary(data.m_pips, outputStream);
    writeBinary(data.m_tag, outputStream);
}


void bil::readBinary(TileType& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_siteTypes, inputStream);
    readBinary(data.m_wires, inputStream);
    readBinary(data.m_pips, inputStream);
    readBinary(data.m_tag, inputStream);
}