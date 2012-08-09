/**
* \file PIP.hpp
* \brief Contains declaration of PIP class.
*/

#pragma once
#ifndef BIL_PIP_HPP
#define BIL_PIP_HPP

#include <vector>
#include <serialization/PIPBS.hpp>
#include <xdlrc/model/PIPDirection.hpp>


namespace bil {

    /**
    * \brief A programmable interface point.
    *
    * This class describes a programmable interface point, in short PIP. PIPs
    * are located on tiles and represent a connection between a start and an end
    * wire, that can be activated or not by configuration. The direction of the
    * connection can vary. (In an XDLRC file, PIPs that connect an input/output
    * pin pair by connecting the corresponding pin wires are marked as route-
    * through, as they allow routing to go through a primitive site. Since this
    * information is redundant, it is omitted here. Because of similar reasons
    * the location of the PIP is omitted, too.)
    */
    class PIP {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PIP instance.
        */
        PIP();


        /**********************************************************************/
        /* START WIRE INDEX                                                   */
        /**********************************************************************/

        /**
        * \brief Sets index of start wire.
        * \param index Index of wire in superordinated TileType.
        */
        void startWireIndex(unsigned short index);

        /**
        * \brief Gets index of start wire.
        * \return Index of wire in superordinated TileType.
        */
        unsigned short startWireIndex() const;


        /**********************************************************************/
        /* END WIRE INDEX                                                     */
        /**********************************************************************/

        /**
        * \brief Sets index of end wire.
        * \param index Index of wire in superordinated TileType.
        */
        void endWireIndex(unsigned short index);

        /**
        * \brief Gets index of end wire.
        * \return Index of wire in superordinated TileType.
        */
        unsigned short endWireIndex() const;


        /**********************************************************************/
        /* DIRECTION                                                          */
        /**********************************************************************/

        /**
        * \brief Sets direction.
        * \param dir The new direction.
        */
        void direction(PIPDirection::direction_t dir);

        /**
        * \brief Gets direction.
        * \return The direction.
        */
        PIPDirection::direction_t direction() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend bool operator== (const PIP& pip1, const PIP& pip2);
        friend bool operator< (const PIP& pip1, const PIP& pip2);

        friend void writeBinary(const PIP& data, std::ostream& outputStream);
        friend void readBinary(PIP& data, std::istream& inputStream);

        unsigned short m_startWireIndex;
        unsigned short m_endWireIndex;
        PIPDirection::direction_t m_direction;

    };


    /// Tests two PIP instances for memberwise equality
    inline bool operator== (const PIP& pip1, const PIP& pip2)
    {
        if (pip1.m_startWireIndex != pip2.m_startWireIndex) return false;
        if (pip1.m_endWireIndex != pip2.m_endWireIndex) return false;
        return (pip1.m_direction == pip2.m_direction);
    }

    /// Tests two PIP instances for memberwise inequality
    inline bool operator!= (const PIP& pip1, const PIP& pip2)
    {
        return !(operator== (pip1, pip2));
    }


    /// Tests two PIP instances for memberwise <
    inline bool operator< (const PIP& pip1, const PIP& pip2)
    {
        if (pip1.m_startWireIndex != pip2.m_startWireIndex)
            return (pip1.m_startWireIndex < pip2.m_startWireIndex);
        if (pip1.m_endWireIndex != pip2.m_endWireIndex)
            return (pip1.m_endWireIndex < pip2.m_endWireIndex);
        return (pip1.m_direction < pip2.m_direction);
    }

    /// Tests two PIP instances for memberwise >
    inline bool operator> (const PIP& pip1, const PIP& pip2)
    {
        return (operator< (pip2, pip1));
    }

    /// Tests two PIP instances for memberwise <=
    inline bool operator<= (const PIP& pip1, const PIP& pip2)
    {
        return !(operator> (pip1, pip2));
    }

    /// Tests two PIP instances for memberwise >=
    inline bool operator>= (const PIP& pip1, const PIP& pip2)
    {
        return !(operator< (pip1, pip2));
    }


    /// An ordered list of PIPs.
    typedef std::vector<PIP> PIPs;

}

#endif
