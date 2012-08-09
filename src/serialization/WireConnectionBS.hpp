/**
* \file WireConnectionBS.hpp
* \brief Contains binary serialization functions for WireConnection class.
*/

#pragma once
#ifndef BIL_WIRECONNECTIONBS_HPP
#define BIL_WIRECONNECTIONBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class WireConnection;


    /**
    * \brief Writes data from a WireConnection into a binary stream.
    * \param data The WireConnection to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const WireConnection& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a WireConnection from a binary stream.
    * \param data The WireConnection to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(WireConnection& data, std::istream& inputStream);

}

#endif
