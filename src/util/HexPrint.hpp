/**
* \file HexPrint.hpp
* \brief Contains function declarations for printing data as hex strings.
*/

#pragma once
#ifndef BIL_HEXPRINT_HPP
#define BIL_HEXPRINT_HPP

#include <cstring>
#include <ostream>
#include <string>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Prints a 32 bit word in hexadecimal representation to a stream.
    * \details The hexadecimal representation will have a fixed width of 8
    *          digits (unused digits will be zero) and be prefixed with 0x.
    * \param os Stream to print in.
    * \param word Word to print.
    */
    void printHex(std::ostream& os, boost::uint32_t word);

    /**
    * \brief Prints 32 bit words in hexadecimal representation to a stream.
    * \details The hexadecimal representation will have a fixed width of 8
    *          digits (unused digits will be zero) and be prefixed with 0x.
    * \param os Stream to print in.
    * \param words Pointer to words to print.
    * \param wordCount Number of words to print.
    */
    void printHex(std::ostream& os, const boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Gets hexadecimal string representation of a 32 bit word.
    * \details The hexadecimal representation will have a fixed width of 8
    *          digits (unused digits will be zero) and be prefixed with 0x.
    * \param word Word to print.
    * \return The hexadecimal string.
    */
    std::string hexString(boost::uint32_t word);

    /**
    * \brief Gets hexadecimal string representation of 32 bit words.
    * \details The hexadecimal representation will have a fixed width of 8
    *          digits (unused digits will be zero) and be prefixed with 0x.
    * \param words Pointer to words to print.
    * \param wordCount Number of words to print.
    * \return The hexadecimal string.
    */
    std::string hexString(const boost::uint32_t* words, size_t wordCount);

}

#endif
