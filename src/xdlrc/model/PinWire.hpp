/**
* \file PinWire.hpp
* \brief Contains declaration of PinWire class.
*/

#pragma once
#ifndef BIL_PINWIRE_HPP
#define BIL_PINWIRE_HPP

#include <vector>
#include <serialization/PinWireBS.hpp>


namespace bil {

    /**
    * \brief Attaches a tile wire to a pin of a primitive site.
    *
    * All pins of a primitive site are connected to the wires of containing tile
    * with the help of this class.
    */
    class PinWire {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PinWire instance.
        */
        PinWire();


        /**********************************************************************/
        /* WIRE INDEX                                                         */
        /**********************************************************************/

        /**
        * \brief Sets index of wire to connect to.
        * \param index Index of wire in superordinated TileType.
        */
        void wireIndex(unsigned short index);

        /**
        * \brief Gets index of wire to connect to.
        * \return Index of wire in superordinated TileType.
        */
        unsigned short wireIndex() const;


        /**********************************************************************/
        /* PIN INDEX                                                          */
        /**********************************************************************/

        /**
        * \brief Sets index of pin to connect to.
        * \param index Index of pin in corresponding PrimitiveDefinition.
        */
        void pinIndex(unsigned short index);

        /**
        * \brief Gets index of pin to connect to.
        * \return Index of pin in corresponding PrimitiveDefinition.
        */
        unsigned short pinIndex() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend bool operator== (const PinWire& pw1, const PinWire& pw2);

        friend void writeBinary(const PinWire& data, std::ostream& outputStream);
        friend void readBinary(PinWire& data, std::istream& inputStream);

        unsigned short m_wireIndex;
        unsigned short m_pinIndex;

    };

    /// Tests two PinWire instances for memberwise equality
    inline bool operator== (const PinWire& pw1, const PinWire& pw2)
    {
        if (pw1.m_wireIndex != pw2.m_wireIndex) return false;
        return (pw1.m_pinIndex == pw2.m_pinIndex);
    }

    /// Tests two PinWire instances for memberwise inequality
    inline bool operator!= (const PinWire& pw1, const PinWire& pw2)
    {
        return !(operator== (pw1, pw2));
    }


    /// An ordered list of pin wires.
    typedef std::vector<PinWire> PinWires;

}

#endif
