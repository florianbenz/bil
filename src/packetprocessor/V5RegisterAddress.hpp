/**
* \file V5RegisterAddress.hpp
* \brief Contains V5RegisterAddress enumeration constants and strings.
*/

#pragma once
#ifndef BIL_V5REGISTERADDRESS_HPP
#define BIL_V5REGISTERADDRESS_HPP

#include <bitstream/RegisterAddress.hpp>


namespace bil {

    /**
    * \brief Namespace for Virtex-5 register address constants.
    *
    * Contains the register address constants of a Virtex-5 packet processor.
    */
    namespace V5RegisterAddress {

        const RegisterAddress::address_t CRC = 0x0;
        const RegisterAddress::address_t FAR = 0x1;
        const RegisterAddress::address_t FDRI = 0x2;
        const RegisterAddress::address_t FDRO = 0x3;
        const RegisterAddress::address_t CMD = 0x4;
        const RegisterAddress::address_t CTL0 = 0x5;
        const RegisterAddress::address_t MASK = 0x6;
        const RegisterAddress::address_t STAT = 0x7;
        const RegisterAddress::address_t LOUT = 0x8;
        const RegisterAddress::address_t COR0 = 0x9;
        const RegisterAddress::address_t MFWR = 0xa;
        const RegisterAddress::address_t CBC = 0xb;
        const RegisterAddress::address_t IDCODE = 0xc;
        const RegisterAddress::address_t AXSS = 0xd;
        const RegisterAddress::address_t COR1 = 0xe;
        const RegisterAddress::address_t CSOB = 0xf;
        const RegisterAddress::address_t WBSTAR = 0x10;
        const RegisterAddress::address_t TIMER = 0x11;
        const RegisterAddress::address_t REG19 = 0x13;
        const RegisterAddress::address_t BOOTSTS = 0x16;
        const RegisterAddress::address_t CTL1 = 0x18;

        extern const char* const CRC_STRING;
        extern const char* const FAR_STRING;
        extern const char* const FDRI_STRING;
        extern const char* const FDRO_STRING;
        extern const char* const CMD_STRING;
        extern const char* const CTL0_STRING;
        extern const char* const MASK_STRING;
        extern const char* const STAT_STRING;
        extern const char* const LOUT_STRING;
        extern const char* const COR0_STRING;
        extern const char* const MFWR_STRING;
        extern const char* const CBC_STRING;
        extern const char* const IDCODE_STRING;
        extern const char* const AXSS_STRING;
        extern const char* const COR1_STRING;
        extern const char* const CSOB_STRING;
        extern const char* const WBSTAR_STRING;
        extern const char* const TIMER_STRING;
        extern const char* const REG19_STRING;
        extern const char* const BOOTSTS_STRING;
        extern const char* const CTL1_STRING;


        /**
        * \brief Returns a string representation of given address constant.
        * \return The string representation.
        */
        const char* toString(RegisterAddress::address_t address);

    }

}

#endif
