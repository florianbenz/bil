/**
* \file BitFileSections.hpp
* \brief Contains declaration of bitfile section constants.
*/

#pragma once
#ifndef BIL_BITFILESECTIONS_HPP
#define BIL_BITFILESECTIONS_HPP

#include <cstring>
#include <boost/cstdint.hpp>


namespace bil {

    // bitfile header size
    const size_t BITFILE_HEADER_SIZE = 13;

    // bitfile header
    extern const boost::uint8_t BITFILE_HEADER[BITFILE_HEADER_SIZE];


    // constants denoting the sections found in a bitfile
    const char BITFILE_KEY_SOURCEFILENAME = 'a';
    const char BITFILE_KEY_TARGETDEVICENAME = 'b';
    const char BITFILE_KEY_CREATIONDATE = 'c';
    const char BITFILE_KEY_CREATIONTIME = 'd';
    const char BITFILE_KEY_BITSTREAM = 'e';

}

#endif
