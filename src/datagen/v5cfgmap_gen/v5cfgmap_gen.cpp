/**
* \file v5cfgmap_gen.cpp
* \brief Contains the main method of the v5cfgmap_gen program.
* \details The v5cfgmap_gen program reads in a device description, and generates
*          the configuration tile map (describing which tiles get configured by
*          which configuration frames) out of this.
*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <datagen/v5cfgmap_gen/v5cfgmap_genAlgo.hpp>
#include <datagen/v5cfgmap_gen/v5cfgmap_genArgs.hpp>
#include <datagen/v5cfgmap_gen/v5cfgmap_genMsgs.hpp>
#include <deviceinfo/DeviceNameUtil.hpp>
#include <exception/CommandLineException.hpp>


int main(int argc, char** argv)
{
    using namespace bil;

    try
    {
        // process given command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);

        // load device file
        std::cout << LOADING_DEVICE_FILE_MSG;
        Device device;
        std::ifstream deviceFileStream(deviceFileName.c_str(), std::ios::binary);
        readBinary(device, deviceFileStream);

        // load address layout
        std::string deviceName = removePackageAndSpeed((device.name()).c_str());
        std::cout << LOADING_ADDRESS_LAYOUT1_MSG << deviceName << LOADING_ADDRESS_LAYOUT2_MSG;
        V5AddressLayout addressLayout;
        std::string calFileName = dataPathName + deviceName + CAL_FILE_EXT;
        std::ifstream calInputStream(calFileName.c_str(), std::ios::binary);
        readBinary(addressLayout, calInputStream);

        // create mapping
        std::cout << CREATING_TILEMAP_MSG;
        V5CfgTileMap map;
        generateCfgTileMap(map, device, addressLayout);

        // write mapping
        std::cout << WRITING_TILEMAP_FILE_MSG;
        std::ofstream mapFileStream(mapFileName.c_str(), std::ios::binary);
        writeBinary(map, mapFileStream);

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