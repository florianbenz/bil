/**
* \file PIPDirection.cpp
* \brief Contains PIPDirection enumeration constants and strings.
*/

#include <cstring>
#include <exception/Exception.hpp>
#include <xdlrc/model/PIPDirection.hpp>

using namespace bil;

const char* const PIPDirection::MONODI_BUF_STRING = "->";
const char* const PIPDirection::BIDI_UNBUF_STRING = "==";
const char* const PIPDirection::BIDI_ONEBUF_STRING = "=>";
const char* const PIPDirection::BIDI_TWOBUF_STRING = "=-";


const char* PIPDirection::toString(direction_t dir)
{
    switch (dir)
    {
    case MONODI_BUF: return MONODI_BUF_STRING;
    case BIDI_UNBUF: return BIDI_UNBUF_STRING;
    case BIDI_ONEBUF: return BIDI_ONEBUF_STRING;
    case BIDI_TWOBUF: return BIDI_TWOBUF_STRING;
    default: return 0;
    }
}


PIPDirection::direction_t PIPDirection::fromString(const char* s)
{
    if (0 == strcmp(s, MONODI_BUF_STRING)) return MONODI_BUF;
    if (0 == strcmp(s, BIDI_UNBUF_STRING)) return BIDI_UNBUF;
    if (0 == strcmp(s, BIDI_ONEBUF_STRING)) return BIDI_ONEBUF;
    if (0 == strcmp(s, BIDI_TWOBUF_STRING)) return BIDI_TWOBUF;
    throw Exception();
}