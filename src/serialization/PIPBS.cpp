/**
* \file PIPBS.cpp
* \brief Contains binary serialization functions for PIP class.
*/

#include <serialization/PIPBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/PIP.hpp>

using namespace bil;


void bil::writeBinary(const PIP& data, std::ostream& outputStream)
{
    writeBinary(data.m_startWireIndex, outputStream);
    writeBinary(data.m_endWireIndex, outputStream);
    writeBinary(data.m_direction, outputStream);
}


void bil::readBinary(PIP& data, std::istream& inputStream)
{
    readBinary(data.m_startWireIndex, inputStream);
    readBinary(data.m_endWireIndex, inputStream);
    readBinary(data.m_direction, inputStream);
}