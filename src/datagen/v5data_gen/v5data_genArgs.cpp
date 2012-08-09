/**
* \file v5data_genArgs.cpp
* \brief Contains definition of v5data_gen command line parsing function.
*
*/

#include <datagen/v5data_gen/v5data_genArgs.hpp>
#include <datagen/v5data_gen/v5data_genMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;


std::string outputPath;


void parseCommandLine(int argc, char** argv)
{
    // test if there are enough parameters
    if (1 >= argc) throw CommandLineException(ERROR_TOO_FEW_PARAMETERS_MSG);

    // set program parameters to standard values
    outputPath.clear();

    // examine all program parameters
    std::string arg;
    size_t positionalOptIndex = 0;
    for (size_t i = 1; i < static_cast<size_t>(argc); ++i)
    {
        // copy parameter
        arg.assign(argv[i]);
        // no switches allowed
        if ('-' == arg[0])
        {
            std::string msg = ERROR_UNKNOWN_OPTION_1_MSG;
            msg.append(arg);
            msg.append(ERROR_UNKNOWN_OPTION_2_MSG);
            throw CommandLineException(msg);
        }
        // process positional arguments
        else
        {
            if (0 == positionalOptIndex) outputPath = arg;
            else throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            positionalOptIndex++;
        }
    }

    // enforce that output path ends with path separator
    if (outputPath.empty()) return;
    char lastChar = outputPath[outputPath.size()-1];
    if ('/' == lastChar) return;
    if ('\\' == lastChar) return;
    outputPath.push_back('/');
}