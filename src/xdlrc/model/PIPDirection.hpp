/**
* \file PIPDirection.hpp
* \brief Contains PIPDirection enumeration constants and strings.
*/

#pragma once
#ifndef BIL_PIPDIRECTION_HPP
#define BIL_PIPDIRECTION_HPP


namespace bil {

    /**
    * \brief Namespace for PIP direction constants.
    *
    * The connections established by PIPs can have different directions, which
    * are enumerated here.
    */
    namespace PIPDirection {

        /// PIP direction type.
        typedef unsigned char direction_t;


        /// Directional, buffered.
        const direction_t MONODI_BUF = 0x00;

        /// Bidirectional, unbuffered.
        const direction_t BIDI_UNBUF = 0x01;

        /// Bidirectional, buffered in one direction.
        const direction_t BIDI_ONEBUF = 0x02;

        /// Bidirectional, buffered in both directions.
        const direction_t BIDI_TWOBUF = 0x03;


        extern const char* const MONODI_BUF_STRING;
        extern const char* const BIDI_UNBUF_STRING;
        extern const char* const BIDI_ONEBUF_STRING;
        extern const char* const BIDI_TWOBUF_STRING;


        /**
        * \brief Returns a string representation of given direction constant.
        * \param dir The direction constant.
        * \return The string representation.
        */
        const char* toString(direction_t dir);

        /**
        * \brief Returns direction constant of given string representation.
        * \param s The string representation.
        * \return The direction constant.
        * \throws .
        */
        direction_t fromString(const char* s);

    }

}

#endif
