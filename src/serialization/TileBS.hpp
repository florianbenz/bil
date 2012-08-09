/**
* \file TileBS.hpp
* \brief Contains binary serialization functions for Tile class.
*/

#pragma once
#ifndef BIL_TILEBS_HPP
#define BIL_TILEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class Tile;


    /**
    * \brief Writes data from a Tile into a binary stream.
    * \param data The Tile to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const Tile& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a Tile from a binary stream.
    * \param data The Tile to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(Tile& data, std::istream& inputStream);

}

#endif
