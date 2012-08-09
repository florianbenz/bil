/**
* \file BuswidthPatternRawData.cpp
* \brief Functions for handling buswidth pattern raw data.
*/

#include <bitstream/BuswidthPatternRawData.hpp>
#include <exception/Exception.hpp>

using namespace bil;


const size_t BUSWIDTH_PATTERN_SIZE = 2;
const boost::uint32_t BUSWIDTH_WORD1 = 0x000000bb;
const boost::uint32_t BUSWIDTH_WORD2 = 0x11220044;


size_t bil::isBuswidthPattern(const boost::uint32_t* words, size_t wordCount)
{
    // test if data is large enough
    if (BUSWIDTH_PATTERN_SIZE > wordCount) return 0;
    // test if both words are correct
    if (BUSWIDTH_WORD1 != *words++) return 0;
    if (BUSWIDTH_WORD2 != *words) return 0;
    // buswidth pattern raw data found, return its size
    return BUSWIDTH_PATTERN_SIZE;
}


size_t bil::writeBuswidthPattern(boost::uint32_t* words, size_t wordCount)
{
    // check if buffer is large enough
    if (BUSWIDTH_PATTERN_SIZE > wordCount) throw Exception();
    // write buswidth pattern
    *words++ = BUSWIDTH_WORD1;
    *words = BUSWIDTH_WORD2;
    // return written size
    return BUSWIDTH_PATTERN_SIZE;
}