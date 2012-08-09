/**
* \file V5BitstreamSyntaxChecker.hpp
* \brief Contains declaration of V5BitstreamSyntaxChecker class.
*/

#pragma once
#ifndef BIL_V5BITSTREAMSYNTAXCHECKER_HPP
#define BIL_V5BITSTREAMSYNTAXCHECKER_HPP

#include <bitstream/V5PacketVisitor.hpp>


namespace bil {

    /**
    * \brief Visitor for checking syntax of a Virtex-5 bitstream.
    *
    * A Packet visitor that checks the syntactical correctness of a Virtex-5
    * bitstream. That means, that the packets have to be in the right order and
    * number, and have to be of types that are valid for Virtex-5 bitstreams.
    * Every time a packet is given to a V5BitstreamSyntaxChecker instance, it
    * updates its state. In case of a syntax error it throws an exception.
    */
    class V5BitstreamSyntaxChecker: public V5PacketVisitor {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        V5BitstreamSyntaxChecker();


        /**********************************************************************/
        /* SYNTAX CHECK STATE                                                 */
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

        /**
        * \brief Resets the internal state.
        */
        virtual void reset();


        /**********************************************************************/
        /* VISITING METHODS                                                   */
        /**********************************************************************/

        /**
        * \brief Visits a BuswidthPattern packet.
        * \param buswidthPattern BuswidthPattern instance to be visited.
        * \throws .
        */
        virtual void visit(const BuswidthPattern& buswidthPattern);

        /**
        * \brief Visits a DummyWord packet.
        * \details Never throws, since dummy words can be everywhere.
        * \param dummyWord DummyWord instance to be visited.
        */
        virtual void visit(const DummyWord& dummyWord);

        /**
        * \brief Visits a SyncWord packet.
        * \param syncWord SyncWord instance to be visited.
        * \throws .
        */
        virtual void visit(const SyncWord& syncWord);

        /**
        * \brief Visits a Type1Packet packet.
        * \param type1Packet Type1Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type1Packet& type1Packet);

        /**
        * \brief Visits a Type2Packet packet.
        * \param type2Packet Type2Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type2Packet& type2Packet);


    private:

        bool m_behindSyncWord;
        bool m_lastPacketWasType1;
        RegisterAddress::address_t m_lastType1Address;

    };

}

#endif
