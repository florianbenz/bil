/**
* \file PIPString.hpp
* \brief Contains functions for converting PIPs to text.
*/

#pragma once
#ifndef BIL_PIPSTRING_HPP
#define BIL_PIPSTRING_HPP

#include <string>
#include <xdlrc/model/PIP.hpp>
#include <xdlrc/model/Wire.hpp>


namespace bil {

    /**
    * \brief Converts a PIP to a text representation.
    * \param pip The PIP to convert.
    * \param wires The wires the PIP references.
    * \return The string with the PIP text representation.
    * \throws .
    */
    std::string pipString(const PIP& pip, const Wires& wires);

}

#endif
