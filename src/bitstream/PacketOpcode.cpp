/**
* \file PacketOpcode.cpp
* \brief Contains packet opcode enumeration constants and strings.
*/

#include <bitstream/PacketOpcode.hpp>

using namespace bil;

const char* const PacketOpcode::NO_OP_STRING = "NO_OP";
const char* const PacketOpcode::REGISTER_READ_STRING = "REGISTER_READ";
const char* const PacketOpcode::REGISTER_WRITE_STRING = "REGISTER_WRITE";


const char* PacketOpcode::toString(opcode_t opcode)
{
    switch (opcode)
    {
    case NO_OP: return NO_OP_STRING;
    case REGISTER_READ: return REGISTER_READ_STRING;
    case REGISTER_WRITE: return REGISTER_WRITE_STRING;
    default: return 0;
    }
}