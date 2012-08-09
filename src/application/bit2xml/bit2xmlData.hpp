/**
* \file bit2xmlData.hpp
* \brief Contains declaration of constants holding the xsl and css stylesheets
*          for use with the bit2xml program.
*/

#pragma once
#ifndef BIT2XMLDATA_HPP
#define BIT2XMLDATA_HPP


/// size of XSL stylesheet
const size_t DISASSEMBLY_XSL_SIZE = 3704;

/// XSL stylesheet
extern const unsigned char DISASSEMBLY_XSL[DISASSEMBLY_XSL_SIZE];


/// size of CSS stylesheet
const size_t DISASSEMBLY_CSS_SIZE = 720;

/// CSS stylesheet
extern const unsigned char DISASSEMBLY_CSS[DISASSEMBLY_CSS_SIZE];


#endif
