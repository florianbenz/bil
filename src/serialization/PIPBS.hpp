/**
* \file PIPBS.hpp
* \brief Contains binary serialization functions for PIP class.
*/

#pragma once
#ifndef BIL_PIPBS_HPP
#define BIL_PIPBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PIP;


    /**
    * \brief Writes data from a PIP into a binary stream.
    * \param data The PIP to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PIP& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PIP from a binary stream.
    * \param data The PIP to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PIP& data, std::istream& inputStream);

}

#endif
