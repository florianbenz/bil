/**
* \file bitextract.cpp
* \brief Contains the main method of the bitextract program.
* \details The bitextract program extracts the configuration frames out of a
*          Xilinx bitfile into a binary file.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <application/bitextract/bitextractArgs.hpp>
#include <application/bitextract/bitextractMsgs.hpp>
#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileReader.hpp>
#include <bitstream/V5BitstreamReader.hpp>
#include <bitstream/V5BitstreamDeviceDetector.hpp>
#include <configuration/V5AddressLayout.hpp>
#include <configuration/V5AddressLayoutRegistry.hpp>
#include <configuration/V5ConfigurationDump.hpp>
#include <deviceinfo/DeviceRegistry.hpp>
#include <exception/CommandLineException.hpp>
#include <packetprocessor/V5PacketProcessor.hpp>


int main(int argc, char** argv)
{
    using namespace bil;

    try
    {
        // process command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);

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
        std::string s = dataPathName + V5DEVICES_FILENAME;
        std::ifstream lstFileStream(s.c_str(), std::ios::binary);
        DeviceRegistry deviceRegistry;
        readBinary(deviceRegistry, lstFileStream);

        // detect target device type
        std::cout << DETECTING_TARGETDEVICE_MSG;
        DeviceID::ID_t deviceID = detectV5DeviceType(bs);
        s = deviceRegistry.lookup(deviceID);
        if (s.empty()) throw Exception();

        // load address layout
        std::cout << LOADING_ADDRESSLAYOUT1_MSG << s << LOADING_ADDRESSLAYOUT2_MSG;
        V5AddressLayout addressLayout;
        s = dataPathName + s + CAL_FILE_EXT;
        std::ifstream calFileStream(s.c_str(), std::ios::binary);
        readBinary(addressLayout, calFileStream);
        V5AddressLayoutRegistry addressLayoutRegistry;
        addressLayoutRegistry.insert(deviceID, addressLayout);

        // execute bitstream
        std::cout << EXECUTING_BITSTREAM_MSG;
        V5PacketProcessor packetProcessor(addressLayoutRegistry);
        bs.runVisitor(packetProcessor);

        // write configuration data
        std::cout << WRITING_CFG_MSG;
        std::ofstream cfgFileStream(outCfgFile.c_str(), std::ios::binary);
        std::ofstream indexFileStream(outIndexFile.c_str());
        indexFileStream << INDEX_FILE_HEADER;
        dumpConfiguration(packetProcessor.configuration(), cfgFileStream, indexFileStream);

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