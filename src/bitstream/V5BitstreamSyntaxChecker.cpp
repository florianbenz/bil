/**
* \file V5BitstreamSyntaxChecker.cpp
* \brief Contains definition of V5BitstreamSyntaxChecker class.
*/

#include <bitstream/V5BitstreamSyntaxChecker.hpp>
#include <exception/Exception.hpp>

using namespace bil;


V5BitstreamSyntaxChecker::V5BitstreamSyntaxChecker()
{
    reset();
}


bool V5BitstreamSyntaxChecker::behindSyncWord() const
{
    return m_behindSyncWord;
}


bool V5BitstreamSyntaxChecker::lastPacketWasType1() const
{
    return m_lastPacketWasType1;
}


RegisterAddress::address_t V5BitstreamSyntaxChecker::lastType1Address() const
{
    return m_lastType1Address;
}


void V5BitstreamSyntaxChecker::reset()
{
    // reset status flags
    m_behindSyncWord = false;
    m_lastPacketWasType1 = false;
    m_lastType1Address = 0;
}


void V5BitstreamSyntaxChecker::visit(const BuswidthPattern&)
{
    // buswidth pattern is only allowed somewhere in front of sync word
    if (m_behindSyncWord) throw Exception();
    m_lastPacketWasType1 = false;
}


void V5BitstreamSyntaxChecker::visit(const DummyWord&)
{
    // dummy words are allowed everywhere
    m_lastPacketWasType1 = false;
}


void V5BitstreamSyntaxChecker::visit(const SyncWord&)
{
    // sync word is only allowed one time
    if (m_behindSyncWord) throw Exception();
    m_behindSyncWord = true;
    m_lastPacketWasType1 = false;
}


void V5BitstreamSyntaxChecker::visit(const Type1Packet& type1Packet)
{
    // type 1 data packets are only allowed somewhere behind sync word
    if (!m_behindSyncWord) throw Exception();
    m_lastPacketWasType1 = true;
    // store packet's register address
    m_lastType1Address = type1Packet.registerAddress();
}


void V5BitstreamSyntaxChecker::visit(const Type2Packet&)
{
    // type 2 data packets are only allowed somewhere behind sync word and
    // have to be immediately behind a type 1 packet
    if (!m_behindSyncWord) throw Exception();
    if (!m_lastPacketWasType1) throw Exception();
    m_lastPacketWasType1 = false;
}