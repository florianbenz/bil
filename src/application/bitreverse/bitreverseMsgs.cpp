/**
* \file bitreverseMsgs.cpp
* \brief Contains definition of text message constants for bitreverse.
*/

#include <application/bitreverse/bitreverseMsgs.hpp>


const char* const SPLASH_MSG =
  "bitreverse version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const LOADING_BITFILE_MSG =
  "\nLoading bitfile...\n";

const char* const DECODING_BITSTREAM_MSG =
  "Decoding bitstream...\n";

const char* const LOADING_DEVICELIST_MSG =
  "Loading device list...\n";

const char* const DETECTING_TARGETDEVICE_MSG =
"Detecting target device...\n";

const char* const LOADING_ADDRESSLAYOUT1_MSG =
  "Loading address layout for ";

const char* const LOADING_ADDRESSLAYOUT2_MSG =
  "...\n";

const char* const EXECUTING_BITSTREAM_MSG =
  "Executing bitstream...\n";

const char* const LOADING_DEVICE1_MSG =
  "\nLoading device ";

const char* const LOADING_DEVICE2_MSG =
  "... \n";

const char* const LOADING_CFGTILEMAP_MSG =
  "Loading configuration tile map file...\n";

const char* const LOADING_DATABASE_MSG =
  "Loading configuration data base...\n";

const char* const DOING_REVERSAL_MSG =
  "Doing reversal...\n";

const char* const FINISHED_MSG =
  "\nFinished.\n";

const char* const INFO_MSG =
  "\n\nUsage: bitreverse [-dp <data path>] <bitfile>\n"
  "                  <package name >[<xdlfile>]\n"
  "Where:\n"
  "<bitfile> = Name of input bitfile to process\n"
  "<package name> = Package name of bitfile target device\n"
  "<xdlfile> = Name of output XDL design file\n"
  "<data path> = Path to device data files\n\n"
  "bitreverse: Reads in a bitstream, and outputs a XDL file containing\n"
  "            the reconstructed design from bitstream.\n\n";


const char* const ERROR_MSG =
  "Error: ";

const char* const ERROR_UNKNOWN_MSG =
  "Unknown error occurred.\n";


const char* const ERROR_TOO_MANY_PARAMETERS_MSG =
  "Too many parameters!";

const char* const ERROR_UNKNOWN_OPTION_1_MSG =
  "Unknown option \"";

const char* const ERROR_UNKNOWN_OPTION_2_MSG =
  "\"!";

const char* const ERROR_NO_PACKAGENAME_MSG =
  "No device package name specified!";

const char* const ERROR_NO_BIT_FILE_MSG =
  "No input bitfile file specified!";

const char* const ERROR_NO_DATAPATH_MSG =
  "No data path specified!";


const char* const V5DEVICES_FILENAME = "\\v5devices.lst";

const char* const CAL_FILE_EXT = ".cal";

const char* const DEVICE_FILE_EXT = ".dev";

const char* const MAP_FILE_EXT = ".map";

const char* const CFGDB_FILE_EXT = ".cdb";

const char* const XDL_FILE_EXT = ".xdl";