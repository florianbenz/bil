/**
* \file ElementBS.cpp
* \brief Contains binary serialization functions for Element class.
*/

#include <serialization/ElementBS.hpp>
#include <util/BinarySerialization.hpp>
#include <xdlrc/model/Element.hpp>

using namespace bil;


void bil::writeBinary(const Element& data, std::ostream& outputStream)
{
    writeBinary(data.m_name, outputStream);
    writeBinary(data.m_options, outputStream);
}


void bil::readBinary(Element& data, std::istream& inputStream)
{
    readBinary(data.m_name, inputStream);
    readBinary(data.m_options, inputStream);
}