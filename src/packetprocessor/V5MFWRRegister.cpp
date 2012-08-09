/**
* \file V5MFWRRegister.cpp
* \brief Contains definition of V5MFWRRegister class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/V5CMDRegister.hpp>
#include <packetprocessor/V5FDRIRegister.hpp>
#include <packetprocessor/V5MFWRRegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5MFWRRegister::V5MFWRRegister(const V5CMDRegister& cmdReg, V5FDRIRegister& fdriReg):
  Register(V5RegisterAddress::MFWR, V5RegisterAddress::MFWR_STRING, true, false),
  m_cmdReg(cmdReg),
  m_fdriReg(fdriReg)
{

}


void V5MFWRRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // CMD register must be in MFW mode
    if (V5CommandCode::MFW != m_cmdReg.commandCode()) throw Exception();
    // at least two dummy words must be written
    if (2 > wordCount) throw Exception();
    // write frame
    m_fdriReg.writePreviousFrame();
}


const V5CMDRegister& V5MFWRRegister::cmdRegister() const
{
    return m_cmdReg;
}


V5FDRIRegister& V5MFWRRegister::fdriRegister() const
{
    return m_fdriReg;
}