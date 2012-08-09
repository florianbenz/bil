/**
* \file V5CfgColumn.cpp
* \brief Contains Virtex-5 configuration column enumeration constants and
*        strings.
*/

#include <configuration/V5CfgColumn.hpp>

using namespace bil;


const char* const V5CfgColumn::CLB_STRING = "CLB";
const char* const V5CfgColumn::DSP_STRING = "DSP";
const char* const V5CfgColumn::BRAM_STRING = "BRAM";
const char* const V5CfgColumn::IOB_STRING = "IOB";
const char* const V5CfgColumn::CLK_STRING = "CLK";
const char* const V5CfgColumn::SERIAL_STRING = "SERIAL";


const char* V5CfgColumn::toString(V5CfgColumn::column_t columnType)
{
    switch (columnType)
    {
    case CLB: return CLB_STRING;
    case DSP: return DSP_STRING;
    case BRAM: return BRAM_STRING;
    case IOB: return IOB_STRING;
    case CLK: return CLK_STRING;
    case SERIAL: return SERIAL_STRING;
    default: return 0;
    }
}