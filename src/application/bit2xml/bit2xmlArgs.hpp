/**
* \file bit2xmlArgs.hpp
* \brief Contains declaration of bit2xml command line parsing function.
*/

#pragma once
#ifndef BIT2XMLARGS_HPP
#define BIT2XMLARGS_HPP

#include <string>


/// program parameter denoting if stylesheets have to be generated
extern bool addStylesheet;

/// program parameter containing input bitfile name
extern std::string bitFileName;

/// program parameter containing output XML name
extern std::string xmlFileName;


/**
* \brief Parses command line of bit2xml program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
