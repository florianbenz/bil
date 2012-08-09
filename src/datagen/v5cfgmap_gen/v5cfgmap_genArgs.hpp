/**
* \file v5cfgmap_genArgs.hpp
* \brief Contains declaration of v5cfgmap_gen command line parsing function.
*/

#pragma once
#ifndef V5CFGMAP_GENARGS_HPP
#define V5CFGMAP_GENARGS_HPP

#include <string>


/// program parameter containing input device file name
extern std::string deviceFileName;

/// program parameter containing data path name
extern std::string dataPathName;

/// program parameter containing output map file name
extern std::string mapFileName;


/**
* \brief Parses command line of v5cfgmap_gen program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
