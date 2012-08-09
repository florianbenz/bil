/**
* \file Type2Packet.hpp
* \brief Contains declaration of Type2Packet class.
*/

#pragma once
#ifndef BIL_TYPE2PACKET_HPP
#define BIL_TYPE2PACKET_HPP

#include <vector>
#include <cstring>
#include <boost/cstdint.hpp>
#include <bitstream/Packet.hpp>
#include <bitstream/PacketOpcode.hpp>


namespace bil {

    /**
    * \brief Type 2 data packet.
    *
    * Type 2 packets carry data and an opcode telling configuration logic what
    * to do (read, write, or no op). The read mode requests data from the
    * configuration logic (this data will be outputted to the configuration
    * interface). The write mode writes the packet data to configuration logic
    * (this will trigger some further actions like configuration logic state
    * changes and/or writes to configuration memory). The no op mode simply does
    * nothing.
    */
    class Type2Packet: public Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Default constructor.
        */
        Type2Packet();

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual Type2Packet* clone() const;


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
        * \brief Sets packet opcode.
        * \param opcode New opcode.
        * \throws .
        */
        void opcode(PacketOpcode::opcode_t opcode);

        /**
        * \brief Gets packet opcode.
        * \return The current opcode.
        */
        PacketOpcode::opcode_t opcode() const;


        /**
        * \brief Sets word count.
        * \details In read mode this sets how many words should be read from
        *          configuration logic, in write mode how many words should
        *          be written to configuration logic. In NO_OP mode the only
        *          valid word count is zero.
        * \param count New word count.
        * \throws .
        */
        void wordCount(size_t count);

        /**
        * \brief Gets word count.
        * \return The current word count.
        */
        size_t wordCount() const;


        /**
        * \brief Gets a pointer to payload data.
        * \details If packet is not in write mode, this will return 0.
        * \return The pointer.
        */
        boost::uint32_t* dataWords();

        /**
        * \brief Gets a pointer to read only payload data.
        * \details If packet is not in write mode, this will return 0.
        * \return The pointer.
        */
        const boost::uint32_t* dataWords() const;


        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Sets opcode to NO_OP, wordCount to 0, and clears data.
        */
        virtual void clear();


    private:

        std::vector<boost::uint32_t> m_data;
        size_t m_wordCount;

        PacketOpcode::opcode_t m_opcode;

    };

}

#endif
