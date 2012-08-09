/**
* \file RegisterLookup.cpp
* \brief Contains definition of RegisterLookup class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/Register.hpp>
#include <packetprocessor/RegisterLookup.hpp>

using namespace bil;


RegisterLookup::RegisterLookup(RegisterAddress::address_t highestAddress):
  m_registers(highestAddress + 1, 0)
{

}


void RegisterLookup::add(Register& reg)
{
    // check if register address fits in lookup table and if slot is free
    if (reg.address() >= m_registers.size()) throw Exception();
    if (0 != m_registers[reg.address()]) throw Exception();

    // insert register reference into lookup table at its address
    m_registers[reg.address()] = &reg;
}


bool RegisterLookup::remove(RegisterAddress::address_t registerAddress)
{
    // if address can not be deleted (because of address out of range or there
    // is no register tied to this address), return false
    if (m_registers.size() <= registerAddress) return false;
    if (0 == m_registers[registerAddress]) return false;

    // delete address
    m_registers[registerAddress] = 0;
    return true;
}


Register* RegisterLookup::lookup(RegisterAddress::address_t registerAddress) const
{
    // check if address is in lookup table, if not, return 0
    if (m_registers.size() <= registerAddress) return 0;
    // do lookup
    return m_registers[registerAddress];
}