/**
* \file xdlcmpArgs.cpp
* \brief Contains definition of xdlcmp command line parsing function.
*/

#include <test/xdlcmp/xdlcmpArgs.hpp>
#include <test/xdlcmp/xdlcmpMsgs.hpp>
#include <exception/CommandLineException.hpp>

using namespace bil;

std::string xdlRefFileName;
std::string xdlTestFileName;
std::string reportFileName;
std::string dataPathName;


void parseCommandLine(int argc, char** argv)
{
    // set program parameters to standard values
    xdlRefFileName.clear();
    xdlTestFileName.clear();
    reportFileName.clear();
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
            case 0: xdlRefFileName = arg; break;
            case 1: xdlTestFileName = arg; break;
            case 2: reportFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // first XDL file name must not be empty
    if (xdlRefFileName.empty()) throw CommandLineException(ERROR_NO_REFXDL_FILE_MSG);

    // second XDL file name must not be empty
    if (xdlTestFileName.empty()) throw CommandLineException(ERROR_NO_TESTXDL_FILE_MSG);

    // output file must not be empty
    if (reportFileName.empty()) throw CommandLineException(ERROR_NO_REPORT_FILE_MSG);

    // if data path set, enforce that it ends with path separator
    if (!dataPathName.empty())
    {
        char lastChar = dataPathName[dataPathName.size()-1];
        if (('/' != lastChar) && ('\\' != lastChar)) dataPathName.push_back('/');
    }
}