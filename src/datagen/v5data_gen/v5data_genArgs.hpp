/**
* \file v5data_genArgs.hpp
* \brief Contains declaration of v5data_gen command line parsing function.
*/

#pragma once
#ifndef V5DATA_GENARGS_HPP
#define V5DATA_GENARGS_HPP

#include <string>


/// program parameter containing output path
extern std::string outputPath;


/**
* \brief Parses command line of v5data_gen program.
* \param argc Program argument count.
* \param argv Program arguments array.
* \throws .
*/
void parseCommandLine(int argc, char** argv);


#endif
