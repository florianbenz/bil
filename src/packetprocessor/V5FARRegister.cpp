/**
* \file V5FARRegister.cpp
* \brief Contains definition of V5FARRegister class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/V5FARRegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5FARRegister::V5FARRegister():
  Register(V5RegisterAddress::FAR, V5RegisterAddress::FAR_STRING, true, true),
  m_frameAddress()
{

}


void V5FARRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // set command and execute
    m_frameAddress.rawAddress(*words);
}


void V5FARRegister::read(boost::uint32_t* words, size_t wordCount) const
{
    Register::read(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // return current command code
    *words = m_frameAddress.rawAddress();
}


V5FrameAddress& V5FARRegister::frameAddress()
{
    return m_frameAddress;
}


const V5FrameAddress& V5FARRegister::frameAddress() const
{
    return m_frameAddress;
}