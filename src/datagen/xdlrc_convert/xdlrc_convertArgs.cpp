/**
* \file xdlrc_convertArgs.cpp
* \brief Contains definition of xdlrc_convert command line parsing function.
*/

#include <datagen/xdlrc_convert/xdlrc_convertArgs.hpp>
#include <datagen/xdlrc_convert/xdlrc_convertMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;


std::string xdlrcFileName;
std::string outFileName;


void parseCommandLine(int argc, char** argv)
{
    // test if there are enough parameters
    if (1 >= argc) throw CommandLineException(ERROR_TOO_FEW_PARAMETERS_MSG);

    // set program parameters to standard values
    xdlrcFileName.clear();
    outFileName.clear();

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
            case 0: xdlrcFileName = arg; break;
            case 1: outFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // if out filename not set, set it
    if (outFileName.empty())
    {
        size_t pos = xdlrcFileName.find_last_of(".");
        std::string xdlrcFileNameWithoutExt = xdlrcFileName.substr(0, pos);
        outFileName = xdlrcFileNameWithoutExt + DEVICE_FILE_EXT;
    }
}