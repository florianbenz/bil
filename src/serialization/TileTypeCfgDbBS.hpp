/**
* \file TileTypeCfgDbBS.hpp
* \brief Contains binary serialization functions for TileTypeCfgDb class.
*/

#pragma once
#ifndef BIL_TILETYPECFGDBBS_HPP
#define BIL_TILETYPECFGDBBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class TileTypeCfgDb;


    /**
    * \brief Writes data from a TileTypeCfgDb into a binary stream.
    * \param data The TileTypeCfgDb to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const TileTypeCfgDb& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a TileTypeCfgDb from a binary stream.
    * \param data The TileTypeCfgDb to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(TileTypeCfgDb& data, std::istream& inputStream);

}

#endif
