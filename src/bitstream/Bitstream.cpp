/**
* \file Bitstream.cpp
* \brief Contains definition of Bitstream class.
*/

#include <bitstream/Bitstream.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void Bitstream::append(std::auto_ptr<Packet> packet)
{
    m_packets.push_back(packet);
}


void Bitstream::insert(std::auto_ptr<Packet> packet, size_t packetIndex)
{
    if (m_packets.size() <= packetIndex) throw Exception();
    m_packets.insert(m_packets.begin() + packetIndex, packet);
}


void Bitstream::erase(size_t packetIndex)
{
    if (m_packets.size() <= packetIndex) throw Exception();
    m_packets.erase(m_packets.begin() + packetIndex);
}


void Bitstream::clear()
{
    m_packets.clear();
}


size_t Bitstream::size() const
{
    return m_packets.size();
}


Packet& Bitstream::at(size_t packetIndex)
{
    if (m_packets.size() <= packetIndex) throw Exception();
    return m_packets[packetIndex];
}


const Packet& Bitstream::at(size_t packetIndex) const
{
    if (m_packets.size() <= packetIndex) throw Exception();
    return m_packets[packetIndex];
}


void Bitstream::runVisitor(PacketVisitor& visitor) const
{
    size_t packetCount = m_packets.size();
    for (size_t i = 0; i < packetCount; ++i)
        (m_packets[i]).accept(visitor);
}