/**
* \file TileType.hpp
* \brief Contains declaration of TileType class.
*/

#pragma once
#ifndef BIL_TILETYPE_HPP
#define BIL_TILETYPE_HPP

#include <serialization/TileTypeBS.hpp>
#include <xdlrc/model/PIP.hpp>
#include <xdlrc/model/PrimitiveSiteType.hpp>
#include <xdlrc/model/Wire.hpp>


namespace bil {

    /**
    * \brief Tile type data.
    *
    * The tile entity in XDLRC is broken up into two classes: Tile and TileType.
    * The TileType class stores common data of tiles belonging to a distinct
    * type. This drastically decreases memory requirements, since the common
    * data is stored once in a TileType instance, instead storing them over and
    * over in every Tile instance.
    */
    class TileType {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new TileType instance.
        */
        TileType();


        /**********************************************************************/
        /* TYPE NAME                                                          */
        /**********************************************************************/

        /**
        * \brief Gets type name.
        * \return The type name.
        */
        std::string& name();

        /**
        * \brief Gets type name read only.
        * \return The type name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* PRIMITIVE SITE TYPES                                               */
        /**********************************************************************/

        /**
        * \brief Gets primitive site types.
        * \return The primitive site types.
        */
        PrimitiveSiteTypes& siteTypes();

        /**
        * \brief Gets primitive site types read only.
        * \return The primitive site types.
        */
        const PrimitiveSiteTypes& siteTypes() const;


        /**********************************************************************/
        /* WIRES                                                              */
        /**********************************************************************/

        /**
        * \brief Gets all tile wires.
        * \return The wires.
        */
        Wires& wires();

        /**
        * \brief Gets all tile wires read only.
        * \return The wires.
        */
        const Wires& wires() const;


        /**********************************************************************/
        /* PIPS                                                               */
        /**********************************************************************/

        /**
        * \brief Gets all PIPs.
        * \return The PIPs.
        */
        PIPs& pips();

        /**
        * \brief Gets all PIPs read only.
        * \return The PIPs.
        */
        const PIPs& pips() const;


        /**********************************************************************/
        /* MULTI-PURPOSE-TAG                                                  */
        /**********************************************************************/

        /**
        * \brief Gets tag.
        * \param t The tag.
        */
        void tag(size_t t);

        /**
        * \brief Gets tag.
        * \return The tag.
        */
        size_t tag() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const TileType& data, std::ostream& outputStream);
        friend void readBinary(TileType& data, std::istream& inputStream);

        std::string m_name;
        PrimitiveSiteTypes m_siteTypes;
        Wires m_wires;
        PIPs m_pips;
        size_t m_tag;

    };

    /// An ordered list of tile types.
    typedef std::vector<TileType> TileTypes;

}

#endif
