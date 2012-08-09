/**
* \file NameSplit.cpp
* \brief Splitting of XDL(RC) names into parts.
*/

#include <cstdlib>
#include <cstring>
#include <xdlrc/util/NameSplit.hpp>

using namespace bil;


bool bil::extractPosition(const char* name, unsigned& x, unsigned& y)
{
    // scan for last occurrence of underscore
    name = strrchr(name, '_');

    // read X coordinate
    if (0 == name) return false;
    if ('X' != *(++name)) return false;
    x = strtol(++name, const_cast<char**>(&name), 10);

    // read Y coordinate
    if (0 == name) return false;
    if ('Y' != *(name++)) return false;
    y = strtol(name, const_cast<char**>(&name), 10);

    // test for string end
    return ((0 != name) && (0 == *name));
}