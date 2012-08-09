/**
* \file V5CfgBlock.cpp
* \brief Contains Virtex-5 configuration block enumeration constants and
*        strings.
*/

#include <configuration/V5CfgBlock.hpp>

using namespace bil;

const char* const V5CfgBlock::INTERCONNECT_AND_CFG_STRING = "INTERCONNECT_AND_CFG";
const char* const V5CfgBlock::BRAM_CONTENT_STRING = "BRAM_CONTENT";
const char* const V5CfgBlock::SPECIAL_STRING = "SPECIAL";
const char* const V5CfgBlock::BRAM_NONCFGDATA_STRING = "BRAM_NONCFGDATA";


const char* V5CfgBlock::toString(block_t block)
{
    switch (block)
    {
    case INTERCONNECT_AND_CFG: return INTERCONNECT_AND_CFG_STRING;
    case BRAM_CONTENT: return BRAM_CONTENT_STRING;
    case SPECIAL: return SPECIAL_STRING;
    case BRAM_NONCFGDATA: return BRAM_NONCFGDATA_STRING;
    default: return 0;
    }
}