/**
* \file V5CommandCode.hpp
* \brief Contains V5CommandCode enumeration constants and strings.
*/

#pragma once
#ifndef BIL_V5COMMANDCODE_HPP
#define BIL_V5COMMANDCODE_HPP

#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Namespace for Virtex-5 command code constants.
    *
    * The following command codes are recognized by Virtex-5 command register.
    */
    namespace V5CommandCode {

        /// Command code type.
        typedef boost::uint32_t command_t;

        const command_t NULLCMD = 0x0;
        const command_t WCFG = 0x1;
        const command_t MFW = 0x2;
        const command_t LFRM = 0x3;
        const command_t RCFG = 0x4;
        const command_t START = 0x5;
        const command_t RCAP = 0x6;
        const command_t RCRC = 0x7;
        const command_t AGHIGH = 0x8;
        const command_t SWITCH = 0x9;
        const command_t GRESTORE = 0xa;
        const command_t SHUTDOWN = 0xb;
        const command_t GCAPTURE = 0xc;
        const command_t DESYNCH = 0xd;
        const command_t IPROG = 0xf;
        const command_t CRCC = 0x10;
        const command_t LTIMER = 0x11;

        extern const char* const NULLCMD_STRING;
        extern const char* const WCFG_STRING;
        extern const char* const MFW_STRING;
        extern const char* const LFRM_STRING;
        extern const char* const RCFG_STRING;
        extern const char* const START_STRING;
        extern const char* const RCAP_STRING;
        extern const char* const RCRC_STRING;
        extern const char* const AGHIGH_STRING;
        extern const char* const SWITCH_STRING;
        extern const char* const GRESTORE_STRING;
        extern const char* const SHUTDOWN_STRING;
        extern const char* const GCAPTURE_STRING;
        extern const char* const DESYNCH_STRING;
        extern const char* const IPROG_STRING;
        extern const char* const CRCC_STRING;
        extern const char* const LTIMER_STRING;


        /**
        * \brief Returns a string representation of given command code.
        * \return The string representation.
        */
        const char* toString(command_t command);

    }

}

#endif
