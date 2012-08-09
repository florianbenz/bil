/**
* \file PIP.cpp
* \brief Contains definition of PIP class.
*/

#include <xdlrc/model/PIP.hpp>

using namespace bil;


PIP::PIP():
  m_startWireIndex(0),
  m_endWireIndex(0),
  m_direction(PIPDirection::MONODI_BUF)
{

}


void PIP::startWireIndex(unsigned short index)
{
    m_startWireIndex = index;
}


unsigned short PIP::startWireIndex() const
{
    return m_startWireIndex;
}


void PIP::endWireIndex(unsigned short index)
{
    m_endWireIndex = index;
}


unsigned short PIP::endWireIndex() const
{
    return m_endWireIndex;
}


void PIP::direction(PIPDirection::direction_t dir)
{
    m_direction = dir;
}


PIPDirection::direction_t PIP::direction() const
{
    return m_direction;
}


void PIP::clear()
{
    m_startWireIndex = 0;
    m_endWireIndex = 0;
    m_direction = PIPDirection::MONODI_BUF;
}