/**
* \file bitreverse.cpp
* \brief Contains the main method of the bitreverse program.
* \details The bitreverse program reads in a bitstream, and outputs a XDL file
*          with the design reconstructed from bitstream.
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <application/bitreverse/bitreverseArgs.hpp>
#include <application/bitreverse/bitreverseMsgs.hpp>
#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileReader.hpp>
#include <bitstream/V5BitstreamReader.hpp>
#include <bitstream/V5BitstreamDeviceDetector.hpp>
#include <cfgdecode/CfgDecoder.hpp>
#include <cfgdecode/CfgPrint.hpp>
#include <configuration/V5AddressLayout.hpp>
#include <configuration/V5AddressLayoutRegistry.hpp>
#include <correlation/cfgextraction/V5CfgExtractor.hpp>
#include <correlation/cfgextraction/V5CfgTileMap.hpp>
#include <deviceinfo/DeviceRegistry.hpp>
#include <exception/CommandLineException.hpp>
#include <mappingdb/DeviceCfgDb.hpp>
#include <packetprocessor/V5PacketProcessor.hpp>
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
        // get configuration data from bitstream
        std::string deviceName;
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

            // detect target device type
            std::cout << DETECTING_TARGETDEVICE_MSG;
            DeviceID::ID_t deviceID = detectV5DeviceType(bs);
            deviceName = deviceRegistry.lookup(deviceID);
            if (deviceName.empty()) throw Exception();

            // load address layout
            std::cout << LOADING_ADDRESSLAYOUT1_MSG << deviceName << LOADING_ADDRESSLAYOUT2_MSG;
            V5AddressLayout addressLayout;
            std::string calFileName = dataPathName + deviceName + CAL_FILE_EXT;
            std::ifstream calFileStream(calFileName.c_str(), std::ios::binary);
            readBinary(addressLayout, calFileStream);
            addressLayoutRegistry.insert(deviceID, addressLayout);

            // execute bitstream
            std::cout << EXECUTING_BITSTREAM_MSG;
            bs.runVisitor(packetProcessor);
        }


        //======================================================================
        // load device description and configuration tile map
        std::string devicePackageName = deviceName + packageName;
        Device device;
        V5CfgTileMap cfgTileMap;
        {
            std::cout << LOADING_DEVICE1_MSG << devicePackageName << LOADING_DEVICE2_MSG;
            std::string deviceFileName = dataPathName + devicePackageName + DEVICE_FILE_EXT;
            std::ifstream deviceInputStream(deviceFileName.c_str(), std::ios::binary);
            readBinary(device, deviceInputStream);

            std::cout << LOADING_CFGTILEMAP_MSG;
            std::string mapFileName = dataPathName + devicePackageName + MAP_FILE_EXT;
            std::ifstream mapInputStream(mapFileName.c_str(), std::ios::binary);
            readBinary(cfgTileMap, mapInputStream);
        }


        //======================================================================
        // load configuration database
        DeviceCfgDb cfgDatabase;
        {
            std::cout << LOADING_DATABASE_MSG;
            std::string dbFilename = dataPathName + devicePackageName + CFGDB_FILE_EXT;
            std::ifstream dbFileStream(dbFilename.c_str(), std::ios::binary);
            readBinary(cfgDatabase, dbFileStream);
        }


        //======================================================================
        // do reversal
        CfgDecoder decoder;
        {
            std::cout << DOING_REVERSAL_MSG;
            V5CfgExtractor cfgExtractor(configuration, cfgTileMap);
            decoder.decode(cfgExtractor, cfgDatabase, device);

            std::ofstream xdlFileStream(xdlFileName.c_str());
            printPIPs(decoder.pipRefs(), device, xdlFileStream);
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