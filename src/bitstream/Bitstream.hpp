/**
* \file Bitstream.hpp
* \brief Contains declaration of Bitstream class.
*/

#pragma once
#ifndef BIL_BITSTREAM_HPP
#define BIL_BITSTREAM_HPP

#include <memory>
#include <boost/ptr_container/ptr_vector.hpp>
#include <bitstream/Packet.hpp>


namespace bil {

    /**
    * \brief Models a Virtex bitstream.
    *
    * All bitstreams for Virtex devices consist of an ordered list of packets of
    * different types, depending on their purpose. The Bitstream class is a
    * polymorphic container holding the different packets in sequence.
    */
    class Bitstream {
    public:

        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Appends a packet to the bitstream.
        * \param packet The new packet.
        */
        void append(std::auto_ptr<Packet> packet);

        /**
        * \brief Inserts a packet into the bitstream.
        * \param packet The new packet.
        * \param packetIndex Index at which packet is inserted.
        */
        void insert(std::auto_ptr<Packet> packet, size_t packetIndex);

        /**
        * \brief Erases a packet from bitstream.
        * \param packetIndex Index of packet to erase.
        */
        void erase(size_t packetIndex);

        /**
        * \brief Erases all packets.
        */
        void clear();


        /**********************************************************************/
        /* CONTENT ITERATION                                                  */
        /**********************************************************************/

        /**
        * \brief Gets the number of contained packets.
        * \return The packet count.
        */
        size_t size() const;

        /**
        * \brief Gets the packet at the specified index.
        * \param packetIndex Index of packet to get.
        * \return The Packet.
        * \throws .
        */
        Packet& at(size_t packetIndex);

        /**
        * \brief Gets the packet at the specified index read only.
        * \param packetIndex Index of packet to get.
        * \return The Packet.
        * \throws .
        */
        const Packet& at(size_t packetIndex) const;


        /**********************************************************************/
        /* VISITOR INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Visits every packet with specified visitor.
        * \param visitor Visitor to call.
        */
        void runVisitor(PacketVisitor& visitor) const;


    private:

        boost::ptr_vector<Packet> m_packets;

    };

}

#endif
