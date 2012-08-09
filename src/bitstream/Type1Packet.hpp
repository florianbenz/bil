/**
* \file Type1Packet.hpp
* \brief Contains declaration of Type1Packet class.
*/

#pragma once
#ifndef BIL_TYPE1PACKET_HPP
#define BIL_TYPE1PACKET_HPP

#include <bitstream/RegisterAddress.hpp>
#include <bitstream/Type2Packet.hpp>


namespace bil {

    /**
    * \brief A type 1 packet.
    *
    * The type 1 packet carries besides opcode and data a register address. This
    * address tells the configuration logic which register should be read or in
    * which register the packet data should be written.
    */
    class Type1Packet: public Type2Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Default constructor.
        */
        Type1Packet();

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual Type1Packet* clone() const;


        /**********************************************************************/
        /* VISITOR INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Accepts a visitor for dynamic type dependent stuff.
        * \param visitor Visitor, which matching method will be called.
        */
        virtual void accept(PacketVisitor& visitor) const;


        /**********************************************************************/
        /* PACKET CONTENT                                                     */
        /**********************************************************************/

        /**
        * \brief Sets register address.
        * \param address New register address.
        */
        void registerAddress(RegisterAddress::address_t address);

        /**
        * \brief Gets register address.
        * \return Current register address.
        */
        RegisterAddress::address_t registerAddress() const;


        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Zeros register address (additionally to inherited behavior).
        */
        virtual void clear();


    private:

        RegisterAddress::address_t m_registerAddress;

    };

}

#endif
