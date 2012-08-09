/**
* \file BitFileReader.hpp
* \brief Function for reading a bitfile from a stream.
*/

#pragma once
#ifndef BIL_BITFILEREADER_HPP
#define BIL_BITFILEREADER_HPP

#include <istream>


namespace bil {

    class BitFileData;


    /**
    * \brief Reads bitfile data from stream.
    * \param bfd BitFileData instance to read into.
    * \param inputStream Stream to read from.
    * \throws .
    */
    void readBitfile(BitFileData& bfd, std::istream& inputStream);

}

#endif
