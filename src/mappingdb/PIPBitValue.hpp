/**
* \file PIPBitValue.hpp
* \brief Contains declaration of PIPBitValue class.
*/

#pragma once
#ifndef BIL_PIPBITVALUE_HPP
#define BIL_PIPBITVALUE_HPP

#include <vector>
#include <boost/cstdint.hpp>
#include <serialization/PIPBitValueBS.hpp>


namespace bil {

    /**
    * \brief The value of a PIPs associated configuration bits.
    *
    * This class associates a PIP with the value of its configuration bits.
    * Whenever the associated bits resemble this value, this PIP is active.
    */
    class PIPBitValue {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PIPBitValue instance.
        */
        PIPBitValue();


        /**********************************************************************/
        /* PIP INDEX                                                          */
        /**********************************************************************/

        /**
        * \brief Sets PIP index.
        * \param index Index of PIP in corresponding Device.
        */
        void pipIndex(size_t index);

        /**
        * \brief Gets pip index.
        * \return Index of PIP in corresponding Device.
        */
        size_t pipIndex() const;


        /**********************************************************************/
        /* BIT VALUE                                                          */
        /**********************************************************************/

        /// constant for maximum bits in value
        static const boost::uint32_t MAX_BIT_COUNT = 31;

        /// bit mask for the used/unused bit flag
        static const boost::uint32_t VALUE_UNUSED = 0x80000000;

        /**
        * \brief Sets active PIP configuration value.
        * \param value Value of the PIPs configuration bits.
        */
        void bitValue(boost::uint32_t value);

        /**
        * \brief Gets active PIP configuration value.
        * \return Value of the PIPs configuration bits.
        */
        boost::uint32_t bitValue() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend bool operator== (const PIPBitValue& val1, const PIPBitValue& val2);
        friend bool operator< (const PIPBitValue& val1, const PIPBitValue& val2);

        friend void writeBinary(const PIPBitValue& data, std::ostream& outputStream);
        friend void readBinary(PIPBitValue& data, std::istream& inputStream);

        size_t m_pipIndex;
        boost::uint32_t m_bitValue;

    };


    /// Tests two PIPBitValue instances for memberwise equality
    inline bool operator== (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        if (val1.m_bitValue != val2.m_bitValue) return false;
        return val1.m_pipIndex == val2.m_pipIndex;
    }

    /// Tests two PIPBitValue instances for memberwise inequality
    inline bool operator!= (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        return !(operator== (val1, val2));
    }


    /// Tests two PIPBitValue instances for memberwise <
    inline bool operator< (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        if (val1.m_bitValue != val2.m_bitValue) return val1.m_bitValue < val2.m_bitValue;
        return val1.m_pipIndex < val2.m_pipIndex;
    }

    /// Tests two PIPBitValue instances for memberwise >
    inline bool operator> (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        return (operator< (val2, val1));
    }

    /// Tests two PIPBitValue instances for memberwise <=
    inline bool operator<= (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        return !(operator> (val1, val2));
    }

    /// Tests two PIPBitValue instances for memberwise >=
    inline bool operator>= (const PIPBitValue& val1, const PIPBitValue& val2)
    {
        return !(operator< (val1, val2));
    }


    /// A list of PIPBitValue instances
    typedef std::vector<PIPBitValue> PIPBitValues;

}

#endif
