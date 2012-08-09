/**
* \file PrimitiveTypeBS.cpp
* \brief Contains binary serialization functions for PrimitiveType class.
*/

#include <serialization/PrimitiveTypeBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/PrimitiveType.hpp>

using namespace bil;


void bil::writeBinary(const PrimitiveType& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_pins, outputStream);
    writeBinary(data.m_elements, outputStream);
    writeBinary(data.m_tag, outputStream);
}


void bil::readBinary(PrimitiveType& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_pins, inputStream);
    readBinary(data.m_elements, inputStream);
    readBinary(data.m_tag, inputStream);
}