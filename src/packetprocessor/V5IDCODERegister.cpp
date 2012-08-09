/**
* \file V5IDCODERegister.cpp
* \brief Contains definition of V5IDCODERegister class.
*/

#include <configuration/V5AddressLayoutRegistry.hpp>
#include <exception/Exception.hpp>
#include <packetprocessor/V5FDRIRegister.hpp>
#include <packetprocessor/V5IDCODERegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5IDCODERegister::V5IDCODERegister(V5FDRIRegister& fdriReg, const V5AddressLayoutRegistry& registry):
  Register(V5RegisterAddress::IDCODE, V5RegisterAddress::IDCODE_STRING, true, true),
  m_idCode(),
  m_fdriRegister(fdriReg),
  m_addressLayoutRegistry(registry)
{

}


void V5IDCODERegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // set command and execute
    idCode(*words);
}


void V5IDCODERegister::read(boost::uint32_t* words, size_t wordCount) const
{
    Register::read(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // return current ID code
    *words = m_idCode;
}


void V5IDCODERegister::idCode(DeviceID::ID_t id)
{
    // lookup address layout for that id
    const V5AddressLayout* layout = m_addressLayoutRegistry.lookup(id);
    if (0 == layout) throw Exception();

    // copy address layout to FDRI
    V5Configuration& configuration = m_fdriRegister.configuration();
    configuration.addressLayout(*layout);

    // store new id code
    m_idCode = id;
}


DeviceID::ID_t V5IDCODERegister::idCode() const
{
    return m_idCode;
}


V5FDRIRegister& V5IDCODERegister::fdriRegister() const
{
    return m_fdriRegister;
}


const V5AddressLayoutRegistry& V5IDCODERegister::layoutRegistry() const
{
    return m_addressLayoutRegistry;
}