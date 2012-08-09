/**
* \file V5PacketProcessor.cpp
* \brief Contains definition of V5PacketProcessor class.
*/

#include <configuration/V5AddressLayoutRegistry.hpp>
#include <exception/Exception.hpp>
#include <packetprocessor/V5PacketProcessor.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5PacketProcessor::V5PacketProcessor(const V5AddressLayoutRegistry& registry):
  m_addressLayoutRegistry(registry),
  m_registerLookup(V5RegisterAddress::CTL1),
  m_crcReg(),
  m_farReg(),
  m_cmdReg(m_crcReg),
  m_fdriReg(m_cmdReg, m_farReg),
  m_mfwrReg(m_cmdReg, m_fdriReg),
  m_idcodeReg(m_fdriReg, m_addressLayoutRegistry),
  m_fdroReg(V5RegisterAddress::FDRO, V5RegisterAddress::FDRO_STRING, false, true),
  m_ctl0Reg(V5RegisterAddress::CTL0, V5RegisterAddress::CTL0_STRING, true, true),
  m_maskReg(V5RegisterAddress::MASK, V5RegisterAddress::MASK_STRING, true, true),
  m_statReg(V5RegisterAddress::STAT, V5RegisterAddress::STAT_STRING, false, true),
  m_loutReg(V5RegisterAddress::LOUT, V5RegisterAddress::LOUT_STRING, true, false),
  m_cor0Reg(V5RegisterAddress::COR0, V5RegisterAddress::COR0_STRING, true, true),
  m_cbcReg(V5RegisterAddress::CBC, V5RegisterAddress::CBC_STRING, true, false),
  m_axssReg(V5RegisterAddress::AXSS, V5RegisterAddress::AXSS_STRING, true, true),
  m_cor1Reg(V5RegisterAddress::COR1, V5RegisterAddress::COR1_STRING, true, true),
  m_csobReg(V5RegisterAddress::CSOB, V5RegisterAddress::CSOB_STRING, true, false),
  m_wbstarReg(V5RegisterAddress::WBSTAR, V5RegisterAddress::WBSTAR_STRING, true, true),
  m_timerReg(V5RegisterAddress::TIMER, V5RegisterAddress::TIMER_STRING, true, true),
  m_reg19Reg(V5RegisterAddress::REG19, V5RegisterAddress::REG19_STRING, true, false),
  m_bootstsReg(V5RegisterAddress::BOOTSTS, V5RegisterAddress::BOOTSTS_STRING, false, true),
  m_ctl1Reg(V5RegisterAddress::CTL1, V5RegisterAddress::CTL1_STRING, true, true)
{
    m_registerLookup.add(m_crcReg);
    m_registerLookup.add(m_farReg);
    m_registerLookup.add(m_cmdReg);
    m_registerLookup.add(m_fdriReg);
    m_registerLookup.add(m_mfwrReg);
    m_registerLookup.add(m_idcodeReg);
    m_registerLookup.add(m_fdroReg);
    m_registerLookup.add(m_ctl0Reg);
    m_registerLookup.add(m_maskReg);
    m_registerLookup.add(m_statReg);
    m_registerLookup.add(m_loutReg);
    m_registerLookup.add(m_cor0Reg);
    m_registerLookup.add(m_cbcReg);
    m_registerLookup.add(m_axssReg);
    m_registerLookup.add(m_cor1Reg);
    m_registerLookup.add(m_csobReg);
    m_registerLookup.add(m_wbstarReg);
    m_registerLookup.add(m_timerReg);
    m_registerLookup.add(m_reg19Reg);
    m_registerLookup.add(m_bootstsReg);
    m_registerLookup.add(m_ctl1Reg);
}


void V5PacketProcessor::visit(const DummyWord& dummyWord)
{
    // dummy words after sync word contribute to the CRC check as they are used
    // for writing padding frames
    const boost::uint32_t dummy = dummyWord.value();
    if (behindSyncWord()) m_crcReg.update(&dummy, 1, V5RegisterAddress::FDRI);
}


void V5PacketProcessor::visit(const Type1Packet& type1Packet)
{
    V5BitstreamSyntaxChecker::visit(type1Packet);
    visitDataPacket(type1Packet);
}


void V5PacketProcessor::visit(const Type2Packet& type2Packet)
{
    V5BitstreamSyntaxChecker::visit(type2Packet);
    visitDataPacket(type2Packet);
}


void V5PacketProcessor::reset()
{
    // reset syntax check state and configuration memory
    V5BitstreamSyntaxChecker::reset();
    m_fdriReg.configuration().clear();
}


V5Configuration& V5PacketProcessor::configuration()
{
    return m_fdriReg.configuration();
}


const V5Configuration& V5PacketProcessor::configuration() const
{
    return m_fdriReg.configuration();
}


const V5AddressLayoutRegistry& V5PacketProcessor::addressLayoutRegistry() const
{
    return m_addressLayoutRegistry;
}


void V5PacketProcessor::visitDataPacket(const Type2Packet& type2Packet)
{
    // handle type 2 based data packets, they contain data for the register
    // engine
    switch (type2Packet.opcode()) {
    case PacketOpcode::REGISTER_WRITE:
        // do register write
        registerWrite(lastType1Address(), type2Packet.dataWords(), type2Packet.wordCount());
        break;

    case PacketOpcode::REGISTER_READ:
        // do register read - not implemented yet
        break;

    case PacketOpcode::NO_OP:
        // NO OP - do nothing
        break;

    default: throw Exception();
    }
}


void V5PacketProcessor::registerWrite(RegisterAddress::address_t regAddr, const boost::uint32_t* words, size_t wordCount)
{
    // get pointer to target register
    Register* reg = m_registerLookup.lookup(regAddr);
    if (0 == reg) throw Exception();

    // CRC check written data (excluding writes to LOUT)
    if (V5RegisterAddress::LOUT != regAddr)
        m_crcReg.update(words, wordCount, regAddr);

    // write data to target register
    reg->write(words, wordCount);
}