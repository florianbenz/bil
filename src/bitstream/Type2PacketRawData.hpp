/**
* \file Type2PacketRawData.hpp
* \brief Functions for handling type 2 packet raw data.
*/

#pragma once
#ifndef BIL_TYPE2PACKETRAWDATA_HPP
#define BIL_TYPE2PACKETRAWDATA_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    class Type2Packet;


    /**
    * \brief Tells if some data starts with type 2 packet raw data.
    * \param words Pointer to data.
    * \param wordCount Number of data words.
    * \return Returns number of words the type 2 packet raw data occupies, if
    *         data starts with it. Otherwise returns 0.
    */
    size_t isType2Packet(const boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Gets raw data size of a packet.
    * \param type2Packet The type 2 packet in question.
    * \return Number of packet raw data words.
    */
    size_t type2PacketWordCount(const Type2Packet& type2Packet);

    /**
    * \brief Writes out a type 2 packet as raw data.
    * \param type2Packet The type 2 packet to be written.
    * \param words Pointer to buffer to write into.
    * \param wordCount Number of words in buffer.
    * \return Number of words written.
    * \throws .
    */
    size_t writeType2Packet(const Type2Packet& type2Packet, boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Reads in a type 2 packet from raw data.
    * \param type2Packet The type 2 packet in which to read.
    * \param words Pointer to type 2 raw data to read from.
    * \param wordCount Number of data words.
    * \return Number of words read.
    * \throws .
    */
    size_t readType2Packet(Type2Packet& type2Packet, const boost::uint32_t* words, size_t wordCount);

}

#endif
