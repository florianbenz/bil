/**
* \file V5CfgTileMapEntry.hpp
* \brief Contains declaration of V5CfgTileMapEntry class.
*/

#pragma once
#ifndef BIL_V5CFGTILEMAPENTRY_HPP
#define BIL_V5CFGTILEMAPENTRY_HPP

#include <boost/cstdint.hpp>


namespace bil {

    class V5Configuration;


    /**
    * \brief Denotes a tiles associated configuration data chunk.
    *
    * Every tile has got an associated data chunk in the whole configuration
    * data. This chunk is referenced by a number of frame addresses. For a
    * distinct tile the corresponding frame addresses only differ in their frame
    * index, making up a continuous range of frame addresses. Since a tile needs
    * not all data out of every frame, but a continuous range of its bits, this
    * range is also specified (by indexing its beginning and ending word).
    */
    struct V5CfgTileMapEntry {

        /**********************************************************************/
        /* ADDRESS PARTS EQUAL IN ALL CORRESPONDING FRAMES                    */
        /**********************************************************************/

        /// upper/lower flag of corresponding addresses
        bool lowerHalf;
        /// row index of corresponding addresses
        unsigned char rowIndex;
        /// column index of corresponding addresses
        unsigned char columnIndex;


        /**********************************************************************/
        /* CONTINOUS FRAME INDEX RANGE                                        */
        /**********************************************************************/

        /// lowest frame index of corresponding addresses
        unsigned char frameBeginIndex;
        /// highest frame index of corresponding addresses
        unsigned char frameEndIndex;


        /**********************************************************************/
        /* CONTINOUS WORD RANGE INSIDE ALL CORRESPONDING FRAMES               */
        /**********************************************************************/

        /// beginning word offset (in every frame)
        unsigned char wordBeginOffset;
        /// ending word offset (in every frame)
        unsigned char wordEndOffset;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all data fields to default values.
        */
        void clear();

    };


    /**
    * \brief Gets number of words a V5CfgTileMapEntry references.
    * \param where A V5CfgTileMapEntry referencing configuration data.
    * \return The number of words referenced.
    */
    size_t getCfgDataWordCount(const V5CfgTileMapEntry& where);

    /**
    * \brief Gets configuration data referenced by a V5CfgTileMapEntry.
    * \param data Address of buffer to copy in.
    * \param dataWordCount Size of buffer in words.
    * \param src The configuration data from which to copy.
    * \param where A V5CfgTileMapEntry referencing configuration data.
    * \return The number of words copied to given buffer.
    */
    size_t getCfgData(boost::uint32_t* data, size_t dataWordCount,
                      const V5Configuration& src, const V5CfgTileMapEntry& where);

}

#endif
