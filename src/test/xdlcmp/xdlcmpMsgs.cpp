/**
* \file xdlcmpMsgs.cpp
* \brief Contains definition of text message constants for xdlcmp.
*/

#include <test/xdlcmp/xdlcmpMsgs.hpp>


const char* const SPLASH_MSG =
  "xdlcmp version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const READING_REFERENCE_XDL_MSG =
  "Reading reference XDL file...\n";

const char* const READING_TEST_XDL_MSG =
  "\nReading test XDL file...\n";

const char* const PARSING_XDL_HEADER_MSG =
  "Parsing XDL header...\n";

const char* const LOADING_DEVICE1_MSG =
  "Loading device ";

const char* const LOADING_DEVICE2_MSG =
  "... \n";

const char* const PARSING_XDL_MSG =
  "Parsing XDL...\n";

const char* const COMPARING_MSG =
  "\nComparing...\n";

const char* const FINISHED_MSG =
  "\nFinished.\n";

const char* const INFO_MSG =
  "\n\nUsage: xdlcmp [-dp <data path>] <reference XDL file>\n"
  "              <test XDL file> [<report file>]\n"
  "Where:\n"
  "<reference XDL file> = Name of reference XDL input file\n"
  "<test xdl file> = Name of test XDL input file\n"
  "<report file> = Name of report output file\n"
  "<data path> = Path to device data files\n\n"
  "xdlcmp: Reads in two XDL files and compares them.\n\n";


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

const char* const ERROR_NO_REFXDL_FILE_MSG =
  "No input reference XDL file specified!";

const char* const ERROR_NO_TESTXDL_FILE_MSG =
  "No input test XDL file specified!";

const char* const ERROR_NO_REPORT_FILE_MSG =
 "No output report file specified!";

extern const char* const ERROR_NO_DATAPATH_MSG =
  "No data path given!";


const char* const DEVICE_FILE_EXT = ".dev";

const char* const REPORT_FILE_EXT = ".txt";