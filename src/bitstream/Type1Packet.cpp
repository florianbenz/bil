/**
* \file Type1Packet.cpp
* \brief Contains definition of Type1Packet class.
*/

#include <bitstream/PacketVisitor.hpp>
#include <bitstream/Type1Packet.hpp>

using namespace bil;


Type1Packet::Type1Packet():
  m_registerAddress()
{

}


Type1Packet* Type1Packet::clone() const
{
    return new Type1Packet(*this);
}


void Type1Packet::accept(PacketVisitor& visitor) const
{
    visitor.visit(*this);
}


void Type1Packet::registerAddress(RegisterAddress::address_t address)
{
    m_registerAddress = address;
}


RegisterAddress::address_t Type1Packet::registerAddress() const
{
    return m_registerAddress;
}


void Type1Packet::clear()
{
    Type2Packet::clear();
    m_registerAddress = 0;
}