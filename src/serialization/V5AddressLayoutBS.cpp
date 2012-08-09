/**
* \file V5AddressLayoutBS.cpp
* \brief Contains binary serialization functions for V5AddressLayout class.
*/

#include <serialization/V5AddressLayoutBS.hpp>
#include <util/BinarySerialization.hpp>
#include <configuration/V5AddressLayout.hpp>

using namespace bil;


void bil::writeBinary(const V5AddressLayout& data, std::ostream& outputStream)
{
    writeBinary(data.m_columns, outputStream);
    writeBinary(data.m_upperRowCount, outputStream);
    writeBinary(data.m_lowerRowCount, outputStream);
}


void bil::readBinary(V5AddressLayout& data, std::istream& inputStream)
{
    readBinary(data.m_columns, inputStream);
    readBinary(data.m_upperRowCount, inputStream);
    readBinary(data.m_lowerRowCount, inputStream);
    data.m_bramCount = data.countBRAMs(data.m_columns);
}