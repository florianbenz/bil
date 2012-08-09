/**
* \file bitcorrelate.cpp
* \brief Contains the main method of the bitcorrelate program.
* \details The bitcorrelate program reads in a XDL design, and its corresponding
*          bitstream. By correlating both data sets it retrieves bit positions
*          of the PIPs and configuration options.
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileReader.hpp>
#include <bitstream/V5BitstreamReader.hpp>
#include <configuration/V5AddressLayout.hpp>
#include <configuration/V5AddressLayoutRegistry.hpp>
#include <correlation/cfgextraction/V5CfgTileMap.hpp>
#include <correlation/cfgextraction/V5CfgExtractor.hpp>
#include <correlation/Correlator.hpp>
#include <datagen/bitcorrelate/bitcorrelateArgs.hpp>
#include <datagen/bitcorrelate/bitcorrelateMsgs.hpp>
#include <deviceinfo/DeviceNameUtil.hpp>
#include <deviceinfo/DeviceRegistry.hpp>
#include <exception/CommandLineException.hpp>
#include <mappingdb/DeviceCfgDb.hpp>
#include <mappingdb/DeviceCfgDbStats.hpp>
#include <packetprocessor/V5PacketProcessor.hpp>
#include <xdl/model/Design.hpp>
#include <xdl/parser/XDLParser.hpp>
#include <xdlrc/model/Device.hpp>

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
        // parse XDL file
        Design design;
        Device device;
        std::string devicePackageName;
        {
            // open XDL file and parse its header
            std::cout << PARSING_XDL_HEADER_MSG;
            XDLParser parser;
            std::ifstream xdlInputStream(xdlFileName.c_str());
            parser.parseHeader(xdlInputStream, design);
            devicePackageName = removeSpeed((design.deviceName()).c_str());

            // load device file of corresponding device
            std::cout << LOADING_DEVICE1_MSG << devicePackageName << LOADING_DEVICE2_MSG;
            std::string deviceFileName = dataPathName + devicePackageName + DEVICE_FILE_EXT;
            std::ifstream deviceInputStream(deviceFileName.c_str(), std::ios::binary);
            readBinary(device, deviceInputStream);

            // parse XDL
            std::cout << PARSING_XDL_MSG;
            parser.parseBody(device);
        }

        //======================================================================
        // load configuration tile map
        V5CfgTileMap cfgTileMap;
        {
            std::cout << LOADING_CFGTILEMAP_MSG;
            std::string mapFileName = dataPathName + devicePackageName + MAP_FILE_EXT;
            std::ifstream mapInputStream(mapFileName.c_str(), std::ios::binary);
            readBinary(cfgTileMap, mapInputStream);
        }

        //======================================================================
        // get configuration data from bitstream
        V5AddressLayoutRegistry addressLayoutRegistry;
        V5PacketProcessor packetProcessor(addressLayoutRegistry);
        V5Configuration& configuration = packetProcessor.configuration();
        {
            // load bitfile
            std::cout << LOADING_BITFILE_MSG;
            BitFileData bfd;
            std::ifstream bitfileStream(bitFileName.c_str(), std::ios::binary);
            readBitfile(bfd, bitfileStream);

            // construct bitstream from bitfile raw data
            std::cout << DECODING_BITSTREAM_MSG;
            Bitstream bs;
            readV5Bitstream(bs, bfd.bitstreamWords(), bfd.bitstreamWordCount());
            bfd.bitstreamWordCount(0);

            // read in available devices
            std::cout << LOADING_DEVICELIST_MSG;
            std::string deviceListFileName = dataPathName + V5DEVICES_FILENAME;
            std::ifstream lstFileStream(deviceListFileName.c_str(), std::ios::binary);
            DeviceRegistry deviceRegistry;
            readBinary(deviceRegistry, lstFileStream);

            // load address layout
            std::string deviceName = removePackageAndSpeed(devicePackageName.c_str());
            std::cout << LOADING_ADDRESSLAYOUT1_MSG << deviceName << LOADING_ADDRESSLAYOUT2_MSG;
            V5AddressLayout addressLayout;
            std::string calFileName = dataPathName + deviceName + CAL_FILE_EXT;
            std::ifstream calFileStream(calFileName.c_str(), std::ios::binary);
            readBinary(addressLayout, calFileStream);
            DeviceID::ID_t deviceID = deviceRegistry.lookup(deviceName);
            addressLayoutRegistry.insert(deviceID, addressLayout);

            // execute bitstream
            std::cout << EXECUTING_BITSTREAM_MSG;
            bs.runVisitor(packetProcessor);
        }


        //======================================================================
        // do correlation
        DeviceCfgDb cfgDatabase;
        std::cout << DOING_CORRELATION_MSG;
        {
            Correlator correlator;
            V5CfgExtractor cfgExtractor(configuration, cfgTileMap);
            correlator.run(cfgDatabase, design, device, cfgExtractor);
        }


        //======================================================================
        // save configuration mapping database
        std::cout << WRITING_DATABASE_MSG;
        std::ofstream dbFileStream(dbFileName.c_str(), std::ios::binary);
        writeBinary(cfgDatabase, dbFileStream);


        //======================================================================
        // write out stats
        std::cout << WRITING_STATS_MSG;
        {
            std::ofstream statsFileStream(statsFileName.c_str());
            DeviceCfgDbStats statsPrinter;
            statsPrinter.printStats(cfgDatabase, device, statsFileStream);
        }


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