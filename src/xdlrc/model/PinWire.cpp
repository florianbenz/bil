/**
* \file PinWire.cpp
* \brief Contains definition of PinWire class.
*/

#include <xdlrc/model/PinWire.hpp>

using namespace bil;


PinWire::PinWire():
  m_wireIndex(0),
  m_pinIndex(0)
{

}


void PinWire::wireIndex(unsigned short index)
{
    m_wireIndex = index;
}


unsigned short PinWire::wireIndex() const
{
    return m_wireIndex;
}


void PinWire::pinIndex(unsigned short index)
{
    m_pinIndex = index;
}


unsigned short PinWire::pinIndex() const
{
    return m_pinIndex;
}


void PinWire::clear()
{
    m_wireIndex = 0;
    m_pinIndex = 0;
}