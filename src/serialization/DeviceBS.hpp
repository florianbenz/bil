/**
* \file DeviceBS.hpp
* \brief Contains binary serialization functions for Device class.
*/

#pragma once
#ifndef BIL_DEVICEBS_HPP
#define BIL_DEVICEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class Device;


    /**
    * \brief Writes data from a Device into a binary stream.
    * \param data The Device to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const Device& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a Device from a binary stream.
    * \param data The Device to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(Device& data, std::istream& inputStream);

}

#endif
