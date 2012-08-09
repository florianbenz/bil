/**
* \file Device.hpp
* \brief Contains declaration of Device class.
*/

#pragma once
#ifndef BIL_DEVICE_HPP
#define BIL_DEVICE_HPP

#include <serialization/DeviceBS.hpp>
#include <xdlrc/model/PrimitiveType.hpp>
#include <xdlrc/model/Tile.hpp>
#include <xdlrc/model/TileType.hpp>


namespace bil {

    /**
    * \brief Models the topmost XDLRC entity.
    *
    * XDLRC data is a hierarchical tree structure of distinct entities carrying
    * data. The Device class models the root of this tree containing the Tiles,
    * TileTypes, and PrimitiveTypes subtrees. The structure is mostly the same
    * as found in an XDLRC file, with some adjustments for much less memory
    * requirements and simpler traversal.
    */
    class Device {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Device instance.
        */
        Device();


        /**********************************************************************/
        /* DEVICE NAME                                                        */
        /**********************************************************************/

        /**
        * \brief Gets device name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets device name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* TILES                                                              */
        /**********************************************************************/

        /**
        * \brief Gets tiles.
        * \return The tiles.
        */
        Tiles& tiles();

        /**
        * \brief Gets tiles read only.
        * \return The tiles.
        */
        const Tiles& tiles() const;


        /**
        * \brief Gets maximum row index found in all tiles.
        * \return The maximum row index.
        */
        unsigned maxRowIndex() const;

        /**
        * \brief Gets maximum column index found in all tiles.
        * \return The maximum column index.
        */
        unsigned maxColumnIndex() const;


        /**********************************************************************/
        /* TILE TYPES                                                         */
        /**********************************************************************/

        /**
        * \brief Gets tile types.
        * \return The tile types.
        */
        TileTypes& tileTypes();

        /**
        * \brief Gets tile types read only.
        * \return The tile types.
        */
        const TileTypes& tileTypes() const;


        /**********************************************************************/
        /* PRIMITIVE TYPES                                                    */
        /**********************************************************************/

        /**
        * \brief Gets primitive types.
        * \return The primitive types.
        */
        PrimitiveTypes& primitiveTypes();

        /**
        * \brief Gets primitive types read only.
        * \return The primitive types.
        */
        const PrimitiveTypes& primitiveTypes() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const Device& data, std::ostream& outputStream);
        friend void readBinary(Device& data, std::istream& inputStream);

        std::string m_name;
        Tiles m_tiles;
        TileTypes m_tileTypes;
        PrimitiveTypes m_primitiveTypes;

    };

}

#endif
