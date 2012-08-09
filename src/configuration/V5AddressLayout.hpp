/**
* \file V5AddressLayout.hpp
* \brief Contains declaration of V5AddressLayout class.
*/

#pragma once
#ifndef BIL_V5ADDRESSLAYOUT_HPP
#define BIL_V5ADDRESSLAYOUT_HPP

#include <configuration/V5CfgBlock.hpp>
#include <configuration/V5CfgColumn.hpp>
#include <serialization/V5AddressLayoutBS.hpp>


namespace bil {

    /**
    * \brief Configuration address layout of a Virtex-5 device.
    *
    * All devices in the Virtex-5 series share the same configuration memory
    * addressing concept, but number and addressing/placement of the resources
    * to configure differ. This class can be filled with data describing how
    * configuration memory of a specific device is laid out: i.e. which
    * resources are located at which addresses, and which addresses are valid.
    */
    class V5AddressLayout {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5AddressLayout instance.
        */
        V5AddressLayout();

        /**
        * \brief Constructs a new V5AddressLayout instance.
        * \param upperRowCount See upperRowCount().
        * \param lowerRowCount See lowerRowCount().
        * \param columnSequence See columnSequence().
        */
        V5AddressLayout(unsigned upperRowCount, unsigned lowerRowCount, const V5CfgColumnSequence& columnSequence);


        /**********************************************************************/
        /* UPPER ROW COUNT                                                    */
        /**********************************************************************/

        /// Maximum allowed value for upper and lower row count
        static const unsigned ROWCOUNT_MAX = 31;

        /**
        * \brief Sets number of rows in upper half of the FPGA.
        * \details Upper rows are indexed from 0 to number of upper rows - 1.
        *          They start in the FPGA's middle and run to the upper border.
        * \param count Number of upper rows.
        * \throws .
        */
        void upperRowCount(unsigned count);

        /**
        * \brief Gets number of rows in upper half of the FPGA.
        * \return Number of upper rows.
        */
        unsigned upperRowCount() const;


        /**********************************************************************/
        /* LOWER ROW COUNT                                                    */
        /**********************************************************************/

        /**
        * \brief Sets number of rows in lower half of the FPGA.
        * \details Lower rows are indexed from 0 to number of lower rows - 1.
        *          They start in the FPGA's middle and run to the lower border.
        * \param count Number of lower rows.
        * \throws .
        */
        void lowerRowCount(unsigned count);

        /**
        * \brief Gets number of rows in lower half of the FPGA.
        * \return Number of lower rows.
        */
        unsigned lowerRowCount() const;


        /**********************************************************************/
        /* COLUMN SEQUENCE                                                    */
        /**********************************************************************/

        /// Maximum allowed value for column count
        static const unsigned COLUMNCOUNT_MAX = 255;

        /**
        * \brief Sets column sequence.
        * \details The given column sequence is copied and then interpreted as
        *          if it was in INTERCONNECT_AND_CFG block. Column sequences for
        *          the other blocks are deduced from this.
        * \param columns Column sequence.
        * \throws .
        */
        void columnSequence(const V5CfgColumnSequence& columns);

        /**
        * \brief Gets column sequence.
        * \details Result is a read only reference to the V5CfgColumnSequence
        *          instance owned by the V5AddressLayout.
        * \return Column sequence of a row in INTERCONNECT_AND_CFG block.
        */
        const V5CfgColumnSequence& columnSequence() const;


        /**********************************************************************/
        /* QUERY FUNCTIONS                                                    */
        /**********************************************************************/

        /**
        * \brief Gets number of rows in upper or lower half of the FPGA.
        * \details The total row count equals rowCount(false) + rowCount(true).
        * \param lowerHalf Flag designating upper or lower half.
        * \return Number of rows in designated half of the FPGA.
        */
        unsigned rowCount(bool lowerHalf) const;

        /**
        * \brief Gets number of columns in the specified block.
        * \param block Block to query.
        * \return Number of columns.
        */
        unsigned columnCount(V5CfgBlock::block_t block) const;

        /**
        * \brief Gets number of frames a resource of specified column type in
        *        specified block is configured with.
        * \param block Block the column/resource is in.
        * \param column Column type of the resource.
        * \return Number of frames the resource is configured with.
        */
        unsigned frameCount(V5CfgBlock::block_t block, V5CfgColumn::column_t column) const;

        /**
        * \brief Gets type of specified column in specified block.
        * \param block Block the column is in.
        * \param columnIndex Index of column to query.
        * \return Type of the column in question.
        * \throws .
        */
        V5CfgColumn::column_t columnType(V5CfgBlock::block_t block, size_t columnIndex) const;


    protected:

        /**
        * \brief Counts the number of block RAM columns in given row.
        * \param columns Row in which to count.
        * \return Number of block RAM columns.
        */
        unsigned countBRAMs(const V5CfgColumnSequence& columns) const;


    private:

        friend bool operator== (const V5AddressLayout& al1, const V5AddressLayout& al2);

        friend void writeBinary(const V5AddressLayout& data, std::ostream& outputStream);
        friend void readBinary(V5AddressLayout& data, std::istream& inputStream);


        unsigned m_upperRowCount;
        unsigned m_lowerRowCount;
        V5CfgColumnSequence m_columns;
        unsigned m_bramCount;

    };


    /// Tests two V5AddressLayout instances for memberwise equality
    inline bool operator== (const V5AddressLayout& al1, const V5AddressLayout& al2)
    {
        if (al1.m_upperRowCount != al2.m_upperRowCount) return false;
        if (al1.m_lowerRowCount != al2.m_lowerRowCount) return false;
        if (al1.m_bramCount != al2.m_bramCount) return false;
        return al1.m_columns == al2.m_columns;
    }

    /// Tests two V5AddressLayout instances for memberwise inequality
    inline bool operator!= (const V5AddressLayout& al1, const V5AddressLayout& al2)
    {
        return !(operator== (al1, al2));
    }

}

#endif
