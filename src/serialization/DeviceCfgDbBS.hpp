/**
* \file DeviceCfgDbBS.hpp
* \brief Contains binary serialization functions for DeviceCfgDb class.
*/

#pragma once
#ifndef BIL_DEVICECFGDBBS_HPP
#define BIL_DEVICECFGDBBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class DeviceCfgDb;


    /**
    * \brief Writes data from a DeviceCfgDb into a binary stream.
    * \param data The DeviceCfgDb to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const DeviceCfgDb& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a DeviceCfgDb from a binary stream.
    * \param data The DeviceCfgDb to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(DeviceCfgDb& data, std::istream& inputStream);

}

#endif
