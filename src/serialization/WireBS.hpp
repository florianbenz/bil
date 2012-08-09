/**
* \file WireBS.hpp
* \brief Contains binary serialization functions for Wire class.
*/

#pragma once
#ifndef BIL_WIREBS_HPP
#define BIL_WIREBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class Wire;


    /**
    * \brief Writes data from a Wire into a binary stream.
    * \param data The Wire to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const Wire& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a Wire from a binary stream.
    * \param data The Wire to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(Wire& data, std::istream& inputStream);

}

#endif
