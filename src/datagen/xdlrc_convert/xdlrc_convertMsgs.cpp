/**
* \file xdlrc_convertMsgs.cpp
* \brief Contains definition of text message constants for xdlrc_convert.
*/

#include <datagen/xdlrc_convert/xdlrc_convertMsgs.hpp>


const char* const SPLASH_MSG =
  "xdlrc_convert version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const FIRST_PASS_MSG =
  "Doing first parsing pass...\n";

const char* const SECOND_PASS_MSG =
  "Doing second parsing pass...\n";

const char* const WRITING_DEVICE_FILE_MSG =
  "Writing device file...\n";

const char* const FINISHED_MSG =
  "Finished.\n";

const char* const INFO_MSG =
  "\n\nUsage: xdlrc_convert <infile> [<outfile>]\n"
  "Where:\n"
  "<infile> = Name of XDLRC file to parse\n"
  "<outfile> = Name of output file\n\n"
  "xdlrc_convert: Parses a xdlrc file, and converts it into a much\n"
  "               smaller binary representation.\n";


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


const char* const DEVICE_FILE_EXT = ".dev";