/**
* \file bit2xmlArgs.cpp
* \brief Contains definition of bit2xml command line parsing function.
*/

#include <application/bit2xml/bit2xmlArgs.hpp>
#include <application/bit2xml/bit2xmlMsgs.hpp>
#include <exception/CommandLineException.hpp>
#include <exception/Exception.hpp>

using namespace bil;


bool addStylesheet;
std::string bitFileName;
std::string xmlFileName;


void parseCommandLine(int argc, char** argv)
{
    // set program parameters to standard values
    addStylesheet = false;
    bitFileName.clear();
    xmlFileName.clear();

    // examine all program parameters
    std::string arg;
    size_t positionalOptIndex = 0;
    for (size_t i = 1; i < static_cast<size_t>(argc); ++i)
    {
        // copy parameter
        arg.assign(argv[i]);
        // process named arguments/switches
        if ('-' == arg[0])
        {
            if ("-s" == arg) addStylesheet = true;
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
            case 1: xmlFileName = arg; break;
            default: throw CommandLineException(ERROR_TOO_MANY_PARAMETERS_MSG);
            }
            positionalOptIndex++;
        }
    }

    // check required bitfile name
    if (bitFileName.empty()) throw CommandLineException(ERROR_NO_INPUT_FILE_MSG);
    // set XML file name, if not set
    if (xmlFileName.empty())
    {
        size_t pos = bitFileName.find_last_of(".");
        std::string bitFileNameWithoutExt = bitFileName.substr(0, pos);
        xmlFileName = bitFileNameWithoutExt + XML_FILE_EXT;
    }
}