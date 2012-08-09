/**
* \file bitextractArgs.hpp
* \brief Contains declaration of bitextract command line parsing function.
*/

#pragma once
#ifndef BITEXTRACTARGS_HPP
#define BITEXTRACTARGS_HPP

#include <string>


/// program parameter containing input bitfile name
extern std::string bitFileName;

/// program parameter containing data path name
extern std::string dataPathName;

/// program parameter containing output configuration file name
extern std::string outCfgFile;

/// program parameter containing output index file name
extern std::string outIndexFile;


/**
* \brief Parses command line of bitextract program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
