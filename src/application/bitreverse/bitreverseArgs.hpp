/**
* \file bitreverseArgs.hpp
* \brief Contains declaration of bitreverse command line parsing function.
*/

#pragma once
#ifndef BITREVERSEARGS_HPP
#define BITREVERSEARGS_HPP

#include <string>


/// program parameter containing input bitfile name
extern std::string bitFileName;

/// program parameter containing target device package name
extern std::string packageName;

/// program parameter containing output XDL file name
extern std::string xdlFileName;

/// program parameter containing data path name
extern std::string dataPathName;


/**
* \brief Parses command line of bitreverse program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
