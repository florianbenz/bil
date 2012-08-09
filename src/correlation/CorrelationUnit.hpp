/**
* \file CorrelationUnit.hpp
* \brief Contains declaration of CorrelationUnit class.
*/

#pragma once
#ifndef BIL_CORRELATIONUNIT_HPP
#define BIL_CORRELATIONUNIT_HPP

#include <vector>
#include <boost/cstdint.hpp>
#include <boost/dynamic_bitset.hpp>


namespace bil {

    /**
    * \brief Holds a data unit for correlation.
    *
    * An instance of this class holds a data pair for correlation, consisting of
    * a tile's known data and unknown data. The known data part is a bitset
    * denoting the activated PIPs for that tile (stemming for example from a XDL
    * design). The unknown data part is the binary configuration data from the
    * corresponding configuration frames and is also stored in a bitset.
    *
    * Todo: Should later be extended to cover also the configuration options of
    * the tile's primitive sites.
    */
    class CorrelationUnit {
    public:

        /**********************************************************************/
        /* PIP BITSET                                                         */
        /**********************************************************************/

        /**
        * \brief Sets the number of PIP bits.
        * \param size The number of bits.
        */
        void pipBitSize(size_t size);

        /**
        * \brief Gets the number of PIP bits.
        * \return The number of bits.
        */
        size_t pipBitSize() const;


        /**
        * \brief Sets a PIP bit to 1.
        * \param index Index of the bit to set.
        */
        void setPIPBit(size_t index);

        /**
        * \brief Sets a PIP bit to 0.
        * \param index Index of the bit to set.
        */
        void resetPIPBit(size_t index);

        /**
        * \brief Sets all PIP bits to 1.
        */
        void setPIPBits();

        /**
        * \brief Sets all PIP bits to 0.
        */
        void resetPIPBits();


        /**
        * \brief Gets a PIP bit.
        * \param index Index of bit.
        * \return True, if denoted bit is set, false otherwise.
        */
        bool testPIPBit(size_t index) const;

        /**
        * \brief Tells if the PIP bits resemble an isolated PIP.
        * \return True, if 1 PIP bit is set, false otherwise.
        */
        bool isIsolated() const;


        /**********************************************************************/
        /* CONFIGURATION DATA BITSET                                          */
        /**********************************************************************/

        /**
        * \brief Sets the number of configuration data bits.
        * \param size The number of bits.
        */
        void cfgBitSize(size_t size);

        /**
        * \brief Gets the number of configuration data bits.
        * \return The number of bits.
        */
        size_t cfgBitSize() const;


        /**
        * \brief Sets a configuration data bit to 1.
        * \param index Index of the bit to set.
        */
        void setCfgBit(size_t index);

        /**
        * \brief Sets a configuration data bit to 0.
        * \param index Index of the bit to set.
        */
        void resetCfgBit(size_t index);

        /**
        * \brief Sets all configuration data bits to 1.
        */
        void setCfgBits();

        /**
        * \brief Sets all configuration data bits to 0.
        */
        void resetCfgBits();


        /**
        * \brief Gets a configuration bit.
        * \param index Index of bit.
        * \return True, if denoted bit is set, false otherwise.
        */
        bool testCfgBit(size_t index) const;

        /// Constant for denoting an invalid bit index
        static const size_t INVALID_BIT_INDEX = static_cast<size_t>(-1);

        /**
        * \brief Gets index of first set configuration data bit.
        * \return If found, index of bit; INVALID_BIT_INDEX otherwise.
        */
        size_t firstCfgBit() const;

        /**
        * \brief Gets index of first set bit behind given index.
        * \param index The start index.
        * \return If found, index of bit; INVALID_BIT_INDEX otherwise.
        */
        size_t nextCfgBit(size_t index) const;


        /**
        * \brief Appends configuration bits.
        * \param data Buffer from which to copy bits.
        * \param dataWordCount Buffer size in words.
        */
        void appendCfgBits(boost::uint32_t* data, size_t dataWordCount);


        /**********************************************************************/
        /* INTERSECTION                                                       */
        /**********************************************************************/

        /**
        * \brief Intersects this unit with another one.
        * \param with The other unit.
        * \throw .
        */
        void intersect(const CorrelationUnit& with);

        /**
        * \brief Intersects this unit with another inverted one.
        * \param with The other unit.
        * \throw .
        */
        void intersectInverted(const CorrelationUnit& with);


    private:

        boost::dynamic_bitset<boost::uint32_t> m_pipBits;
        boost::dynamic_bitset<boost::uint32_t> m_cfgBits;

    };


    /// A list of CorrelationUnits
    typedef std::vector<CorrelationUnit> CorrelationUnits;

}

#endif
