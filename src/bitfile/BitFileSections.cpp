/**
* \file BitFileSections.cpp
* \brief Contains definition of bitfile section constants.
*/

#include <bitfile/BitFileSections.hpp>


const boost::uint8_t bil::BITFILE_HEADER[BITFILE_HEADER_SIZE] =
{
    // length of following magic word (9 bytes)
    0x00, 0x09,
    // magic word
    0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x0f, 0xf0, 0x00,
    // length of section keys (1 byte)
    0x00, 0x01
};