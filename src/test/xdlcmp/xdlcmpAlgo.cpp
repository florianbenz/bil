/**
* \file xdlcmpAlgo.cpp
* \brief Contains definition of xdlcmp compare functions.
*/

#include <algorithm>
#include <iterator>
#include <test/xdlcmp/xdlcmpAlgo.hpp>
#include <xdl/writer/PIPRefString.hpp>

using namespace bil;

const char* const PIPSPRESENT1_MSG = "PIPs present in reference design, but not in test design:\n";
const char* const PIPSPRESENT2_MSG = "\nPIPs present in test design, but not in reference design:\n";
const char* const PIPSSTATS1_MSG = "\nPIPs in reference design: ";
const char* const PIPSSTATS2_MSG = "Correct PIPs in test design: ";
const char* const PIPSSTATS3_MSG = "Missing PIPs in test design: ";
const char* const PIPSSTATS4_MSG = "Incorrect PIPs in test design: ";
const char* const PIP_MSG = "pip";
const char ENDLN = '\n';


void getPIPs(const Design& design, PIPRefs& pipRefs)
{
    // clear old data
    pipRefs.clear();

    // collect all PIPs from all nets
    const Nets& nets = design.nets();
    size_t netCount = nets.size();
    for (size_t i = 0; i < netCount; ++i)
    {
        const Net& net = nets[i];
        const PIPRefs& srcPipRefs = net.pipRefs();
        pipRefs.insert(pipRefs.end(), srcPipRefs.begin(), srcPipRefs.end());
    }

    // sort them
    std::sort(pipRefs.begin(), pipRefs.end());
}


void comparePIPs(const PIPRefs& refPIPRefs, const PIPRefs& testPIPRefs,
  const Device& device, std::ostream& outputStream)
{
    // cache pointers to tiles and tile types
    const Tiles& tiles = device.tiles();
    const TileTypes& tileTypes = device.tileTypes();

    // flag vector for test PIPs
    std::vector<bool> correctPips;
    correctPips.resize(testPIPRefs.size(), false);

    // iterators for test PIPs
    PIPRefs::const_iterator itBegin = testPIPRefs.begin();
    PIPRefs::const_iterator itEnd = testPIPRefs.end();
    PIPRefs::const_iterator it;

    // stats counters
    size_t correctPIPCount = 0;
    size_t missingPIPCount = 0;
    size_t incorrectPIPCount = 0;

    // loop over all reference PIPs and check, if they are in test PIPs
    outputStream << PIPSPRESENT1_MSG;
    size_t refPipCount = refPIPRefs.size();
    for (size_t i = 0; i < refPipCount; ++i)
    {
        const PIPRef& refPIPRef = refPIPRefs[i];
        it = std::find(itBegin, itEnd, refPIPRef);
        if (it != itEnd)
        {
            size_t testPipIndex = std::distance(itBegin, it);
            correctPips[testPipIndex] = true;
            ++correctPIPCount;
        }
        else
        {
            outputStream << PIP_MSG << pipRefString(refPIPRef, tiles, tileTypes) << ENDLN;
            ++missingPIPCount;
        }
    }

    // loop over all test PIPs and check, if they are in reference PIPs
    outputStream << PIPSPRESENT2_MSG;
    size_t testPipCount = testPIPRefs.size();
    for (size_t i = 0; i < testPipCount; ++i)
    {
        if (correctPips[i]) continue;
        const PIPRef& testPIPRef = testPIPRefs[i];
        outputStream << PIP_MSG << pipRefString(testPIPRef, tiles, tileTypes) << ENDLN;
        ++incorrectPIPCount;
    }

    // print stats
    outputStream << PIPSSTATS1_MSG << refPipCount << ENDLN;
    outputStream << PIPSSTATS2_MSG << correctPIPCount << ENDLN;
    outputStream << PIPSSTATS3_MSG << missingPIPCount << ENDLN;
    outputStream << PIPSSTATS4_MSG << incorrectPIPCount;
}