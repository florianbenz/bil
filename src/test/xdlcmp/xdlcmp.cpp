/**
* \file xdlcmp.cpp
* \brief Contains the main method of the xdlcmp program.
* \details The xdlcmp program reads in two XDL files and compares them.
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <deviceinfo/DeviceNameUtil.hpp>
#include <exception/CommandLineException.hpp>
#include <test/xdlcmp/xdlcmpAlgo.hpp>
#include <test/xdlcmp/xdlcmpArgs.hpp>
#include <test/xdlcmp/xdlcmpMsgs.hpp>
#include <xdl/parser/XDLParser.hpp>

using namespace bil;


int main(int argc, char** argv)
{
    try
    {
        //======================================================================
        // process given command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);


        //======================================================================
        // parse reference XDL file
        std::cout << READING_REFERENCE_XDL_MSG;
        Device device;
        Design refDesign;
        {
            // open XDL file and parse its header
            XDLParser parser;
            std::ifstream xdlInputStream(xdlRefFileName.c_str());
            std::cout << PARSING_XDL_HEADER_MSG;
            parser.parseHeader(xdlInputStream, refDesign);

            // load device file of corresponding device
            std::string devicePackageName = removeSpeed((refDesign.deviceName()).c_str());
            std::cout << LOADING_DEVICE1_MSG << devicePackageName << LOADING_DEVICE2_MSG;
            std::string deviceFileName = dataPathName + devicePackageName + DEVICE_FILE_EXT;
            std::ifstream deviceInputStream(deviceFileName.c_str(), std::ios::binary);
            readBinary(device, deviceInputStream);

            // parse XDL
            std::cout << PARSING_XDL_MSG;
            parser.parseBody(device);
        }

        //======================================================================
        // parse test XDL file
        std::cout << READING_TEST_XDL_MSG;
        Design testDesign;
        {
            // open XDL file and parse it
            XDLParser parser;
            std::ifstream xdlInputStream(xdlTestFileName.c_str());
            std::cout << PARSING_XDL_HEADER_MSG;
            parser.parseHeader(xdlInputStream, testDesign);
            std::cout << PARSING_XDL_MSG;
            parser.parseBody(device);
        }


        //======================================================================
        // get PIPs and compare them
        std::cout << COMPARING_MSG;
        PIPRefs refPIPRefs;
        getPIPs(refDesign, refPIPRefs);
        refDesign.clear();

        PIPRefs testPIPRefs;
        getPIPs(testDesign, testPIPRefs);
        testDesign.clear();

        std::ofstream reportOutputStream(reportFileName.c_str());
        comparePIPs(refPIPRefs, testPIPRefs, device, reportOutputStream);


        //======================================================================
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