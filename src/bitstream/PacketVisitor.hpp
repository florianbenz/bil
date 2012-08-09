/**
* \file PacketVisitor.hpp
* \brief Contains declaration of PacketVisitor class.
*/

#pragma once
#ifndef BIL_PACKETVISITOR_HPP
#define BIL_PACKETVISITOR_HPP


namespace bil {

    class BuswidthPattern;
    class DummyWord;
    class Packet;
    class SyncWord;
    class Type1Packet;
    class Type2Packet;


    /**
    * \brief Abstract visitor base class for bitstream packets.
    *
    * By deriving from PacketVisitor and passing these instances into
    * Packet::accept() method, the visitor's visit() method matching the
    * packet's dynamic type will be called. So it's possible to inquiry the
    * dynamic type of a given packet.
    */
    class PacketVisitor {
    public:

        virtual ~PacketVisitor() {};


        /**
        * \brief Method for visiting a BuswidthPattern instance.
        * \param buswidthPattern BuswidthPattern instance to be visited.
        */
        virtual void visit(const BuswidthPattern& buswidthPattern) = 0;

        /**
        * \brief Method for visiting a DummyWord instance.
        * \param dummyWord DummyWord instance to be visited.
        */
        virtual void visit(const DummyWord& dummyWord) = 0;

        /**
        * \brief Method for visiting a Packet instance.
        * \param packet Packet instance to be visited.
        */
        virtual void visit(const Packet& packet) = 0;

        /**
        * \brief Method for visiting a SyncWord instance.
        * \param syncWord SyncWord instance to be visited.
        */
        virtual void visit(const SyncWord& syncWord) = 0;

        /**
        * \brief Method for visiting a Type1Packet instance.
        * \param type1Packet Type1Packet instance to be visited.
        */
        virtual void visit(const Type1Packet& type1Packet) = 0;

        /**
        * \brief Method for visiting a Type2Packet instance.
        * \param type2Packet Type2Packet instance to be visited.
        */
        virtual void visit(const Type2Packet& type2Packet) = 0;

    };

}

#endif
