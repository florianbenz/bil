/**
* \file Pin.cpp
* \brief Contains definition of Pin class.
*/

#include <xdlrc/model/Pin.hpp>

using namespace bil;


Pin::Pin():
  m_externalName(),
  m_isInput(false)
{

}


std::string& Pin::externalName()
{
    return m_externalName;
}


const std::string& Pin::externalName() const
{
    return m_externalName;
}


void Pin::isInput(bool flag)
{
    m_isInput = flag;
}


bool Pin::isInput() const
{
    return m_isInput;
}


void Pin::clear()
{
    m_externalName.clear();
    m_isInput = false;
}