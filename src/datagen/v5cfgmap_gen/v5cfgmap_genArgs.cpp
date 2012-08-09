/**
* \file v5cfgmap_genArgs.cpp
* \brief Contains definition of v5cfgmap_gen command line parsing function.
*
*/

#include <datagen/v5cfgmap_gen/v5cfgmap_genArgs.hpp>
#include <datagen/v5cfgmap_gen/v5cfgmap_genMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;


std::string deviceFileName;
std::string dataPathName;
std::string mapFileName;


void parseCommandLine(int argc, char** argv)
{
    // test if there are enough parameters
    if (1 >= argc) throw CommandLineException(ERROR_TOO_FEW_PARAMETERS_MSG);

    // set program parameters to standard values
    deviceFileName.clear();
    dataPathName.clear();
    mapFileName.clear();

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
            switch (positionalOptIndex)
            {
            case 0: deviceFileName = arg; break;
            case 1: dataPathName = arg; break;
            case 2: mapFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // if data path set, enforce that it ends with path separator
    if (!dataPathName.empty())
    {
        char lastChar = dataPathName[dataPathName.size()-1];
        if (('/' != lastChar) && ('\\' != lastChar)) dataPathName.push_back('/');
    }

    // if mapFileName not set, set it
    if (mapFileName.empty())
    {
        size_t pos = deviceFileName.find_last_of(".");
        std::string deviceFileNameWithoutExt = deviceFileName.substr(0, pos);
        mapFileName = deviceFileNameWithoutExt + MAP_FILE_EXT;
    }
}