/**
* \file EndianConversion.hpp
* \brief Contains functions for converting endianess.
*/

#pragma once
#ifndef BIL_ENDIANCONVERSION_HPP
#define BIL_ENDIANCONVERSION_HPP

#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Swaps given 16 bit value from big endian to little endian and vice
    *          versa (i.e. exchanges first octet for second).
    * \param x The value.
    * \return The endianess swapped value.
    */
    inline boost::uint16_t swapBigLittleEndian(const boost::uint16_t& x)
    {
        return (x >> 8) |
               (x << 8);
    }

    /**
    * \brief Swaps given 32 bit value from big endian to little endian and vice
    *          versa (i.e. exchanges first octet for fourth, and second for third).
    * \param x The value.
    * \return The endianess swapped value.
    */
    inline boost::uint32_t swapBigLittleEndian(const boost::uint32_t& x)
    {
        return (x >> 24) |
               (x << 24) |
               ((x >> 8) & 0x0000ff00) |
               ((x << 8) & 0x00ff0000);
    }

    /**
    * \brief Swaps given 64 bit value from big endian to little endian and vice
    *          versa (i.e. exchanges first octet for eighth, second for seventh,
    *          third for sixth, and fourth for fifth).
    * \param x The value.
    * \return The endianess swapped value.
    */
    inline boost::uint64_t swapBigLittleEndian(const boost::uint64_t& x)
    {
        return (x >> 56) |
               (x << 56) |
               ((x >> 40) & 0x000000000000ff00) |
               ((x << 40) & 0x00ff000000000000) |
               ((x >> 24) & 0x0000000000ff0000) |
               ((x << 24) & 0x0000ff0000000000) |
               ((x >> 8)  & 0x00000000ff000000) |
               ((x << 8)  & 0x000000ff00000000);
    }


    /**
    * \brief Swaps given value from big endian to endianess of the system and
    *        vice versa.
    * \param x The big endian value.
    * \return The converted value.
    */
    template <typename type>
    inline type swapBigEndian(const type& x)
    {
#ifdef __LITTLE_ENDIAN__
        return swapBigLittleEndian(x);
#elif defined(__BIG_ENDIAN__)
        return x;
#else
#error Unsupported endianess: Define __LITTLE_ENDIAN__ or __BIG_ENDIAN__!
#endif
    }

    /**
    * \brief Swaps given value from little endian to endianess of the system
    *        and vice versa.
    * \param x The little endian value.
    * \return The converted value.
    */
    template <typename type>
    inline type swapLittleEndian(const type& x)
    {
#ifdef __LITTLE_ENDIAN__
        return x;
#elif defined(__BIG_ENDIAN__)
        swapBigLittleEndian(x);
#else
#error Unsupported endianess: Define __LITTLE_ENDIAN__ or __BIG_ENDIAN__!
#endif
    }

}

#endif
