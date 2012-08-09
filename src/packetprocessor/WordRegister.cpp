/**
* \file WordRegister.cpp
* \brief Contains definition of WordRegister class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/WordRegister.hpp>

using namespace bil;


WordRegister::WordRegister(RegisterAddress::address_t address, const std::string& name, bool writable, bool readable):
  Register(address, name, writable, readable),
  m_value(0)
{

}


void WordRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    // call inherited
    Register::write(words, wordCount);
    // only one word can be written at a time
    if (1 != wordCount) throw Exception();
    // write word to register
    m_value = *words;
}


void WordRegister::read(boost::uint32_t* words, size_t wordCount) const
{
    // call inherited
    Register::read(words, wordCount);
    // only one word can be read at a time
    if (1 != wordCount) throw Exception();
    // read word from register
    *words = m_value;
}


void WordRegister::value(boost::uint32_t val)
{
    m_value = val;
}


boost::uint32_t WordRegister::value() const
{
    return m_value;
}