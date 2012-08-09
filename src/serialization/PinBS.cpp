/**
* \file PinBS.cpp
* \brief Contains binary serialization functions for Pin class.
*/

#include <serialization/PinBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/Pin.hpp>

using namespace bil;


void bil::writeBinary(const Pin& data, std::ostream& outputStream)
{
    writeBinary(data.m_externalName, outputStream);
    writeBinary(data.m_isInput, outputStream);
}


void bil::readBinary(Pin& data, std::istream& inputStream)
{
    readBinary(data.m_externalName, inputStream);
    readBinary(data.m_isInput, inputStream);
}