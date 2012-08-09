/**
* \file V5CommandCode.cpp
* \brief Contains V5CommandCode enumeration constants and strings.
*/

#include <packetprocessor/V5CommandCode.hpp>

using namespace bil;

const char* const V5CommandCode::NULLCMD_STRING = "NULL";
const char* const V5CommandCode::WCFG_STRING = "WCFG";
const char* const V5CommandCode::MFW_STRING = "MFW";
const char* const V5CommandCode::LFRM_STRING = "LFRM";
const char* const V5CommandCode::RCFG_STRING = "RCFG";
const char* const V5CommandCode::START_STRING = "START";
const char* const V5CommandCode::RCAP_STRING = "RCAP";
const char* const V5CommandCode::RCRC_STRING = "RCRC";
const char* const V5CommandCode::AGHIGH_STRING = "AGHIGH";
const char* const V5CommandCode::SWITCH_STRING = "SWITCH";
const char* const V5CommandCode::GRESTORE_STRING = "GRESTORE";
const char* const V5CommandCode::SHUTDOWN_STRING = "SHUTDOWN";
const char* const V5CommandCode::GCAPTURE_STRING = "GCAPTURE";
const char* const V5CommandCode::DESYNCH_STRING = "DESYNCH";
const char* const V5CommandCode::IPROG_STRING = "IPROG";
const char* const V5CommandCode::CRCC_STRING = "CRCC";
const char* const V5CommandCode::LTIMER_STRING = "LTIMER";


const char* V5CommandCode::toString(command_t command)
{
    switch (command)
    {
    case NULLCMD: return NULLCMD_STRING;
    case WCFG: return WCFG_STRING;
    case MFW: return MFW_STRING;
    case LFRM: return LFRM_STRING;
    case RCFG: return RCFG_STRING;
    case START: return START_STRING;
    case RCAP: return RCAP_STRING;
    case RCRC: return RCRC_STRING;
    case AGHIGH: return AGHIGH_STRING;
    case SWITCH: return SWITCH_STRING;
    case GRESTORE: return GRESTORE_STRING;
    case SHUTDOWN: return SHUTDOWN_STRING;
    case GCAPTURE: return GCAPTURE_STRING;
    case DESYNCH: return DESYNCH_STRING;
    case IPROG: return IPROG_STRING;
    case CRCC: return CRCC_STRING;
    case LTIMER: return LTIMER_STRING;
    default: return 0;
    }
}