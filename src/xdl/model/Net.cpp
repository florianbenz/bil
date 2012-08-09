/**
* \file Net.cpp
* \brief Contains definition of Net class.
*/

#include <xdl/model/Net.hpp>

using namespace bil;


Net::Net():
  m_name(),
  m_attributes(),
  m_pinRefs(),
  m_pipRefs(),
  m_type(NetType::WIRE)
{

}


std::string& Net::name()
{
    return m_name;
}


const std::string& Net::name() const
{
    return m_name;
}


void Net::type(NetType::net_t type)
{
    m_type = type;
}


NetType::net_t Net::type() const
{
    return m_type;
}


PinRefs& Net::pinRefs()
{
    return m_pinRefs;
}


const PinRefs& Net::pinRefs() const
{
    return m_pinRefs;
}


PIPRefs& Net::pipRefs()
{
    return m_pipRefs;
}


const PIPRefs& Net::pipRefs() const
{
    return m_pipRefs;
}


std::string& Net::attributes()
{
    return m_attributes;
}


const std::string& Net::attributes() const
{
    return m_attributes;
}


void Net::clear()
{
    m_name.clear();
    m_attributes.clear();
    m_type = NetType::WIRE;
    m_pinRefs.clear();
    m_pipRefs.clear();
}