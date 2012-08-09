/**
* \file WireBS.cpp
* \brief Contains binary serialization functions for Wire class.
*/

#include <serialization/WireBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/Wire.hpp>

using namespace bil;


void bil::writeBinary(const Wire& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_connections, outputStream);
}


void bil::readBinary(Wire& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_connections, inputStream);
}