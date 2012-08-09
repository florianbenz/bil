/**
* \file V5ConfigurationDump.cpp
* \brief Functions for dumping V5Configuration contents to a stream.
*/

#include <configuration/V5Configuration.hpp>
#include <configuration/V5ConfigurationDump.hpp>
#include <configuration/V5FrameAddressString.hpp>
#include <exception/IOException.hpp>
#include <util/HexPrint.hpp>

using namespace bil;


void bil::dumpConfiguration(const V5Configuration& cfg, std::ostream& cfgOut, std::ostream& indexOut)
{
    // collect list with all frame addresses and their frames
    V5Configuration::pairconstptrs_t pairs = cfg.contents();

    // loop over list
    size_t frameCount = pairs.size();
    for (size_t i = 0; i < frameCount; ++i)
    {
        // get pointer to current pair
        const V5Configuration::pair_t* pairPtr = pairs[i];

        // write one line with raw frame address info and frame data offset
        const V5FrameAddress& address = pairPtr->first;
        indexOut << toRawAddressString(address) << '\t';
        printHex(indexOut, cfgOut.tellp());
        indexOut << "\t(" << toSymbolicString(address) << "):";
        indexOut << V5CfgColumn::toString(address.columnType()) << '\n';
        if (!indexOut) throw IOException();

        // write frame data
        const V5CfgFrame& frame = pairPtr->second;
        cfgOut.write(reinterpret_cast<const char*>(frame.data()), V5CfgFrame::WORDCOUNT << 2);
        if (!cfgOut) throw IOException();
    }
}