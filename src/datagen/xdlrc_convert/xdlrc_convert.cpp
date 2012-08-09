/**
* \file xdlrc_convert.cpp
* \brief Contains the main method of the xdlrc_convert program.
* \details The xdlrc_convert program reads in a xdlrc file, and converts it into
*          a much smaller binary representation.
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <datagen/xdlrc_convert/xdlrc_convertArgs.hpp>
#include <datagen/xdlrc_convert/xdlrc_convertMsgs.hpp>
#include <exception/CommandLineException.hpp>
#include <xdlrc/model/Device.hpp>
#include <xdlrc/parser/XDLRCParser.hpp>


int main(int argc, char** argv)
{
    using namespace bil;

    try
    {
        // process given command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);

        // open xdlrc file and prepare parser
        std::ifstream inputStream(xdlrcFileName.c_str());
        XDLRCParser parser;
        Device device;

        // do first parsing pass
        std::cout << FIRST_PASS_MSG;
        parser.parseFirstPass(inputStream, device);
        // reset file pointer to beginning
        inputStream.clear();
        inputStream.seekg(0);
        // do second parsing pass
        std::cout << SECOND_PASS_MSG;
        parser.parseSecondPass();

        // write parsed data into file
        std::ofstream outputStream(outFileName.c_str(), std::ios::binary);
        writeBinary(device, outputStream);

        // finished
        std::cout << FINISHED_MSG;
    }
    catch (const CommandLineException& e)
    {
        std::cout << ERROR_MSG << e.what() << INFO_MSG;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cout << ERROR_UNKNOWN_MSG;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}