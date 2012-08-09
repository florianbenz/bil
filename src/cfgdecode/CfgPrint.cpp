/**
* \file CfgPrint.cpp
* \brief Contains functions for printing PIPs and primitive site configurations.
*/

#include <cfgdecode/CfgPrint.hpp>

using namespace bil;


void bil::printPIPs(const PIPRefs& pipRefs, const Device& device,
  std::ostream& outputStream)
{
    // cache tiles and tile types
    const Tiles& tiles = device.tiles();
    const TileTypes& tileTypes = device.tileTypes();

    // loop over all given PIP references
    size_t pipCount = pipRefs.size();
    for (size_t i = 0; i < pipCount; ++i)
    {
        // get current PIPRef
        const PIPRef& pipRef = pipRefs[i];

        // get tile location of PIP
        const Tile& tile = tiles.at(pipRef.tileIndex());

        // get start wire, direction, and end wire of PIP
        const TileType& tileType = tileTypes.at(tile.typeIndex());
        const PIPs& pips = tileType.pips();
        const PIP& pip = pips.at(pipRef.pipIndex());
        const Wires& wires = tileType.wires();
        const Wire& startWire = wires.at(pip.startWireIndex());
        const Wire& endWire = wires.at(pip.endWireIndex());

        // print that
        outputStream << tile.name() << ' ' << startWire.name() << ' ';
        outputStream << PIPDirection::toString(pip.direction()) << ' ';
        outputStream << endWire.name() << '\n';
    }
}
