/**
* \file PrimitiveSiteBS.cpp
* \brief Contains binary serialization functions for PrimitiveSite class.
*/

#include <serialization/PrimitiveSiteBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/PrimitiveSite.hpp>

using namespace bil;


void bil::writeBinary(const PrimitiveSite& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_bonded, outputStream);
}


void bil::readBinary(PrimitiveSite& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_bonded, inputStream);
}