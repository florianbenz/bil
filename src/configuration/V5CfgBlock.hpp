/**
* \file V5CfgBlock.hpp
* \brief Contains Virtex-5 configuration block enumeration constants and
*        strings.
*/

#pragma once
#ifndef BIL_V5CFGBLOCK_HPP
#define BIL_V5CFGBLOCK_HPP


namespace bil {

    /**
    * \brief Namespace for Virtex-5 configuration block constants.
    *
    * Configuration address space is divided into continuous regions called
    * blocks which contain data for a specific purpose. These blocks are
    * addressed with the following constants.
    */
    namespace V5CfgBlock {

        /// Configuration block type.
        typedef unsigned char block_t;


        /// Interconnection and configuration data block.
        const block_t INTERCONNECT_AND_CFG = 0x00;

        /// Block RAM content block.
        const block_t BRAM_CONTENT = 0x01;

        /// Dynamic reconfiguration data block.
        const block_t SPECIAL = 0x02;

        /// BRAM non-configuration data block.
        const block_t BRAM_NONCFGDATA = 0x03;


        extern const char* const INTERCONNECT_AND_CFG_STRING;
        extern const char* const BRAM_CONTENT_STRING;
        extern const char* const SPECIAL_STRING;
        extern const char* const BRAM_NONCFGDATA_STRING;


        /**
        * \brief Returns a string representation of given block constant.
        * \param block The block.
        * \return The string representation.
        */
        const char* toString(block_t block);

    }

}

#endif
