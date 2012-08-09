/**
* \file PIPString.cpp
* \brief Contains functions for converting PIPs to text.
*/

#include <xdlrc/util/PIPString.hpp>

using namespace bil;


std::string bil::pipString(const PIP& pip, const Wires& wires)
{
    // get start and end wires
    const Wire& startWire = wires.at(pip.startWireIndex());
    const Wire& endWire = wires.at(pip.endWireIndex());

    // build string
    std::string pipStr(startWire.name());
    pipStr.push_back(' ');
    pipStr.append(PIPDirection::toString(pip.direction()));
    pipStr.push_back(' ');
    pipStr.append(endWire.name());

    // return it
    return pipStr;
}