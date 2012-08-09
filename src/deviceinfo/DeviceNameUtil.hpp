/**
* \file DeviceNameUtil.hpp
* \brief Splitting of device names into parts.
*/

#pragma once
#ifndef BIL_DEVICENAMEUTIL_HPP
#define BIL_DEVICENAMEUTIL_HPP

#include <string>


namespace bil {

    /**
    * \brief Removes package name and speed grade (if present) from a device name.
    * \param deviceName Device name to shorten.
    * \return Device name without package name or speed grade.
    */
    std::string removePackageAndSpeed(const char* deviceName);

    /**
    * \brief Removes speed grade (if present) from a device name.
    * \param deviceName Device name to shorten.
    * \return Device name without speed grade.
    */
    std::string removeSpeed(const char* deviceName);

}

#endif
