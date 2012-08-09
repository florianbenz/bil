/**
* \file bitcorrelateArgs.hpp
* \brief Contains declaration of bitcorrelate command line parsing function.
*/

#pragma once
#ifndef BITCORRELATEARGS_HPP
#define BITCORRELATEARGS_HPP

#include <string>


/// program parameter containing input XDL file name
extern std::string xdlFileName;

/// program parameter containing input bitfile name
extern std::string bitFileName;

/// program parameter containing output database file name
extern std::string dbFileName;

/// program parameter containing output statistics file name
extern std::string statsFileName;

/// program parameter containing data path name
extern std::string dataPathName;


/**
* \brief Parses command line of bitcorrelate program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
