/**
* \file Wire.cpp
* \brief Contains definition of Wire class.
*/

#include <xdlrc/model/Wire.hpp>

using namespace bil;


Wire::Wire():
  m_name(),
  m_connections()
{

}


std::string& Wire::name()
{
    return m_name;
}


const std::string& Wire::name() const
{
    return m_name;
}


WireConnections& Wire::connections()
{
    return m_connections;
}


const WireConnections& Wire::connections() const
{
    return m_connections;
}


void Wire::clear()
{
    m_name.clear();
    m_connections.clear();
}