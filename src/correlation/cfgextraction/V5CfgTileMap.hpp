/**
* \file V5CfgTileMap.hpp
* \brief Contains declaration of V5CfgTileMap class.
*/

#pragma once
#ifndef BIL_V5CFGTILEMAP_HPP
#define BIL_V5CFGTILEMAP_HPP

#include <cstring>
#include <vector>
#include <correlation/cfgextraction/V5CfgTileMapEntry.hpp>
#include <serialization/V5CfgTileMapBS.hpp>


namespace bil {

    /**
    * \brief Holds V5CfgTileMapEntry instances for a grid of tiles.
    *
    * A 2-dimensional container for V5CfgTileMapEntry instances. Every grid
    * position holds a V5CfgTileMapEntry instance for the corresponding tile.
    */
    class V5CfgTileMap {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5CfgTileMap instance.
        */
        V5CfgTileMap();


        /**********************************************************************/
        /* TILE ENTRY LOOKUP                                                  */
        /**********************************************************************/

        /**
        * \brief Gets the number of tile rows.
        * \return The row count.
        */
        unsigned rowCount() const;

        /**
        * \brief Gets the number of tile columns.
        * \return The column count.
        */
        unsigned columnCount() const;

        /**
        * \brief Gets V5CfgTileMapEntry for specified tile position.
        * \param row Row of tile.
        * \param column Column of tile.
        * \return The V5CfgTileMapEntry instance.
        * \throws .
        */
        V5CfgTileMapEntry& entries(unsigned row, unsigned column);

        /**
        * \brief Gets V5CfgTileMapEntry for specified tile position read only.
        * \param row Row of tile.
        * \param column Column of tile.
        * \return The V5CfgTileMapEntry instance.
        * \throws .
        */
        const V5CfgTileMapEntry& entries(unsigned row, unsigned column) const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resize the tile grid.
        * \details Resizing the grid will reset all contained data.
        * \param rowCount The new row number of tiles.
        * \param columnCount The new column number of tiles.
        */
        void resize(unsigned rowCount, unsigned columnCount);

        /**
        * \brief Empties tile grid and erases all data.
        */
        void clear();


    private:

        friend void writeBinary(const V5CfgTileMap& data, std::ostream& outputStream);
        friend void readBinary(V5CfgTileMap& data, std::istream& inputStream);

        unsigned m_rowCount;
        unsigned m_columnCount;
        std::vector<V5CfgTileMapEntry> m_entries;

    };

}

#endif
