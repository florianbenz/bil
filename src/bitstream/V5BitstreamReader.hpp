/**
* \file V5BitstreamReader.hpp
* \brief Contains declaration of V5BitstreamReader class.
*/

#pragma once
#ifndef BIL_V5BITSTREAMREADER_HPP
#define BIL_V5BITSTREAMREADER_HPP

#include <bitstream/Bitstream.hpp>
#include <bitstream/V5BitstreamSyntaxChecker.hpp>

namespace bil {

    /**
    * \brief Loads Virtex-5 bitstream raw data.
    *
    * This class reads a Virtex-5 raw bitstream, constructs the packets out of
    * it, and puts them into a Bitstream instance. While loading, the packet
    * stream will be syntax checked.
    */
    class V5BitstreamReader {
    public:

        /**********************************************************************/
        /* BITSTREAM LOADING                                                  */
        /**********************************************************************/

        /**
        * \brief Loads Virtex-5 bitstream raw data.
        * \param bitstream Bitstream instance to load packets into.
        * \param words Pointer to data words to load.
        * \param wordCount Number of data words to load.
        * \throws .
        */
        void read(Bitstream& bitstream, const boost::uint32_t* words, size_t wordCount);


    protected:

        /**
        * \brief Create a packet from raw data.
        * \param words Pointer to data words to load.
        * \param wordCount Number of data words to load.
        * \param packetPtr The newly created packet.
        * \return Number of raw data words this packet is loaded from.
        * \throws .
        */
        virtual size_t extractPacket(const boost::uint32_t* words, size_t wordCount, std::auto_ptr<Packet>& packetPtr);


        /**********************************************************************/
        /* SYNTAX CHECKER INTERFACE                                           */
        /**********************************************************************/

        /**
        * \brief Tells, if sync word was passed.
        * \return True if sync word was passed, false otherwise.
        */
        bool behindSyncWord() const;

        /**
        * \brief Tells, if the last packet processed was a type 1 packet.
        * \return True if last packet was a type 1 packet, false otherwise.
        */
        bool lastPacketWasType1() const;

        /**
        * \brief Gets the register address of the last processed type 1 packet.
        * \return The register address.
        */
        RegisterAddress::address_t lastType1Address() const;


    private:

        V5BitstreamSyntaxChecker m_syntaxChecker;

    };


    /**
    * \brief Loads Virtex-5 bitstream raw data.
    * \details Convenience functions for using V5BitstreamReader.
    * \param bitstream Bitstream instance to load packets into.
    * \param words Pointer to data words to load.
    * \param wordCount Number of data words to load.
    * \throws .
    */
    void readV5Bitstream(Bitstream& bitstream, const boost::uint32_t* words, size_t wordCount);

}

#endif
