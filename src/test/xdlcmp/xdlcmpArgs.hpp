/**
* \file xdlcmpArgs.hpp
* \brief Contains declaration of xdlcmp command line parsing function.
*/

#pragma once
#ifndef XDLCMPARGS_HPP
#define XDLCMPARGS_HPP

#include <string>


/// program parameter containing reference input XDL file name
extern std::string xdlRefFileName;

/// program parameter containing test input XDL file name
extern std::string xdlTestFileName;

/// program parameter containing output report file name
extern std::string reportFileName;

/// program parameter containing data path name
extern std::string dataPathName;


/**
* \brief Parses command line of xdlcmp program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
