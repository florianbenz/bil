/**
* \file BitFileWriter.hpp
* \brief Function for writing a bitfile to a stream.
*/

#pragma once
#ifndef BIL_BITFILEWRITER_HPP
#define BIL_BITFILEWRITER_HPP

#include <ostream>


namespace bil {

    class BitFileData;


    /**
    * \brief Writes data in bitfile format to a stream.
    * \param bfd Data to write.
    * \param outputStream Stream to write into.
    * \throws .
    */
    void writeBitfile(const BitFileData& bfd, std::ostream& outputStream);

}

#endif
