/**
* \file Tile.hpp
* \brief Contains declaration of Tile class.
*/

#pragma once
#ifndef BIL_TILE_HPP
#define BIL_TILE_HPP

#include <serialization/TileBS.hpp>
#include <xdlrc/model/PrimitiveSite.hpp>


namespace bil {

    /**
    * \brief Per instance data of tiles.
    *
    * The tile entity in XDLRC is broken up into two classes: Tile and TileType.
    * The Tile class stores data belonging to a distinct tile. It contains its
    * name, its primitive sites, its tile position, its site position, and its
    * type index. The tile position determines a place on the regular 2D-grid of
    * tiles the device is made of. Besides this there is another spatial
    * ordering scheme called sites. Site are the rectangular areas on the FPGA,
    * which are bounded by surrounding wire channels. They are not directly
    * mentioned in XDLRC, but tile names carry the coordinates of their
    * containing site. Every site includes a number of tiles of different types.
    */
    class Tile {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Tile instance.
        */
        Tile();


        /**********************************************************************/
        /* TILE NAME                                                          */
        /**********************************************************************/

        /**
        * \brief Gets tile name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets tile name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* PRIMITIVE SITE INSTANCES                                           */
        /**********************************************************************/

        /**
        * \brief Gets primitive sites.
        * \return The sites.
        */
        PrimitiveSites& primitiveSites();

        /**
        * \brief Gets primitive sites read only.
        * \return The sites.
        */
        const PrimitiveSites& primitiveSites() const;


        /**********************************************************************/
        /* POSITION IN TILE GRID                                              */
        /**********************************************************************/

        /**
        * \brief Sets tile row.
        * \param row The new row.
        */
        void row(unsigned short row);

        /**
        * \brief Gets tile row.
        * \return The row.
        */
        unsigned short row() const;

        /**
        * \brief Sets tile column.
        * \param column The new column.
        */
        void column(unsigned short column);

        /**
        * \brief Gets tile column.
        * \return The column.
        */
        unsigned short column() const;


        /**********************************************************************/
        /* POSITION IN SITE GRID                                              */
        /**********************************************************************/

        /**
        * \brief Sets site x-position.
        * \param x The new x-position.
        */
        void siteX(unsigned short x);

        /**
        * \brief Gets site x-position.
        * \return The x-position.
        */
        unsigned short siteX() const;

        /**
        * \brief Sets site y-position.
        * \param y The new y-position.
        */
        void siteY(unsigned short y);

        /**
        * \brief Gets site y-position.
        * \return The y-position.
        */
        unsigned short siteY() const;


        /**********************************************************************/
        /* TILE TYPE INDEX                                                    */
        /**********************************************************************/

        /**
        * \brief Sets index of TileType.
        * \param index Index of TileType in corresponding Device.
        */
        void typeIndex(unsigned short index);

        /**
        * \brief Gets index of TileType.
        * \return Index of TileType in corresponding Device.
        */
        unsigned short typeIndex() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const Tile& data, std::ostream& outputStream);
        friend void readBinary(Tile& data, std::istream& inputStream);

        std::string m_name;
        PrimitiveSites m_primitiveSites;
        unsigned short m_row;
        unsigned short m_column;
        unsigned short m_siteX;
        unsigned short m_siteY;
        unsigned short m_typeIndex;

    };

    /// An ordered list of tiles.
    typedef std::vector<Tile> Tiles;

}

#endif
