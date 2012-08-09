/**
* \file PIPRefString.hpp
* \brief Contains functions for converting PIPRefs to text.
*/

#pragma once
#ifndef BIL_PIPREFSTRING_HPP
#define BIL_PIPREFSTRING_HPP

#include <string>
#include <xdl/model/PIPRef.hpp>
#include <xdlrc/model/Tile.hpp>
#include <xdlrc/model/TileType.hpp>


namespace bil {

    /**
    * \brief Converts a PIPRef to a text representation.
    * \param pipRef The PIPRef to convert.
    * \param tiles The tiles the PIPRef references.
    * \param tileTypes The types of the referenced tiles.
    * \return The string with the PIPRef text representation.
    * \throws .
    */
    std::string pipRefString(const PIPRef& pipRef, const Tiles& tiles, const TileTypes& tileTypes);

}

#endif
