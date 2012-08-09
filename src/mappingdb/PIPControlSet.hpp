/**
* \file PIPControlSet.hpp
* \brief Contains declaration of PIPControlSet class.
*/

#pragma once
#ifndef BIL_PIPCONTROLSET_HPP
#define BIL_PIPCONTROLSET_HPP

#include <mappingdb/PIPBitValue.hpp>
#include <serialization/PIPControlSetBS.hpp>


namespace bil {

    typedef std::vector<size_t> BitPositions;


    /**
    * \brief A set of interdependent PIPs.
    *
    * A PIPControlSet contains a set of interdependent PIPs, that share
    * configuration bits (instead of having one bit for one PIP). The
    * PIPControlSet contains two lists: A list with its PIPs and their bit
    * values, and a list containing the positions of used configuration bits.
    */
    class PIPControlSet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PIPControlSet instance.
        */
        PIPControlSet();


        /**********************************************************************/
        /* BIT POSITIONS                                                      */
        /**********************************************************************/

        /**
        * \brief Gets the positions of associated configuration bits.
        * \return The bit positions.
        */
        BitPositions& bitPositions();

        /**
        * \brief Gets the positions of associated configuration bits read only.
        * \return The bit positions.
        */
        const BitPositions& bitPositions() const;


        /**********************************************************************/
        /* PIP BIT VALUES                                                     */
        /**********************************************************************/

        /**
        * \brief Gets values of all bits for every PIP.
        * \return The bit values.
        */
        PIPBitValues& pipBitValues();

        /**
        * \brief Gets values of all bits for every PIP read only.
        * \return The bit values.
        */
        const PIPBitValues& pipBitValues() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const PIPControlSet& data, std::ostream& outputStream);
        friend void readBinary(PIPControlSet& data, std::istream& inputStream);

        BitPositions m_bitPositions;
        PIPBitValues m_pipBitValues;

    };


    /// A list of PIPControlSet instances
    typedef std::vector<PIPControlSet> PIPControlSets;

}

#endif
