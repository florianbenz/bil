/**
* \file WireConnectionBS.cpp
* \brief Contains binary serialization functions for WireConnection class.
*/

#include <serialization/WireConnectionBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/WireConnection.hpp>

using namespace bil;


void bil::writeBinary(const WireConnection& data, std::ostream& outputStream)
{
    writeBinary(data.m_xOffset, outputStream);
    writeBinary(data.m_yOffset, outputStream);
    writeBinary(data.m_tileTypeIndex, outputStream);
    writeBinary(data.m_wireIndex, outputStream);
}


void bil::readBinary(WireConnection& data, std::istream& inputStream)
{
    readBinary(data.m_xOffset, inputStream);
    readBinary(data.m_yOffset, inputStream);
    readBinary(data.m_tileTypeIndex, inputStream);
    readBinary(data.m_wireIndex, inputStream);
}