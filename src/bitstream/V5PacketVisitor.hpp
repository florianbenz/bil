/**
* \file V5PacketVisitor.hpp
* \brief Contains declaration of V5PacketVisitor class.
*/

#pragma once
#ifndef BIL_V5PACKETVISITOR_HPP
#define BIL_V5PACKETVISITOR_HPP

#include <bitstream/BuswidthPattern.hpp>
#include <bitstream/DummyWord.hpp>
#include <bitstream/Packet.hpp>
#include <bitstream/PacketVisitor.hpp>
#include <bitstream/SyncWord.hpp>
#include <bitstream/Type1Packet.hpp>
#include <bitstream/Type2Packet.hpp>


namespace bil {

    /**
    * \brief Visitor base class for Virtex-5 bitstream packets.
    *
    * Visitor base class for visiting packets in Virtex-5 bitstreams. Throws an
    * exception when visiting a non Virtex-5 packet. Purpose: if a new packet
    * type is added to PacketVisitor ancestor class, then the corresponding
    * visit() method should be defined in V5PacketVisitor to always throw an
    * exception. So all concrete Virtex-5 visitors are not forced into
    * implementing a from their perspective irrelevant visit() method; and when
    * such a method is called, an exception is thrown.
    */
    class V5PacketVisitor: public PacketVisitor {
    public:

        /**
        * \brief Relevant visit() method for Virtex-5 bitstreams.
        * \details This method is empty and should be overridden by concrete
        *          visitors to do something useful.
        * \param buswidthPattern BuswidthPattern instance to be visited.
        */
        virtual void visit(const BuswidthPattern& buswidthPattern);

        /**
        * \brief Relevant visit() method for Virtex-5 bitstreams.
        * \details This method is empty and should be overridden by concrete
        *          visitors to do something useful.
        * \param dummyWord DummyWord instance to be visited.
        */
        virtual void visit(const DummyWord& dummyWord);

        /**
        * \brief Relevant visit() method for Virtex-5 bitstreams.
        * \details This method is empty and should be overridden by concrete
        *          visitors to do something useful.
        * \param syncWord SyncWord instance to be visited.
        */
        virtual void visit(const SyncWord& syncWord);

        /**
        * \brief Relevant visit() method for Virtex-5 bitstreams.
        * \details This method is empty and should be overridden by concrete
        *          visitors to do something useful.
        * \param type1Packet Type1Packet instance to be visited.
        */
        virtual void visit(const Type1Packet& type1Packet);

        /**
        * \brief Relevant visit() method for Virtex-5 bitstreams.
        * \details This method is empty and should be overridden by concrete
        *          visitors to do something useful.
        * \param type2Packet Type2Packet instance to be visited.
        */
        virtual void visit(const Type2Packet& type2Packet);


        /**
        * \brief Irrelevant visit() method for Virtex-5 bitstreams.
        * \details This method throws an exception and need not be overridden
        *          by concrete visitors.
        * \param packet Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Packet& packet);

    };

}

#endif
