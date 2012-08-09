/**
* \file Packet.hpp
* \brief Contains declaration of Packet class.
*/

#pragma once
#ifndef BIL_PACKET_HPP
#define BIL_PACKET_HPP


namespace bil {

    class PacketVisitor;


    /**
    * \brief Abstract base class for packets in a bitstream.
    *
    * This class is the abstract base class for all packet types occurring in a
    * bitstream. For a simple runtime packet type retrieval this class has a
    * visitor accepting method which has to be overwritten by descendants to be
    * visited.
    */
    class Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual Packet* clone() const = 0;

        /**
        * \brief Destructs a Packet instance.
        */
        virtual ~Packet();


        /**********************************************************************/
        /* VISITOR INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Accepts a visitor for dynamic type dependent stuff.
        * \param visitor Visitor, which matching method will be called.
        */
        virtual void accept(PacketVisitor& visitor) const = 0;

    };

    /**
    * \brief Creates a polymorphic copy of a packet.
    * \param src Reference to packet to copy.
    * \return Pointer to the copied instance.
    */
    Packet* new_clone(const Packet& src);

}

#endif
