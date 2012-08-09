/**
* \file PrimitiveType.hpp
* \brief Contains declaration of PrimitiveType class.
*/

#pragma once
#ifndef BIL_PRIMITIVETYPE_HPP
#define BIL_PRIMITIVETYPE_HPP

#include <serialization/PrimitiveTypeBS.hpp>
#include <xdlrc/model/Element.hpp>
#include <xdlrc/model/Pin.hpp>


namespace bil {

    /**
    * \brief A primitive type.
    *
    * Primitives are a basic logic units of a certain type. The PrimitiveType
    * class describes such a type by providing its name, its pins (connecting
    * the primitive to the outside), and its list of elements (making up its
    * configurable parts).
    */
    class PrimitiveType {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PrimitiveType instance.
        */
        PrimitiveType();


        /**********************************************************************/
        /* TYPE NAME                                                          */
        /**********************************************************************/

        /**
        * \brief Gets type name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets type name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* PINS                                                               */
        /**********************************************************************/

        /**
        * \brief Gets pins.
        * \return The pins.
        */
        Pins& pins();

        /**
        * \brief Gets pins read only.
        * \return The pins.
        */
        const Pins& pins() const;


        /**********************************************************************/
        /* ELEMENTS                                                           */
        /**********************************************************************/

        /**
        * \brief Gets elements.
        * \return The elements.
        */
        Elements& elements();

        /**
        * \brief Gets elements read only.
        * \return The elements.
        */
        const Elements& elements() const;


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

        friend void writeBinary(const PrimitiveType& data, std::ostream& outputStream);
        friend void readBinary(PrimitiveType& data, std::istream& inputStream);

        std::string m_name;
        Pins m_pins;
        Elements m_elements;
        size_t m_tag;

    };

    /// An ordered list of primitive types.
    typedef std::vector<PrimitiveType> PrimitiveTypes;

}

#endif
