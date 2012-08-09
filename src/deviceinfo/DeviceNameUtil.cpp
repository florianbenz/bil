/**
* \file DeviceNameUtil.cpp
* \brief Splitting of device names into parts.
*/

#include <cstdlib>
#include <cstring>
#include <deviceinfo/DeviceNameUtil.hpp>

using namespace bil;


std::string bil::removePackageAndSpeed(const char* deviceName)
{
    // get length until beginning of package name
    const char* sPtr = strstr(deviceName, "ff");
    size_t len;
    if (0 != sPtr) len = sPtr - deviceName;
    else len = strlen(deviceName);

    // return string until package name
    return std::string(deviceName, len);
}


std::string bil::removeSpeed(const char* deviceName)
{
    // get length until beginning of speed grade
    const char* sPtr = strchr(deviceName, '-');
    size_t len;
    if (0 != sPtr) len = sPtr - deviceName;
    else len = strlen(deviceName);

    // return string until package name
    return std::string(deviceName, len);
}