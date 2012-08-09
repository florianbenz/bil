/**
* \file TileLookup2D.hpp
* \brief Contains declaration of TileLookup2D class.
*/

#pragma once
#ifndef BIL_TILELOOKUP2D_HPP
#define BIL_TILELOOKUP2D_HPP

#include <cstring>
#include <vector>


namespace bil {

    class Device;
    class Tile;


    /**
    * \brief A 2-dimensional lookup for tiles.
    *
    * This class helps for fast look up of tiles inside a Device instance by
    * their row and column position. It is a simple read-only lookup, and if
    * the tiles are changed from outside, the lookup must be rebuild in order to
    * work correct.
    */
    class TileLookup2D {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new TileLookup2D instance.
        */
        TileLookup2D();


        /**********************************************************************/
        /* TILE LOOKUP                                                        */
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
        * \brief Gets the tile at specified position read only.
        * \param row Row of tile.
        * \param column Column of tile.
        * \return Pointer to tile, if there is a tile at that position.
        */
        const Tile* lookup(unsigned row, unsigned column) const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Rebuilds the lookup.
        * \param device The device instance which tiles will be used.
        */
        void reset(const Device& device);

        /**
        * \brief Empties the lookup.
        */
        void clear();


    private:

        unsigned m_rowCount;
        unsigned m_columnCount;
        std::vector<const Tile*> m_tiles;

    };

}

#endif
