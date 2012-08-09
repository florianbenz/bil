/**
* \file Type2Packet.cpp
* \brief Contains definition of Type2Packet class.
*/

#include <bitstream/PacketVisitor.hpp>
#include <bitstream/Type2Packet.hpp>
#include <exception/Exception.hpp>

using namespace bil;


Type2Packet::Type2Packet():
  m_data(),
  m_wordCount(0),
  m_opcode(PacketOpcode::NO_OP)
{

}


Type2Packet* Type2Packet::clone() const
{
    return new Type2Packet(*this);
}


void Type2Packet::accept(PacketVisitor& visitor) const
{
    visitor.visit(*this);
}


void Type2Packet::opcode(PacketOpcode::opcode_t opcode)
{
    // set word count and data according to opcode
    switch (opcode)
    {
    case PacketOpcode::NO_OP:
        // word count has to be zero, no data allowed
        m_wordCount = 0;
        m_data.resize(0);
        break;

    case PacketOpcode::REGISTER_READ:
        // no data allowed
        m_data.resize(0);
        break;

    case PacketOpcode::REGISTER_WRITE:
        // set data size to word count words
        m_data.resize(m_wordCount);
        break;

    default: throw Exception();
    }

    // set new opcode
    m_opcode = opcode;
}


PacketOpcode::opcode_t Type2Packet::opcode() const
{
    return m_opcode;
}


void Type2Packet::wordCount(size_t count)
{
    // in no op mode, count must be zero
    if ((PacketOpcode::NO_OP == m_opcode) && (0 < count))
        throw Exception();

    // set new count
    m_wordCount = count;

    // in write mode resize data to new size
    if (PacketOpcode::REGISTER_WRITE == m_opcode)
        m_data.resize(count);
}


size_t Type2Packet::wordCount() const
{
    return m_wordCount;
}


boost::uint32_t* Type2Packet::dataWords()
{
    // if there is data, return pointer to it, else return 0.
    if (0 < m_data.size()) return &(m_data[0]);
    else return 0;
}


const boost::uint32_t* Type2Packet::dataWords() const
{
    // if there is data, return pointer to it, else return 0.
    if (0 < m_data.size()) return &(m_data[0]);
    else return 0;
}


void Type2Packet::clear()
{
    m_opcode = PacketOpcode::NO_OP;
    m_wordCount = 0;
    m_data.resize(0);
}