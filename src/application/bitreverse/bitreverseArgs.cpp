/**
* \file bitreverseArgs.cpp
* \brief Contains definition of bitreverse command line parsing function.
*/

#include <application/bitreverse/bitreverseArgs.hpp>
#include <application/bitreverse/bitreverseMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;

std::string bitFileName;
std::string packageName;
std::string xdlFileName;
std::string dataPathName;


void parseCommandLine(int argc, char** argv)
{
    // set program parameters to standard values
    bitFileName.clear();
    packageName.clear();
    xdlFileName.clear();
    dataPathName.clear();

    // examine all program parameters
    std::string arg;
    size_t positionalOptIndex = 0;
    size_t argCount = static_cast<size_t>(argc);
    for (size_t i = 1; i < argCount; ++i)
    {
        // copy parameter
        arg.assign(argv[i]);
        // process switches
        if ('-' == arg[0])
        {
            if ("-dp" == arg)
            {
                if ((++i) >= argCount)
                    throw CommandLineException(ERROR_NO_DATAPATH_MSG);
                dataPathName.assign(argv[i]);
            }
            else
            {
                std::string msg = ERROR_UNKNOWN_OPTION_1_MSG;
                msg.append(arg);
                msg.append(ERROR_UNKNOWN_OPTION_2_MSG);
                throw CommandLineException(msg);
            }
        }
        // process positional arguments
        else
        {
            switch (positionalOptIndex)
            {
            case 0: bitFileName = arg; break;
            case 1: packageName = arg; break;
            case 2: xdlFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // bitfile name must not be empty
    if (bitFileName.empty()) throw CommandLineException(ERROR_NO_BIT_FILE_MSG);

    // package name must not be empty
    if (packageName.empty()) throw CommandLineException(ERROR_NO_PACKAGENAME_MSG);

    // if XDL input file is empty, then set it to the input file name and
    // change its file extension
    if (xdlFileName.empty())
    {
        size_t pos = bitFileName.find_last_of(".");
        std::string bitFileNameWithoutExt = bitFileName.substr(0, pos);
        xdlFileName = bitFileNameWithoutExt + XDL_FILE_EXT;
    }

    // if data path set, enforce that it ends with path separator
    if (!dataPathName.empty())
    {
        char lastChar = dataPathName[dataPathName.size()-1];
        if (('/' != lastChar) && ('\\' != lastChar)) dataPathName.push_back('/');
    }
}