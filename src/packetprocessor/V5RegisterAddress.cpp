/**
* \file V5RegisterAddress.cpp
* \brief Contains V5RegisterAddress enumeration constants and strings.
*/

#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;

const char* const V5RegisterAddress::CRC_STRING = "CRC";
const char* const V5RegisterAddress::FAR_STRING = "FAR";
const char* const V5RegisterAddress::FDRI_STRING = "FDRI";
const char* const V5RegisterAddress::FDRO_STRING = "FDRO";
const char* const V5RegisterAddress::CMD_STRING = "CMD";
const char* const V5RegisterAddress::CTL0_STRING = "CTL0";
const char* const V5RegisterAddress::MASK_STRING = "MASK";
const char* const V5RegisterAddress::STAT_STRING = "STAT";
const char* const V5RegisterAddress::LOUT_STRING = "LOUT";
const char* const V5RegisterAddress::COR0_STRING = "COR0";
const char* const V5RegisterAddress::MFWR_STRING = "MFWR";
const char* const V5RegisterAddress::CBC_STRING = "CBC";
const char* const V5RegisterAddress::IDCODE_STRING = "IDCODE";
const char* const V5RegisterAddress::AXSS_STRING = "AXSS";
const char* const V5RegisterAddress::COR1_STRING = "COR1";
const char* const V5RegisterAddress::CSOB_STRING = "CSOB";
const char* const V5RegisterAddress::WBSTAR_STRING = "WBSTAR";
const char* const V5RegisterAddress::TIMER_STRING = "TIMER";
const char* const V5RegisterAddress::REG19_STRING = "REG19";
const char* const V5RegisterAddress::BOOTSTS_STRING = "BOOTSTS";
const char* const V5RegisterAddress::CTL1_STRING = "CTL1";


const char* V5RegisterAddress::toString(RegisterAddress::address_t address)
{
    switch (address)
    {
    case CRC: return CRC_STRING;
    case FAR: return FAR_STRING;
    case FDRI: return FDRI_STRING;
    case FDRO: return FDRO_STRING;
    case CMD: return CMD_STRING;
    case CTL0: return CTL0_STRING;
    case MASK: return MASK_STRING;
    case STAT: return STAT_STRING;
    case LOUT: return LOUT_STRING;
    case COR0: return COR0_STRING;
    case MFWR: return MFWR_STRING;
    case CBC: return CBC_STRING;
    case IDCODE: return IDCODE_STRING;
    case AXSS: return AXSS_STRING;
    case COR1: return COR1_STRING;
    case CSOB: return CSOB_STRING;
    case WBSTAR: return WBSTAR_STRING;
    case TIMER: return TIMER_STRING;
    case REG19: return REG19_STRING;
    case BOOTSTS: return BOOTSTS_STRING;
    case CTL1: return CTL1_STRING;
    default: return 0;
    }
}