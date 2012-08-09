/**
* \file BuswidthPatternRawData.hpp
* \brief Functions for handling buswidth pattern raw data.
*/

#pragma once
#ifndef BIL_BUSWIDTHPATTERNRAWDATA_HPP
#define BIL_BUSWIDTHPATTERNRAWDATA_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Tells if some data starts with a buswidth pattern.
    * \param words Pointer to data.
    * \param wordCount Number of data words.
    * \return Returns 2, if data starts with buswidth pattern, 0 otherwise.
    */
    size_t isBuswidthPattern(const boost::uint32_t* words, size_t wordCount);


    /**
    * \brief Writes out a buswidth pattern as raw data.
    * \param words Pointer to buffer to write into.
    * \param wordCount Number of words in buffer.
    * \return Returns 2, i.e. number of words written.
    * \throws .
    */
    size_t writeBuswidthPattern(boost::uint32_t* words, size_t wordCount);

}

#endif
