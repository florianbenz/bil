/**
* \file PrimitiveSiteType.hpp
* \brief Contains declaration of PrimitiveSiteType class.
*/

#pragma once
#ifndef BIL_PRIMITIVESITETYPE_HPP
#define BIL_PRIMITIVESITETYPE_HPP

#include <serialization/PrimitiveSiteTypeBS.hpp>
#include <xdlrc/model/PinWire.hpp>


namespace bil {

    /**
    * \brief Per TileType data of a primitive site.
    *
    * The primitive site entity in XDLRC is broken up into two classes:
    * PrimitiveSite and PrimitiveSiteType. The PrimitiveSiteType class stores
    * common data of primitive sites located on tiles of a distinct type. This
    * includes the primitive type of the site and the connections from tile
    * wires to primitive pins. By storing this data per tile type and not per
    * tile, data space requirements are decreased drastically.
    */
    class PrimitiveSiteType {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PrimitiveSiteType instance.
        */
        PrimitiveSiteType();


        /**********************************************************************/
        /* PRIMITIVE TYPE INDEX                                               */
        /**********************************************************************/

        /**
        * \brief Sets index of this site's primitive type.
        * \param index Index of PrimitiveType in corresponding Device.
        */
        void primitiveTypeIndex(unsigned short index);

        /**
        * \brief Gets index of this site's primitive type.
        * \return Index of PrimitiveType in corresponding Device.
        */
        unsigned short primitiveTypeIndex() const;


        /**********************************************************************/
        /* PIN WIRES                                                          */
        /**********************************************************************/

        /**
        * \brief Gets pin wires.
        * \return The pin wires.
        */
        PinWires& pinWires();

        /**
        * \brief Gets pin wires read only.
        * \return The pin wires.
        */
        const PinWires& pinWires() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const PrimitiveSiteType& data, std::ostream& outputStream);
        friend void readBinary(PrimitiveSiteType& data, std::istream& inputStream);

        PinWires m_pinWires;
        unsigned short m_primitiveTypeIndex;

    };

    /// An ordered list of primitive site types.
    typedef std::vector<PrimitiveSiteType> PrimitiveSiteTypes;

}

#endif
