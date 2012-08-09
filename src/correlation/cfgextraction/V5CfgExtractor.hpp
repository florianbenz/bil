/**
* \file V5CfgExtractor.hpp
* \brief Contains declaration of V5CfgExtractor class.
*/

#pragma once
#ifndef BIL_V5CFGEXTRACTOR_HPP
#define BIL_V5CFGEXTRACTOR_HPP

#include <correlation/cfgextraction/CfgExtractor.hpp>


namespace bil {

    class V5CfgTileMap;
    class V5Configuration;


    /**
    * \brief Extracts data from a Virtex-5 configuration.
    */
    class V5CfgExtractor: public CfgExtractor {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a CfgExtractor instance.
        * \param configuration Configuration from which to extract.
        * \param cfgTileMap Configuration tile map used for determining the data
        *                   portions for every tile.
        */
        V5CfgExtractor(const V5Configuration& configuration, const V5CfgTileMap& cfgTileMap);


        /**********************************************************************/
        /* DATA EXTRACTION                                                    */
        /**********************************************************************/

        /**
        * \brief Gets number of associated data words of a distinct tile.
        * \param row Row position of tile.
        * \param column Column position of tile.
        * \return The number of data words.
        */
        virtual size_t getDataWordCount(unsigned row, unsigned column) const;

        /**
        * \brief Gets associated data words of a distinct tile.
        * \param row Row position of tile.
        * \param column Column position of tile.
        * \param data Pointer to buffer for data words.
        * \param dataWordCount Size of data word buffer.
        * \return The number of retrieved data words.
        * \throws .
        */
        virtual size_t getDataWords(unsigned row, unsigned column, boost::uint32_t* data, size_t dataWordCount) const;


    private:

        const V5Configuration* m_configuration;
        const V5CfgTileMap* m_cfgTileMap;

    };

}

#endif
