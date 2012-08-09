/**
* \file DeviceBS.cpp
* \brief Contains binary serialization functions for Device class.
*/

#include <serialization/DeviceBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/Device.hpp>

using namespace bil;


void bil::writeBinary(const Device& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_tiles, outputStream);
    writeBinary(data.m_tileTypes, outputStream);
    writeBinary(data.m_primitiveTypes, outputStream);
}


void bil::readBinary(Device& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_tiles, inputStream);
    readBinary(data.m_tileTypes, inputStream);
    readBinary(data.m_primitiveTypes, inputStream);
}