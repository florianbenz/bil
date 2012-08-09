/**
* \file Design.cpp
* \brief Contains definition of Design class.
*/

#include <xdl/model/Design.hpp>

using namespace bil;


Design::Design():
  m_name(),
  m_deviceName(),
  m_ncdVersion(),
  m_attributes(),
  m_instances(),
  m_nets()
{

}


std::string& Design::name()
{
    return m_name;
}


const std::string& Design::name() const
{
    return m_name;
}


std::string& Design::deviceName()
{
    return m_deviceName;
}


const std::string& Design::deviceName() const
{
    return m_deviceName;
}


std::string& Design::ncdVersion()
{
    return m_ncdVersion;
}


const std::string& Design::ncdVersion() const
{
    return m_ncdVersion;
}


std::string& Design::attributes()
{
    return m_attributes;
}


const std::string& Design::attributes() const
{
    return m_attributes;
}


Instances& Design::instances()
{
    return m_instances;
}


const Instances& Design::instances() const
{
    return m_instances;
}


Nets& Design::nets()
{
    return m_nets;
}


const Nets& Design::nets() const
{
    return m_nets;
}


void Design::clear()
{
    m_name.clear();
    m_deviceName.clear();
    m_ncdVersion.clear();
    m_attributes.clear();
    m_instances.clear();
    m_nets.clear();
}