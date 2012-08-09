/**
* \file Register.cpp
* \brief Contains definition of Register class.
*/

#include <packetprocessor/Register.hpp>
#include <exception/Exception.hpp>

using namespace bil;


Register::Register(RegisterAddress::address_t address, const std::string& name, bool writable, bool readable):
  m_name(name),  
  m_address(address),
  m_writable(writable),
  m_readable(readable)
{

}


Register::~Register()
{

}


RegisterAddress::address_t Register::address() const
{
    return m_address;
}


const std::string& Register::name() const
{
    return m_name;
}


bool Register::writable() const
{
    return m_writable;
}


bool Register::readable() const
{
    return m_readable;
}


void Register::write(const boost::uint32_t*, size_t)
{
    if (!m_writable) throw Exception();
}


void Register::read(boost::uint32_t*, size_t) const
{
    if (!m_readable) throw Exception();
}