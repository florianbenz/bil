/**
* \file WireConnection.hpp
* \brief Contains declaration of WireConnection class.
*/

#pragma once
#ifndef BIL_WIRECONNECTION_HPP
#define BIL_WIRECONNECTION_HPP

#include <vector>
#include <serialization/WireConnectionBS.hpp>


namespace bil {

    /**
    * \brief A connection to a wire on a tile.
    *
    * This class describes the destination of a connection: a distinct wire on a
    * distinct tile. In an XDLRC file, these two are given by name. But this is
    * changed in here to a more flexible representation that allows storing the
    * WireConnections only per tile type (instead for every single tile!). The
    * destination wire is given by indexing the wire list of the destination
    * tile type; an index to this tile type is also stored. A coordinate pair
    * measuring the distance from connection origin to destination site (sic!)
    * tells about the spatial relationship. Since there is at most only one tile
    * of a distinct type on a site, the destination tile is unambiguous.
    */
    class WireConnection {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new WireConnection instance.
        */
        WireConnection();


        /**********************************************************************/
        /* DESTINATION SITE OFFSET                                            */
        /**********************************************************************/

        /**
        * \brief Sets x offset to destination site.
        * \param offset The new x offset.
        */
        void xOffset(short offset);

        /**
        * \brief Gets x offset to destination site.
        * \return The x offset.
        */
        short xOffset() const;


        /**
        * \brief Sets y offset to destination site.
        * \param offset The new y offset.
        */
        void yOffset(short offset);

        /**
        * \brief Gets y offset to destination site.
        * \return The y offset.
        */
        short yOffset() const;


        /**********************************************************************/
        /* DESTINATION TILE TYPE INDEX                                        */
        /**********************************************************************/

        /**
        * \brief Sets index of destination TileType.
        * \param index Index of TileType in corresponding Device.
        */
        void tileTypeIndex(unsigned short index);

        /**
        * \brief Gets index of destination TileType.
        * \return Index of TileType in corresponding Device.
        */
        unsigned short tileTypeIndex() const;


        /**********************************************************************/
        /* DESTINATION WIRE INDEX                                             */
        /**********************************************************************/

        /**
        * \brief Sets index of destination wire.
        * \param index Index of wire in destination TileType.
        */
        void wireIndex(unsigned short index);

        /**
        * \brief Gets index of destination wire.
        * \return Index of wire in destination TileType.
        */
        unsigned short wireIndex() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend bool operator== (const WireConnection& c1, const WireConnection& c2);

        friend void writeBinary(const WireConnection& data, std::ostream& outputStream);
        friend void readBinary(WireConnection& data, std::istream& inputStream);

        short m_xOffset;
        short m_yOffset;
        unsigned short m_tileTypeIndex;
        unsigned short m_wireIndex;

    };


    /// Tests two WireConnection instances for memberwise equality
    inline bool operator== (const WireConnection& c1, const WireConnection& c2)
    {
        if (c1.m_xOffset != c2.m_xOffset) return false;
        if (c1.m_yOffset != c2.m_yOffset) return false;
        if (c1.m_tileTypeIndex != c2.m_tileTypeIndex) return false;
        return (c1.m_wireIndex == c2.m_wireIndex);
    }

    /// Tests two WireConnection instances for memberwise inequality
    inline bool operator!= (const WireConnection& c1, const WireConnection& c2)
    {
        return !(operator== (c1, c2));
    }


    /// An ordered list of connections.
    typedef std::vector<WireConnection> WireConnections;

}

#endif
