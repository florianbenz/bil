/**
* \file PrimitiveSiteType.cpp
* \brief Contains definition of PrimitiveSiteType class.
*/

#include <xdlrc/model/PrimitiveSiteType.hpp>

using namespace bil;


PrimitiveSiteType::PrimitiveSiteType():
  m_pinWires(),
  m_primitiveTypeIndex(0)
{

}


void PrimitiveSiteType::primitiveTypeIndex(unsigned short index)
{
    m_primitiveTypeIndex = index;
}


unsigned short PrimitiveSiteType::primitiveTypeIndex() const
{
    return m_primitiveTypeIndex;
}


PinWires& PrimitiveSiteType::pinWires()
{
    return m_pinWires;
}


const PinWires& PrimitiveSiteType::pinWires() const
{
    return m_pinWires;
}


void PrimitiveSiteType::clear()
{
    m_primitiveTypeIndex = 0;
    m_pinWires.clear();
}