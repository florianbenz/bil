/**
* \file v5cfgmap_genMsgs.cpp
* \brief Contains definition of text message constants for v5cfgmap_gen.
*/

#include <datagen/v5cfgmap_gen/v5cfgmap_genMsgs.hpp>


const char* const SPLASH_MSG =
  "v5cfgmap_gen version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const LOADING_DEVICE_FILE_MSG =
  "Loading device file...\n";

const char* const LOADING_ADDRESS_LAYOUT1_MSG =
  "Loading address layout for ";

const char* const LOADING_ADDRESS_LAYOUT2_MSG =
  "...\n";

const char* const CREATING_TILEMAP_MSG =
  "Creating configuration tile map...\n";

const char* const WRITING_TILEMAP_FILE_MSG =
  "Writing configuration tile map file...\n";

const char* const FINISHED_MSG =
  "Finished.\n";

const char* const INFO_MSG =
  "\n\nUsage: v5cfgmap_gen <infile> [<datapath> <outfile>]\n"
  "Where:\n"
  "<infile> = Name of device file to open\n"
  "<datapath> = Path to device data files\n"
  "<outfile> = Name of output map file\n\n"
  "v5cfgmap_gen: Generates the configuration tile map file out of a Virtex-5\n"
  "              device file describing which tile gets configured by which\n"
  "              configuration frames.\n";


const char* const ERROR_MSG =
  "Error: ";

const char* const ERROR_UNKNOWN_MSG =
  "Unknown error occurred.\n";


const char* const ERROR_TOO_FEW_PARAMETERS_MSG =
  "Too few parameters!";

const char* const ERROR_TOO_MANY_PARAMETERS_MSG =
  "Too many parameters!";

const char* const ERROR_UNKNOWN_OPTION_1_MSG =
  "Unknown option \"";

const char* const ERROR_UNKNOWN_OPTION_2_MSG =
  "\"!";


const char* const CAL_FILE_EXT = ".cal";

const char* const MAP_FILE_EXT = ".map";