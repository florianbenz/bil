/**
* \file CfgExtractor.hpp
* \brief Contains declaration of CfgExtractor class.
*/

#pragma once
#ifndef BIL_CFGEXTRACTOR_HPP
#define BIL_CFGEXTRACTOR_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Extracts data from configuration.
    *
    * This base class provides an interface for extracting data belonging to a
    * distinct tile out of the whole device configuration data.
    */
    class CfgExtractor {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Destructs a CfgExtractor instance.
        */
        virtual ~CfgExtractor();


        /**********************************************************************/
        /* DATA EXTRACTION                                                    */
        /**********************************************************************/

        /**
        * \brief Gets number of associated data words of a distinct tile.
        * \param row Row position of tile.
        * \param column Column position of tile.
        * \return The number of data words.
        */
        virtual size_t getDataWordCount(unsigned row, unsigned column) const = 0;

        /**
        * \brief Gets associated data words of a distinct tile.
        * \param row Row position of tile.
        * \param column Column position of tile.
        * \param data Pointer to buffer for data words.
        * \param dataWordCount Size of data word buffer.
        * \return The number of retrieved data words.
        * \throws .
        */
        virtual size_t getDataWords(unsigned row, unsigned column, boost::uint32_t* data, size_t dataWordCount) const = 0;

    };

}

#endif
