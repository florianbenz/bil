/**
* \file CRC32.hpp
* \brief Contains declaration of CRC32 functions.
*/

#pragma once
#ifndef BIL_CRC32_HPP
#define BIL_CRC32_HPP

#include <boost/cstdint.hpp>

namespace bil {

    /**
    * \brief Calculates the CRC32 value from 8 bit data and an initial value.
    * \details The algorithm uses 0x82f63b78 as generator polynomial, i.e. the
    *          reversed Castagnoli polynomial (0x1edc6f41).
    * \param oldCRC initial value for CRC
    * \param data8Bit 8 bit of data
    * \return CRC value of given data.
    */
    boost::uint32_t calc8BitCRC32(boost::uint32_t oldCRC, boost::uint8_t data8Bit);

    /**
    * \brief Calculates the CRC32 value from 5 bit data and an initial value.
    * \details The algorithm uses 0x82f63b78 as generator polynomial, i.e. the
    *          reversed Castagnoli polynomial (0x1edc6f41).
    * \param oldCRC initial value for CRC
    * \param data5Bit 5 bit of data
    * \return CRC value of given data.
    */
    boost::uint32_t calc5BitCRC32(boost::uint32_t oldCRC, boost::uint8_t data5Bit);

}

#endif
