/**
* \file DeviceRegistryBS.hpp
* \brief Contains binary serialization functions for DeviceRegistry class.
*/

#pragma once
#ifndef BIL_DEVICEREGISTRYBS_HPP
#define BIL_DEVICEREGISTRYBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class DeviceRegistry;


    /**
    * \brief Writes data from a DeviceRegistry into a binary stream.
    * \param data The DeviceRegistry to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const DeviceRegistry& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a DeviceRegistry from a binary stream.
    * \param data The DeviceRegistry to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(DeviceRegistry& data, std::istream& inputStream);

}

#endif
