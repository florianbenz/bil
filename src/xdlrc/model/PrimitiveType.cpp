/**
* \file PrimitiveType.cpp
* \brief Contains definition of PrimitiveType class.
*/

#include <xdlrc/model/PrimitiveType.hpp>

using namespace bil;


PrimitiveType::PrimitiveType():
  m_name(),
  m_pins(),
  m_elements(),
  m_tag(0)
{

}


std::string& PrimitiveType::name()
{
    return m_name;
}


const std::string& PrimitiveType::name() const
{
    return m_name;
}


Pins& PrimitiveType::pins()
{
    return m_pins;
}


const Pins& PrimitiveType::pins() const
{
    return m_pins;
}


Elements& PrimitiveType::elements()
{
    return m_elements;
}


const Elements& PrimitiveType::elements() const
{
    return m_elements;
}


void PrimitiveType::tag(size_t t)
{
    m_tag = t;
}


size_t PrimitiveType::tag() const
{
    return m_tag;
}


void PrimitiveType::clear()
{
    m_name.clear();
    m_pins.clear();
    m_elements.clear();
    m_tag = 0;
}