/**
* \file Type2PacketRawData.cpp
* \brief Functions for handling type 2 packet raw data.
*/

#include <bitstream/Type2Packet.hpp>
#include <bitstream/Type2PacketRawData.hpp>
#include <exception/Exception.hpp>

using namespace bil;

const size_t HEADERTYPE_BITSHIFT = 29;
const boost::uint32_t HEADERTYPE_VALUE = 0x2;

const size_t OPCODE_BITSHIFT = 27;
const boost::uint32_t OPCODE_BITMASK = 0x3;

const boost::uint32_t WORDCOUNT_BITMASK = 0x7ffffff;


size_t bil::isType2Packet(const boost::uint32_t* words, size_t wordCount)
{
    // packet header is one word
    if (1 > wordCount) return 0;

    // extract packet header
    boost::uint32_t header = *words;
    // check header type
    if (HEADERTYPE_VALUE != (header >> HEADERTYPE_BITSHIFT)) return 0;
    // if packet opcode is a write op, then the packet header is followed by the
    // data to be written
    if (PacketOpcode::REGISTER_WRITE == ((header >> OPCODE_BITSHIFT) & OPCODE_BITMASK))
        return 1 + (header & WORDCOUNT_BITMASK);
    else return 1;
}


size_t bil::type2PacketWordCount(const Type2Packet& type2Packet)
{
    // if packet opcode is REGISTER_WRITE, then the one word big packet header
    // is followed by the packet data. Otherwise packet is header only.
    if (PacketOpcode::REGISTER_WRITE == (type2Packet.opcode()))
        return 1 + type2Packet.wordCount();
    else return 1;
}


size_t bil::writeType2Packet(const Type2Packet& type2Packet, boost::uint32_t* words, size_t wordCount)
{
    // packet header is one word
    if (1 > wordCount) throw Exception();

    // check packet
    if (type2Packet.opcode() > OPCODE_BITMASK) throw Exception();
    if (type2Packet.wordCount() > WORDCOUNT_BITMASK) throw Exception();

    // write packet header
    *words++ =
        (HEADERTYPE_VALUE << HEADERTYPE_BITSHIFT) |
        (type2Packet.opcode() << OPCODE_BITSHIFT) |
        (type2Packet.wordCount());

    // if packet opcode is REGISTER_WRITE, then packet data follows
    if (PacketOpcode::REGISTER_WRITE != (type2Packet.opcode())) return 1;
    // check data length
    if ((1 + type2Packet.wordCount()) > wordCount) throw Exception();
    // write packet data
    memcpy(words, type2Packet.dataWords(), type2Packet.wordCount() << 2);

    // return written size
    return 1 + type2Packet.wordCount();
}


size_t bil::readType2Packet(Type2Packet& type2Packet, const boost::uint32_t* words, size_t wordCount)
{
    // packet header is one word
    if (1 > wordCount) throw Exception();

    // extract packet header and read its data
    boost::uint32_t header = *words++;
    // check packet header type
    if (HEADERTYPE_VALUE != (header >> HEADERTYPE_BITSHIFT)) throw Exception();
    // extract opcode
    type2Packet.opcode((header >> OPCODE_BITSHIFT) & OPCODE_BITMASK);
    // extract word count
    type2Packet.wordCount(header & WORDCOUNT_BITMASK);

    // if packet opcode is REGISTER_WRITE, then packet data follows
    if (PacketOpcode::REGISTER_WRITE != (type2Packet.opcode())) return 1;
    // check packet length
    if ((1 + type2Packet.wordCount()) > wordCount) throw Exception();
    // load data
    memcpy(type2Packet.dataWords(), words, type2Packet.wordCount() << 2);
    return 1 + type2Packet.wordCount();
}