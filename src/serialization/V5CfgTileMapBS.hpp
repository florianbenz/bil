/**
* \file V5CfgTileMapBS.hpp
* \brief Contains binary serialization functions for V5CfgTileMap class.
*/

#pragma once
#ifndef BIL_V5CFGTILEMAPBS_HPP
#define BIL_V5CFGTILEMAPBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class V5CfgTileMap;


    /**
    * \brief Writes data from a V5CfgTileMap into a binary stream.
    * \param data The V5CfgTileMap to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const V5CfgTileMap& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a V5CfgTileMap from a binary stream.
    * \param data The V5CfgTileMap to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(V5CfgTileMap& data, std::istream& inputStream);

}

#endif
