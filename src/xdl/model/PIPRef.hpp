/**
* \file PIPRef.hpp
* \brief Contains declaration of PIPRef class.
*/

#pragma once
#ifndef BIL_PIPREF_HPP
#define BIL_PIPREF_HPP

#include <cstring>
#include <vector>


namespace bil {

    /**
    * \brief References a PIP on a distinct tile.
    *
    * In a XDL design this class is used to denote activated PIPs. It contains
    * one index to the tile the PIP is on, and one index to the PIP itself.
    */
    class PIPRef {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PIPRef instance.
        */
        PIPRef();


        /**********************************************************************/
        /* TILE INDEX                                                         */
        /**********************************************************************/

        /**
        * \brief Sets tile the PIP is on.
        * \param index Index of a Tile in a Device.
        */
        void tileIndex(size_t index);

        /**
        * \brief Gets index of tile the PIP is on.
        * \return Index of a Tile in a Device.
        */
        size_t tileIndex() const;


        /**********************************************************************/
        /* PIP INDEX                                                          */
        /**********************************************************************/

        /**
        * \brief Sets index of PIP.
        * \param index Index of PIP in corresponding TileType.
        */
        void pipIndex(size_t index);

        /**
        * \brief Gets index of PIP.
        * \return Index of PIP in corresponding TileType.
        */
        size_t pipIndex() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend bool operator== (const PIPRef& ref1, const PIPRef& ref2);
        friend bool operator< (const PIPRef& ref1, const PIPRef& ref2);

        size_t m_tileIndex;
        size_t m_pipIndex;

    };


    /// Tests two PIPRef instances for memberwise equality
    inline bool operator== (const PIPRef& ref1, const PIPRef& ref2)
    {
        if (ref1.m_tileIndex != ref2.m_tileIndex) return false;
        return ref1.m_pipIndex == ref2.m_pipIndex;
    }

    /// Tests two PIPRef instances for memberwise inequality
    inline bool operator!= (const PIPRef& ref1, const PIPRef& ref2)
    {
        return !(operator== (ref1, ref2));
    }


    /// Tests two PIPRef instances for memberwise <
    inline bool operator< (const PIPRef& ref1, const PIPRef& ref2)
    {
        if (ref1.m_tileIndex != ref2.m_tileIndex)
            return ref1.m_tileIndex < ref2.m_tileIndex;
        return ref1.m_pipIndex < ref2.m_pipIndex;
    }

    /// Tests two PIPRef instances for memberwise >
    inline bool operator> (const PIPRef& ref1, const PIPRef& ref2)
    {
        return (operator< (ref2, ref1));
    }

    /// Tests two PIPRef instances for memberwise <=
    inline bool operator<= (const PIPRef& ref1, const PIPRef& ref2)
    {
        return !(operator> (ref1, ref2));
    }

    /// Tests two PIPRef instances for memberwise >=
    inline bool operator>= (const PIPRef& ref1, const PIPRef& ref2)
    {
        return !(operator< (ref1, ref2));
    }


    /// An ordered list of PIPRefs.
    typedef std::vector<PIPRef> PIPRefs;

}

#endif
