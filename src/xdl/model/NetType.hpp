/**
* \file NetType.hpp
* \brief Contains NetType enumeration constants and strings.
*/

#pragma once
#ifndef BIL_NETTYPE_HPP
#define BIL_NETTYPE_HPP


namespace bil {

    /**
    * \brief Namespace for net type constants.
    *
    * In XDL the net type denotes whether a net is normal wiring, or tied to a
    * power source or to the ground.
    */
    namespace NetType {

        /// Net type.
        typedef unsigned char net_t;


        /// Normal wiring.
        const net_t WIRE = 0x00;

        /// Tied to a DC power source.
        const net_t VCC = 0x01;

        /// Tied to ground.
        const net_t GND = 0x02;


        extern const char* const WIRE_STRING;
        extern const char* const VCC_STRING;
        extern const char* const VDD_STRING;
        extern const char* const POWER_STRING;
        extern const char* const GND_STRING;
        extern const char* const GROUND_STRING;


        /**
        * \brief Returns a string representation of given net type constant.
        * \param type The net type constant.
        * \return The string representation.
        */
        const char* toString(net_t type);

        /**
        * \brief Returns net type of given string representation.
        * \param s The string representation.
        * \return The net type constant.
        * \throws .
        */
        net_t fromString(const char* s);

    }

}

#endif
