/**
* \file PIPBitValueBS.cpp
* \brief Contains binary serialization functions for PIPBitValue class.
*/

#include <serialization/PIPBitValueBS.hpp>
#include <util/BinarySerialization.hpp>
#include <mappingdb/PIPBitValue.hpp>

using namespace bil;


void bil::writeBinary(const PIPBitValue& data, std::ostream& outputStream)
{
    writeBinary(data.m_pipIndex, outputStream);
    writeBinary(data.m_bitValue, outputStream);
}


void bil::readBinary(PIPBitValue& data, std::istream& inputStream)
{
    readBinary(data.m_pipIndex, inputStream);
    readBinary(data.m_bitValue, inputStream);
}