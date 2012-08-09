/**
* \file xdlrc_convertArgs.hpp
* \brief Contains declaration of xdlrc_convert command line parsing function.
*/

#pragma once
#ifndef XDLRC_CONVERTARGS_HPP
#define XDLRC_CONVERTARGS_HPP

#include <string>


/// program parameter containing input xdlrc file name
extern std::string xdlrcFileName;

/// program parameter containing output file name
extern std::string outFileName;


/**
* \brief Parses command line of xdlrc_convert program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
