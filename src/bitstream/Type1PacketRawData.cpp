/**
* \file Type1PacketRawData.cpp
* \brief Functions for handling type 1 packet raw data.
*/

#include <bitstream/Type1Packet.hpp>
#include <bitstream/Type1PacketRawData.hpp>
#include <exception/Exception.hpp>

using namespace bil;

const size_t HEADERTYPE_BITSHIFT = 29;
const boost::uint32_t HEADERTYPE_VALUE = 0x1;

const size_t OPCODE_BITSHIFT = 27;
const boost::uint32_t OPCODE_BITMASK = 0x3;

const size_t REGISTERADDRESS_BITSHIFT = 13;
const boost::uint32_t REGISTERADDRESS_BITMASK = 0x3fff;

const boost::uint32_t WORDCOUNT_BITMASK = 0x7ff;


size_t bil::isType1Packet(const boost::uint32_t* words, size_t wordCount)
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


size_t bil::type1PacketWordCount(const Type1Packet& type1Packet)
{
    // if packet opcode is REGISTER_WRITE, then the one word big packet header
    // is followed by the packet data. Otherwise packet is header only.
    if (PacketOpcode::REGISTER_WRITE == (type1Packet.opcode()))
        return 1 + type1Packet.wordCount();
    else return 1;
}


size_t bil::writeType1Packet(const Type1Packet& type1Packet, boost::uint32_t* words, size_t wordCount)
{
    // packet header is one word
    if (1 > wordCount) throw Exception();

    // check packet
    if (type1Packet.opcode() > OPCODE_BITMASK) throw Exception();
    if (type1Packet.registerAddress() > REGISTERADDRESS_BITMASK) throw Exception();
    if (type1Packet.wordCount() > WORDCOUNT_BITMASK) throw Exception();

    // write packet header
    *words++ =
        (HEADERTYPE_VALUE << HEADERTYPE_BITSHIFT) |
        (type1Packet.opcode() << OPCODE_BITSHIFT) |
        (type1Packet.registerAddress() << REGISTERADDRESS_BITSHIFT) |
        (type1Packet.wordCount());

    // if packet opcode is REGISTER_WRITE, then packet data follows
    if (PacketOpcode::REGISTER_WRITE != (type1Packet.opcode())) return 1;
    // check data length
    if ((1 + type1Packet.wordCount()) > wordCount) throw Exception();
    // write packet data
    memcpy(words, type1Packet.dataWords(), type1Packet.wordCount() << 2);

    // return written size
    return 1 + type1Packet.wordCount();
}


size_t bil::readType1Packet(Type1Packet& type1Packet, const boost::uint32_t* words, size_t wordCount)
{
    // packet header is one word
    if (1 > wordCount) throw Exception();

    // extract packet header and read its data
    boost::uint32_t header = *words++;
    // check packet header type
    if (HEADERTYPE_VALUE != (header >> HEADERTYPE_BITSHIFT)) throw Exception();
    // extract opcode
    type1Packet.opcode((header >> OPCODE_BITSHIFT) & OPCODE_BITMASK);
    // extract register address
    type1Packet.registerAddress(static_cast<RegisterAddress::address_t>(
        (header >> REGISTERADDRESS_BITSHIFT) & REGISTERADDRESS_BITMASK));
    // extract word count
    type1Packet.wordCount(header & WORDCOUNT_BITMASK);

    // if packet opcode is REGISTER_WRITE, then packet data follows
    if (PacketOpcode::REGISTER_WRITE != (type1Packet.opcode())) return 1;
    // check packet length
    if ((1 + type1Packet.wordCount()) > wordCount) throw Exception();
    // load data
    memcpy(type1Packet.dataWords(), words, type1Packet.wordCount() << 2);
    return 1 + type1Packet.wordCount();
}