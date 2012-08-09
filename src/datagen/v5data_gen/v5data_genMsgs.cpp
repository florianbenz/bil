/**
* \file v5data_genMsgs.cpp
* \brief Contains definition of text message constants for v5data_gen.
*/

#include <datagen/v5data_gen/v5data_genMsgs.hpp>


const char* const SPLASH_MSG =
  "v5data_gen version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const WRITING_DEVICE_LIST_MSG =
  "Writing device list...\n";

const char* const WRITING_CFG_LAYOUTS_MSG =
  "Writing configuration address layouts...\n";

const char* const FINISHED_MSG =
  "Finished.\n";

const char* const INFO_MSG =
  "\n\nUsage: v5data_gen [<outpath>]\n"
  "Where:\n"
  "<outpath> = Path where to put generated files\n\n"
  "v5data_gen: Generates a file containing the names and IDs of\n"
  "            all Virtex-5 devices. For every device also a\n"
  "            configuration layout file is created.\n";


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


const char* const DEVICE_REG_FILENAME = "v5devices.lst";

const char* const CFG_LAYOUT_EXT = ".cal";