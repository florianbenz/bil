/**
* \file NetType.cpp
* \brief Contains NetType enumeration constants and strings.
*/

#include <cstring>
#include <exception/Exception.hpp>
#include <xdl/model/NetType.hpp>

using namespace bil;

const char* const NetType::WIRE_STRING = "wire";
const char* const NetType::VCC_STRING = "vcc";
const char* const NetType::VDD_STRING = "vdd";
const char* const NetType::POWER_STRING = "power";
const char* const NetType::GND_STRING = "gnd";
const char* const NetType::GROUND_STRING = "ground";


const char* NetType::toString(net_t type)
{
    switch (type)
    {
    case WIRE: return WIRE_STRING;
    case VCC: return VCC_STRING;
    case GND: return GND_STRING;
    default: return 0;
    }
}


NetType::net_t NetType::fromString(const char* s)
{
    if (0 == strcmp(s, WIRE_STRING)) return WIRE;
    if (0 == strcmp(s, VCC_STRING)) return VCC;
    if (0 == strcmp(s, VDD_STRING)) return VCC;
    if (0 == strcmp(s, POWER_STRING)) return VCC;
    if (0 == strcmp(s, GND_STRING)) return GND;
    if (0 == strcmp(s, GROUND_STRING)) return GND;
    throw Exception();
}