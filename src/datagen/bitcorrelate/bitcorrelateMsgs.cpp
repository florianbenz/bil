/**
* \file bitcorrelateMsgs.cpp
* \brief Contains definition of text message constants for bitcorrelate.
*/

#include <datagen/bitcorrelate/bitcorrelateMsgs.hpp>


const char* const SPLASH_MSG =
  "bitcorrelate version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const PARSING_XDL_HEADER_MSG =
  "Parsing XDL header...\n";

const char* const LOADING_DEVICE1_MSG =
  "Loading device ";

const char* const LOADING_DEVICE2_MSG =
  "... \n";

const char* const PARSING_XDL_MSG =
  "Parsing XDL...\n";

const char* const LOADING_CFGTILEMAP_MSG =
  "\nLoading configuration tile map file...\n";

const char* const LOADING_BITFILE_MSG =
  "\nLoading bitfile...\n";

const char* const DECODING_BITSTREAM_MSG =
  "Decoding bitstream...\n";

const char* const LOADING_DEVICELIST_MSG =
  "Loading device list...\n";

const char* const LOADING_ADDRESSLAYOUT1_MSG =
  "Loading address layout for ";

const char* const LOADING_ADDRESSLAYOUT2_MSG =
  "...\n";

const char* const EXECUTING_BITSTREAM_MSG =
  "Executing bitstream...\n";

const char* const DOING_CORRELATION_MSG =
  "\nDoing correlation...\n";

const char* const WRITING_DATABASE_MSG =
  "\nWriting database...\n";

const char* const WRITING_STATS_MSG =
  "Writing statistics...\n";

const char* const FINISHED_MSG =
  "\nFinished.\n";

const char* const INFO_MSG =
  "\n\nUsage: bitcorrelate [-dp <datapath>] [-s <statsfile>]\n"
  "                    <xdlfile> <bitfile> <dbfile>\n"
  "Where:\n"
  "<xdlfile> = Name of input XDL design file\n"
  "<bitfile> = Name of corresponding bitfile\n"
  "<dbfile> = Name of output database file\n"
  "<datapath> = Path to device data files\n"
  "<statsfile> = Name of output statistics file\n\n"
  "bitcorrelate: Reads in a XDL design, and its corresponding bitstream.\n"
  "              By correlating both data sets it retrieves bit positions\n"
  "              of the PIPs and configuration options.\n\n";


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

const char* const ERROR_NO_BIT_FILE_MSG =
  "No bitfile specified!";

const char* const ERROR_NO_XDL_FILE_MSG =
  "No XDL file specified!";

const char* const ERROR_NO_DB_FILE_MSG =
  "No data base file specified!";

const char* const ERROR_NO_STATSFILE_MSG =
  "No statistics file specified!";

const char* const ERROR_NO_DATAPATH_MSG =
  "No data path specified!";


const char* const DEVICE_FILE_EXT = ".dev";

const char* const MAP_FILE_EXT = ".map";

const char* const V5DEVICES_FILENAME = "\\v5devices.lst";

const char* const CAL_FILE_EXT = ".cal";