/**
* \file V5FrameAddressString.cpp
* \brief Contains string conversion functions for V5FrameAddress.
*/

#include <cstdio>
#include <configuration/V5FrameAddress.hpp>
#include <configuration/V5FrameAddressString.hpp>

using namespace bil;

static char sBuf[64];
const char* const LOWERHALF_STR = "LOWERHALF";
const char* const UPPERHALF_STR = "UPPERHALF";


std::string bil::toRawAddressString(const V5FrameAddress& address)
{
    // format raw address
    sprintf(sBuf, "0x%.8x", address.rawAddress());
    // return composed string
    return std::string(sBuf);
}


std::string bil::toExpandedString(const V5FrameAddress& address)
{
    // convert upper/lower flag
    char c = address.lowerHalf() ? '1' : '0';
    // format all address parts into one string
    sprintf(sBuf, "%u %c %u %u %u", address.block(), c, address.rowIndex(),
            address.columnIndex(), address.frameIndex());
    // return composed string
    return std::string(sBuf);
}


std::string bil::toSymbolicString(const V5FrameAddress& address)
{
    // convert block
    V5CfgBlock::block_t block = address.block();
    const char* blockName = V5CfgBlock::toString(block);
    // convert upper/lower flag
    const char* upperFlagName = address.lowerHalf() ? LOWERHALF_STR : UPPERHALF_STR;
    // format all address parts into one string
    if (0 == blockName)
        sprintf(sBuf, "%u %s %u %u %u", block, upperFlagName,
                address.rowIndex(), address.columnIndex(), address.frameIndex());
    else
        sprintf(sBuf, "%s %s %u %u %u", blockName, upperFlagName,
                address.rowIndex(), address.columnIndex(), address.frameIndex());
    // return composed string
    return std::string(sBuf);
}