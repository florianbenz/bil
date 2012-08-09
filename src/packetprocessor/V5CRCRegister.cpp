/**
* \file V5CRCRegister.cpp
* \brief Contains definition of V5CRCRegister class.
*/

#include <exception/Exception.hpp>
#include <util/CRC32.hpp>
#include <packetprocessor/V5CRCRegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5CRCRegister::V5CRCRegister():
  Register(V5RegisterAddress::CRC, V5RegisterAddress::CRC_STRING, true, true)
{
    reset();
}


void V5CRCRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // do CRC check (input data can be ignored, since CRC value is already
    // updated using them)
    check();
}


void V5CRCRegister::read(boost::uint32_t* words, size_t wordCount) const
{
    Register::read(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // return current CRC value
    *words = m_crcValue;
}


boost::uint32_t V5CRCRegister::crcValue() const
{
    return m_crcValue;
}


void V5CRCRegister::reset()
{
    m_crcValue = 0;
}


void V5CRCRegister::update(const boost::uint32_t* words, size_t wordCount, RegisterAddress::address_t registerAddress)
{
    // calculate CRC value over all data words
    for (size_t i = 0; i < wordCount; ++i)
    {
        // each word's CRC value is calculated from its four bytes
        boost::uint32_t data = *words++;
        m_crcValue = calc8BitCRC32(m_crcValue, static_cast<boost::uint8_t>(data));
        m_crcValue = calc8BitCRC32(m_crcValue, static_cast<boost::uint8_t>(data >> 8));
        m_crcValue = calc8BitCRC32(m_crcValue, static_cast<boost::uint8_t>(data >> 16));
        m_crcValue = calc8BitCRC32(m_crcValue, static_cast<boost::uint8_t>(data >> 24));
        // 5 byte register address also gets included
        m_crcValue = calc5BitCRC32(m_crcValue, static_cast<boost::uint8_t>(registerAddress));
    }
}


void V5CRCRegister::check() const
{
    if (0 != m_crcValue) throw Exception();
}