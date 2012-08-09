/**
* \file bit2xmlMsgs.cpp
* \brief Contains definition of text message constants for bit2xml.
*/

#include <application/bit2xml/bit2xmlMsgs.hpp>


const char* const SPLASH_MSG =
  "bit2xml version 0.1\nCopyright (c) 2011 Florian Benz\n\n";

const char* const LOADING_BITFILE_MSG =
  "Loading bitfile...\n";

const char* const DECODING_BITSTREAM_MSG =
  "Decoding bitstream...\n";

const char* const WRITING_XML_MSG =
  "Writing XML...\n";

const char* const WRITING_STYLESHEETS_MSG =
  "Writing stylesheets...\n";

const char* const FINISHED_MSG =
  "Finished.\n";

const char* const INFO_MSG =
  "\n\nUsage: bit2xml [-s] <bitfile> [<xmlfile>]\n"
  "Where:\n"
  "-s = Create also xsl and css stylesheets\n"
  "<bitfile> = Name of input bitfile to open\n"
  "<xmlfile> = Name of output XML file\n\n"
  "bit2xml: Converts a Xilinx bitfile into a human readable xml file.\n\n";


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

const char* const ERROR_NO_INPUT_FILE_MSG=
  "No input bitfile specified!";


const char* const XML_HEADER =
  "xml";

const char* const XML_HEADER_DATA =
  "version=\"1.0\" encoding=\"iso-8859-1\"";

const char* const XML_STYLESHEET_HEADER =
  "xml-stylesheet";

const char* const XML_STYLESHEET_HEADER_DATA =
  "type=\"text/xsl\" href=\"disassembly.xsl\"";


const char* const XML_ELEMENT_BITFILE =
  "bitfile";

const char* const XML_ELEMENT_FILENAME =
  "filename";

const char* const XML_ELEMENT_META =
  "meta";

const char* const XML_ELEMENT_PACKETS =
  "packets";


const char* const XSL_FILENAME =
  "disassembly.xsl";

const char* const CSS_FILENAME =
  "disassembly.css";

const char* const XML_FILE_EXT =
  ".xml";