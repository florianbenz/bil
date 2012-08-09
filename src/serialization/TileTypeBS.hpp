/**
* \file TileTypeBS.hpp
* \brief Contains binary serialization functions for TileType class.
*/

#pragma once
#ifndef BIL_TILETYPEBS_HPP
#define BIL_TILETYPEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class TileType;


    /**
    * \brief Writes data from a TileType into a binary stream.
    * \param data The TileType to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const TileType& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a TileType from a binary stream.
    * \param data The TileType to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(TileType& data, std::istream& inputStream);

}

#endif
