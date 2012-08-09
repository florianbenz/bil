/**
* \file bitextractMsgs.cpp
* \brief Contains definition of text message constants for bitextract.
*/

#include <application/bitextract/bitextractMsgs.hpp>


const char* const SPLASH_MSG =
  "bitextract version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const LOADING_BITFILE_MSG =
  "Loading bitfile...\n";

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

const char* const WRITING_CFG_MSG =
  "Writing configuration data...\n";

const char* const FINISHED_MSG =
  "Finished.\n";

const char* const INFO_MSG =
  "\n\nUsage: bitextract [-dp <datapath>] <bitfile>\n"
  "                  [<cfgfile> <indexfile>]\n"
  "Where:\n"
  "<bitfile> = Name of input bitfile to open\n"
  "<cfgfile> = Name of output binary configuration data file\n"
  "<indexfile> = Name of output text index file\n"
  "<datapath> = Path to device data files\n\n"
  "bitextract: Extracts configuration frames out of a Xilinx bitfile into a\n"
  "            binary file.\n\n";


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

const char* const ERROR_NO_INPUT_FILE_MSG =
  "No input bitfile specified!";

const char* const ERROR_NO_DATAPATH_MSG =
  "No data path specified!";


const char* const V5DEVICES_FILENAME =
  "\\v5devices.lst";

const char* const CAL_FILE_EXT =
  ".cal";

const char* const CFG_FILE_EXT =
  ".bin";

const char* const INDEX_FILE_EXT =
  ".txt";

const char* const INDEX_FILE_HEADER =
  "; Created by bitextract\n"
  "; Lines are laid out as follows:\n"
  "; <raw frame address> <byte offset in configuration file> <decoded frame address>:<column type>\n\n";