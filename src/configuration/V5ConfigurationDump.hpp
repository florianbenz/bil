/**
* \file V5ConfigurationDump.hpp
* \brief Functions for dumping V5Configuration contents to a stream.
*/

#pragma once
#ifndef BIL_V5CONFIGURATIONDUMP_HPP
#define BIL_V5CONFIGURATIONDUMP_HPP

#include <ostream>


namespace bil {

    class V5Configuration;


    /**
    * \brief Writes all frames in a V5Configuration to a stream.
    * \param cfg V5Configuration instance which contents to be dumped.
    * \param cfgOut Stream to write the frame data into.
    * \param indexOut Stream to write textual frame offsets into.
    * \throws .
    */
    void dumpConfiguration(const V5Configuration& cfg, std::ostream& cfgOut, std::ostream& indexOut);

}

#endif
