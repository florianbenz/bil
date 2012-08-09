/**
* \file V5FrameAddressString.hpp
* \brief Contains string conversion functions for V5FrameAddress.
*/

#pragma once
#ifndef BIL_V5FRAMEADDRESSSTRING_HPP
#define BIL_V5FRAMEADDRESSSTRING_HPP

#include <string>


namespace bil {

    class V5FrameAddress;


    /**
    * \brief Gets a raw address string representation of the frame address.
    * \return Returns a hexadecimal string denoting the raw frame address.
    */
    std::string toRawAddressString(const V5FrameAddress& address);

    /**
    * \brief Gets a string expanded representation of the frame address.
    * \return Returns a string consisting of the five integer address parts
    *         separated by space.
    */
    std::string toExpandedString(const V5FrameAddress& address);

    /**
    * \brief Gets a symbolic string representation of the frame address.
    * \return Returns a string consisting of the five integer address parts
    *         separated by space, whereas the block index and the upper half
    *         flag are represented by names rather than integers.
    */
    std::string toSymbolicString(const V5FrameAddress& address);

}

#endif
