/**
* \file SyncWordRawData.hpp
* \brief Functions for handling sync word raw data.
*/

#pragma once
#ifndef BIL_SYNCWORDRAWDATA_HPP
#define BIL_SYNCWORDRAWDATA_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Tells if some data starts with a sync word.
    * \param words Pointer to data.
    * \param wordCount Number of data words.
    * \return Returns 1, if data starts with sync word. Otherwise returns 0.
    */
    size_t isSyncWord(const boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Writes out a sync word as raw data.
    * \param words Pointer to buffer to write into.
    * \param wordCount Number of words in buffer.
    * \return Returns 1, i.e. number of words written.
    * \throws .
    */
    size_t writeSyncWord(boost::uint32_t* words, size_t wordCount);

}

#endif
