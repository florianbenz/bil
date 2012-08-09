/**
* \file V5CfgColumn.hpp
* \brief Contains Virtex-5 configuration column enumeration constants and
*        strings.
*/

#pragma once
#ifndef BIL_V5CFGCOLUMN_HPP
#define BIL_V5CFGCOLUMN_HPP

#include <vector>


namespace bil {

    /**
    * \brief Namespace for Virtex-5 configuration column constants.
    *
    * Inside the block subspaces the resources are organized into a grid of rows
    * and columns. All resources inside a column are of the same type, so the
    * following constants identify not only the type of distinct resource but
    * also the type of a whole column of resources.
    */
    namespace V5CfgColumn {

        /// Column resource type.
        typedef unsigned char column_t;


        /// Configurable logic blocks.
        const column_t CLB = 0x00;

        /// Digital signal processors.
        const column_t DSP = 0x01;

        /// Block RAMs.
        const column_t BRAM = 0x02;

        /// I/O buffers.
        const column_t IOB = 0x03;

        /// Clock generation and management.
        const column_t CLK = 0x04;

        /// Serial connections.
        const column_t SERIAL = 0x05;


        extern const char* const CLB_STRING;
        extern const char* const DSP_STRING;
        extern const char* const BRAM_STRING;
        extern const char* const IOB_STRING;
        extern const char* const CLK_STRING;
        extern const char* const SERIAL_STRING;


        /**
        * \brief Returns a string representation of given column type.
        * \param columnType The column type.
        * \return The string representation.
        */
        const char* toString(column_t columnType);

    }


    /**
    * \brief V5CfgColumnSequence holds a sequence of column types.
    *
    * This sequence of column types defines a row. Since all rows inside a block
    * do not differ, it defines also the whole resource grid for a block.
    */
    typedef std::vector<V5CfgColumn::column_t> V5CfgColumnSequence;

}

#endif
