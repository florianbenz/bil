/**
* \file PIPRefString.cpp
* \brief Contains functions for converting PIPRefs to text.
*/

#include <xdl/writer/PIPRefString.hpp>
#include <xdlrc/util/PIPString.hpp>

using namespace bil;


std::string bil::pipRefString(const PIPRef& pipRef, const Tiles& tiles,
  const TileTypes& tileTypes)
{
    // get tile location of PIP
    const Tile& tile = tiles.at(pipRef.tileIndex());
    // add tile name to result string
    std::string pipRefStr(tile.name());
    pipRefStr.push_back(' ');

    // get start wire, direction, and end wire of PIP
    const TileType& tileType = tileTypes.at(tile.typeIndex());
    const PIPs& pips = tileType.pips();
    const PIP& pip = pips.at(pipRef.pipIndex());
    const Wires& wires = tileType.wires();
    pipRefStr.append(pipString(pip, wires));

    // return string
    return pipRefStr;
}