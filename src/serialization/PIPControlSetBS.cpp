/**
* \file PIPControlSetBS.cpp
* \brief Contains binary serialization functions for PIPControlSet class.
*/

#include <serialization/PIPControlSetBS.hpp>
#include <util/BinarySerialization.hpp>
#include <mappingdb/PIPControlSet.hpp>

using namespace bil;


void bil::writeBinary(const PIPControlSet& data, std::ostream& outputStream)
{
    writeBinary(data.m_bitPositions, outputStream);
    writeBinary(data.m_pipBitValues, outputStream);
}


void bil::readBinary(PIPControlSet& data, std::istream& inputStream)
{
    readBinary(data.m_bitPositions, inputStream);
    readBinary(data.m_pipBitValues, inputStream);
}