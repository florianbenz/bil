/**
* \file v5data_gen.cpp
* \brief Contains the main method of the v5data_gen program.
* \details The v5data_gen program generates a file containing the names and IDs
*          of all Virtex-5 devices. For every device also a configuration layout
*          file is created.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <datagen/v5data_gen/v5data_genArgs.hpp>
#include <datagen/v5data_gen/v5data_genData.hpp>
#include <datagen/v5data_gen/v5data_genMsgs.hpp>
#include <deviceinfo/DeviceRegistry.hpp>
#include <exception/CommandLineException.hpp>


int main(int argc, char** argv)
{
    using namespace bil;

    try
    {
        // process given command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);

        // generate device registry
        DeviceRegistry devices;
        for (size_t i = 0; i < V5_DEVICE_COUNT; ++i)
            devices.insert(V5_DEVICE_IDS[i], V5_DEVICE_NAMES[i]);
        // write it to file
        std::cout << WRITING_DEVICE_LIST_MSG;
        std::string fileName = outputPath + DEVICE_REG_FILENAME;
        std::ofstream outputFile(fileName.c_str(), std::ios::binary);
        writeBinary(devices, outputFile);
        outputFile.close();

        // write address layouts
        std::cout << WRITING_CFG_LAYOUTS_MSG;
        for (size_t i = 0; i < V5_DEVICE_COUNT; ++i)
        {
            fileName = outputPath + V5_DEVICE_NAMES[i] + CFG_LAYOUT_EXT;
            outputFile.open(fileName.c_str(), std::ios::binary);
            writeBinary(V5_ADDRESS_LAYOUTS[i], outputFile);
            outputFile.close();
        }

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