/**
* \file bitcorrelateArgs.cpp
* \brief Contains definition of bitcorrelate command line parsing function.
*/

#include <datagen/bitcorrelate/bitcorrelateArgs.hpp>
#include <datagen/bitcorrelate/bitcorrelateMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;

std::string xdlFileName;
std::string bitFileName;
std::string dbFileName;
std::string statsFileName;
std::string dataPathName;


void parseCommandLine(int argc, char** argv)
{
    // set program parameters to standard values
    xdlFileName.clear();
    bitFileName.clear();
    dbFileName.clear();
    statsFileName.clear();
    dataPathName.clear();

    // examine all program parameters
    std::string arg;
    size_t positionalOptIndex = 0;
    size_t argCount = static_cast<size_t>(argc);
    for (size_t i = 1; i < argCount; ++i)
    {
        // copy parameter
        arg.assign(argv[i]);
        // no switches allowed
        if ('-' == arg[0])
        {
            if ("-dp" == arg)
            {
                if ((++i) >= argCount)
                    throw CommandLineException(ERROR_NO_DATAPATH_MSG);
                dataPathName.assign(argv[i]);
            }
            else if ("-s" == arg)
            {
                if ((++i) >= argCount)
                    throw CommandLineException(ERROR_NO_STATSFILE_MSG);
                statsFileName.assign(argv[i]);
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
            case 0: xdlFileName = arg; break;
            case 1: bitFileName = arg; break;
            case 2: dbFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // XDL name must not be empty
    if (xdlFileName.empty()) throw CommandLineException(ERROR_NO_XDL_FILE_MSG);

    // bitfile name must not be empty
    if (bitFileName.empty()) throw CommandLineException(ERROR_NO_BIT_FILE_MSG);

    // data base name must not be empty
    if (dbFileName.empty()) throw CommandLineException(ERROR_NO_DB_FILE_MSG);

    // if data path set, enforce that it ends with path separator
    if (!dataPathName.empty())
    {
        char lastChar = dataPathName[dataPathName.size()-1];
        if (('/' != lastChar) && ('\\' != lastChar)) dataPathName.push_back('/');
    }
}