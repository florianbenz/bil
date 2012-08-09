/**
* \file PinBS.hpp
* \brief Contains binary serialization functions for Pin class.
*/

#pragma once
#ifndef BIL_PINBS_HPP
#define BIL_PINBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class Pin;


    /**
    * \brief Writes data from a Pin into a binary stream.
    * \param data The Pin to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const Pin& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a Pin from a binary stream.
    * \param data The Pin to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(Pin& data, std::istream& inputStream);

}

#endif
