/**
* \file HexPrint.cpp
* \brief Contains function definitions for printing data as hex strings.
*/

#include <iomanip>
#include <sstream>
#include <util/HexPrint.hpp>

using namespace bil;


void bil::printHex(std::ostream& os, boost::uint32_t word)
{
    // print word in hexadecimal representation with fixed width of 8 digits and
    // prefixed by 0x
    os << std::hex << std::setfill('0') << "0x" << std::setw(8) << word;
}


void bil::printHex(std::ostream& os, const boost::uint32_t* words, size_t wordCount)
{
    // print words in hexadecimal representation with fixed width of 8 digits
    // and prefixed by 0x
    os << std::hex << std::setfill('0');
    for (size_t i = 0; i < wordCount; ++i)
    {
        os << "0x" << std::setw(8) << *words++;
        if ((i+1) < wordCount) os << " ";
    }
}


std::string bil::hexString(boost::uint32_t word)
{
    // print word into a stringstream
    std::stringstream ss;
    printHex(ss, word);
    // return stringstream content
    return ss.str();
}


std::string bil::hexString(const boost::uint32_t* words, size_t wordCount)
{
    // print words into a stringstream
    std::stringstream ss;
    printHex(ss, words, wordCount);
    // return stringstream content
    return ss.str();
}