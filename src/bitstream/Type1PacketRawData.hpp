/**
* \file Type1PacketRawData.hpp
* \brief Functions for handling type 1 packet raw data.
*/

#pragma once
#ifndef BIL_TYPE1PACKETRAWDATA_HPP
#define BIL_TYPE1PACKETRAWDATA_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    class Type1Packet;


    /**
    * \brief Tells if some data starts with type 1 packet raw data.
    * \param words Pointer to data.
    * \param wordCount Number of data words.
    * \return Returns number of words the type 1 packet raw data occupies, if
    *         data starts with it. Otherwise returns 0.
    */
    size_t isType1Packet(const boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Gets raw data size of a packet.
    * \param type1Packet The type 1 packet in question.
    * \return Number of packet raw data words.
    */
    size_t type1PacketWordCount(const Type1Packet& type1Packet);

    /**
    * \brief Writes out a type 1 packet as raw data.
    * \param type1Packet The type 1 packet to be written.
    * \param words Pointer to buffer to write into.
    * \param wordCount Number of words in buffer.
    * \return Number of words written.
    * \throws .
    */
    size_t writeType1Packet(const Type1Packet& type1Packet, boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Reads in a type 1 packet from raw data.
    * \param type1Packet The type 1 packet in which to read.
    * \param words Pointer to type 1 raw data to read from.
    * \param wordCount Number of data words.
    * \return Number of words read.
    * \throws .
    */
    size_t readType1Packet(Type1Packet& type1Packet, const boost::uint32_t* words, size_t wordCount);

}

#endif
