/**
* \file bitextractArgs.cpp
* \brief Contains definition of bitextract command line parsing function.
*/

#include <application/bitextract/bitextractArgs.hpp>
#include <application/bitextract/bitextractMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;


std::string bitFileName;
std::string dataPathName;
std::string outCfgFile;
std::string outIndexFile;


void parseCommandLine(int argc, char** argv)
{
    // set program parameters to standard values
    bitFileName.clear();
    dataPathName.clear();
    outCfgFile.clear();
    outIndexFile.clear();

    // examine all program parameters
    std::string arg;
    size_t positionalOptIndex = 0;
    size_t argCount = static_cast<size_t>(argc);
    for (size_t i = 1; i < argCount; ++i)
    {
        // copy parameter
        arg.assign(argv[i]);
        // process named arguments/switches
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
            case 1: outCfgFile = arg; break;
            case 2: outIndexFile = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // check required bitfile name
    if (bitFileName.empty()) throw CommandLineException(ERROR_NO_INPUT_FILE_MSG);

    // if data path set, enforce that it ends with path separator
    if (!dataPathName.empty())
    {
        char lastChar = dataPathName[dataPathName.size()-1];
        if (('/' != lastChar) && ('\\' != lastChar)) dataPathName.push_back('/');
    }

    // set output configuration and output index file name, if not set
    if (outCfgFile.empty() || outIndexFile.empty())
    {
        size_t pos = bitFileName.find_last_of(".");
        std::string bitFileNameWithoutExt = bitFileName.substr(0, pos);
        if (outCfgFile.empty()) outCfgFile = bitFileNameWithoutExt + CFG_FILE_EXT;
        if (outIndexFile.empty()) outIndexFile = bitFileNameWithoutExt + INDEX_FILE_EXT;
    }
}