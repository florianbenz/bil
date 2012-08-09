/**
* \file V5CMDRegister.cpp
* \brief Contains definition of V5CMDRegister class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/V5CMDRegister.hpp>
#include <packetprocessor/V5CRCRegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5CMDRegister::V5CMDRegister(V5CRCRegister& crcReg):
  Register(V5RegisterAddress::CMD, V5RegisterAddress::CMD_STRING, true, true),
  m_command(V5CommandCode::NULLCMD),
  m_crcReg(crcReg)
{

}


void V5CMDRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // set command and execute
    commandCode(*words);
    execute();
}


void V5CMDRegister::read(boost::uint32_t* words, size_t wordCount) const
{
    Register::read(words, wordCount);

    // word count has to be 1
    if (1 != wordCount) throw Exception();
    // return current command code
    *words = m_command;
}


void V5CMDRegister::commandCode(V5CommandCode::command_t code)
{
    // ensure that only valid command codes are loaded into register
    switch (code) {
    case V5CommandCode::NULLCMD:
    case V5CommandCode::WCFG:
    case V5CommandCode::MFW:
    case V5CommandCode::LFRM:
    case V5CommandCode::RCFG:
    case V5CommandCode::START:
    case V5CommandCode::RCAP:
    case V5CommandCode::RCRC:
    case V5CommandCode::AGHIGH:
    case V5CommandCode::SWITCH:
    case V5CommandCode::GRESTORE:
    case V5CommandCode::SHUTDOWN:
    case V5CommandCode::GCAPTURE:
    case V5CommandCode::DESYNCH:
    case V5CommandCode::IPROG:
    case V5CommandCode::CRCC:
    case V5CommandCode::LTIMER: m_command = code; break;
    default: throw Exception();
    }
}


V5CommandCode::command_t V5CMDRegister::commandCode() const
{
    return m_command;
}


void V5CMDRegister::execute() const
{
    // only implemented command code at the moment is RCRC
    if (V5CommandCode::RCRC == m_command) m_crcReg.reset();
}


V5CRCRegister& V5CMDRegister::crcRegister() const
{
    return m_crcReg;
}