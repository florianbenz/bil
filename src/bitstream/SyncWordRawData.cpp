/**
* \file SyncWordRawData.cpp
* \brief Functions for handling sync word raw data.
*/

#include <bitstream/SyncWordRawData.hpp>
#include <exception/Exception.hpp>

using namespace bil;


const size_t SYNCHRO_WORD_SIZE = 1;
const boost::uint32_t SYNCHRO_WORD = 0xaa995566;


size_t bil::isSyncWord(const boost::uint32_t* words, size_t wordCount)
{
    // test if data is large enough
    if (SYNCHRO_WORD_SIZE > wordCount) return 0;
    // test if sync word is correct
    if (SYNCHRO_WORD != *words) return 0;
    // sync word raw data found, return its size
    return SYNCHRO_WORD_SIZE;
}


size_t bil::writeSyncWord(boost::uint32_t* words, size_t wordCount)
{
    // check if buffer is large enough
    if (SYNCHRO_WORD_SIZE > wordCount) throw Exception();
    // write sync word
    *words = SYNCHRO_WORD;
    // return written size
    return SYNCHRO_WORD_SIZE;
}