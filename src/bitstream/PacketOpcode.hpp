/**
* \file PacketOpcode.hpp
* \brief Contains packet opcode enumeration constants and strings.
*/

#pragma once
#ifndef BIL_PACKETOPCODE_HPP
#define BIL_PACKETOPCODE_HPP


namespace bil {

    /**
    * \brief Namespace for packet opcode constants.
    *
    * Some packets in the bitstream contain an opcode, which tells configuration
    * logic (i.e. the packet processor) what to do with this packet.
    */
    namespace PacketOpcode {

        /// Packet opcode type. Tells configuration logic what to do.
        typedef unsigned char opcode_t;


        /// This opcode means: do nothing.
        const opcode_t NO_OP = 0x00;

        /// This opcode means: read data from fpga (to configuration interface).
        const opcode_t REGISTER_READ = 0x01;

        /// This opcode means: write data to fpga (from packet).
        const opcode_t REGISTER_WRITE = 0x02;


        extern const char* const NO_OP_STRING;
        extern const char* const REGISTER_READ_STRING;
        extern const char* const REGISTER_WRITE_STRING;


        /**
        * \brief Returns a string representation of given opcode constant.
        * \return The string representation.
        */
        const char* toString(opcode_t opcode);

    }

}

#endif
