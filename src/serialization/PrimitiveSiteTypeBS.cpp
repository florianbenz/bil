/**
* \file PrimitiveSiteTypeBS.cpp
* \brief Contains binary serialization functions for PrimitiveSiteType class.
*/

#include <serialization/PrimitiveSiteTypeBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/PrimitiveSiteType.hpp>

using namespace bil;


void bil::writeBinary(const PrimitiveSiteType& data, std::ostream& outputStream)
{
    writeBinary(data.m_primitiveTypeIndex, outputStream);
    writeBinary(data.m_pinWires, outputStream);
}


void bil::readBinary(PrimitiveSiteType& data, std::istream& inputStream)
{
    readBinary(data.m_primitiveTypeIndex, inputStream);
    readBinary(data.m_pinWires, inputStream);
}