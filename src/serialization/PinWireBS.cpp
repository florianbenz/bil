/**
* \file PinWireBS.cpp
* \brief Contains binary serialization functions for PinWire class.
*/

#include <serialization/PinWireBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/PinWire.hpp>

using namespace bil;


void bil::writeBinary(const PinWire& data, std::ostream& outputStream)
{
    writeBinary(data.m_wireIndex, outputStream);
    writeBinary(data.m_pinIndex, outputStream);
}


void bil::readBinary(PinWire& data, std::istream& inputStream)
{
    readBinary(data.m_wireIndex, inputStream);
    readBinary(data.m_pinIndex, inputStream);
}