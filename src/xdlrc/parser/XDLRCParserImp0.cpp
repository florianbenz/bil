/**
* \file XDLRCParserImp0.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


const size_t TILETYPE_RESERVE_COUNT = 100;


XDLRCParserImp::XDLRCParserImp():
  m_secondPassEnabled(false),
  m_tileMap(),
  m_tileTypeMap(),
  m_tileTypesEx(),
  m_primitiveTypeMap(),
  m_pinMaps()
{

}


void XDLRCParserImp::parseFirstPass(StreamTokenizer& tokenizer, Device& device)
{
    // clearAll out everything (temporary data and pointers)
    clearAll();

    // store pointer to tokenizer and prepare it
    m_tok = &tokenizer;
    setupSyntax();

    // clear destination object and store pointers to its sub-objects
    device.clear();
    m_device = &device;
    m_tiles = &(device.tiles());
    m_tileTypes = &(device.tileTypes());
    m_primitiveTypes = &(device.primitiveTypes());

    // reserve memory beforehand for tile types, since they are not directly
    // mentioned in XDLRC and will be inferred
    m_tileTypes->reserve(TILETYPE_RESERVE_COUNT);
    m_tileTypesEx.reserve(TILETYPE_RESERVE_COUNT);

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::RESOURCE_REPORT) != 0) throw Exception();
    // skip version string
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    // read device name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    (m_device->name()).assign(m_tok->wordToken());
    // skip family name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD !=m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILES) != 0) throw Exception();
    parse1stTiles();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::PRIMITIVE_DEFS) != 0) throw Exception();
    parse1stPrimitiveDefs();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::SUMMARY) != 0) throw Exception();
    parseSummary();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();

    // reset pointers for safety
    resetTempPointers();
    // everything ok, second pass possible
    m_secondPassEnabled = true;
}


void XDLRCParserImp::parseSecondPass()
{
    // check if second pass can be made
    if (!m_secondPassEnabled) throw Exception();
    m_secondPassEnabled = false;
    // reset pointers for safety
    resetTempPointers();

    // prepare tokenizer
    setupSyntax();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::RESOURCE_REPORT) != 0) throw Exception();
    // skip version string
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    // read and check device name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if ((m_device->name()).compare(m_tok->wordToken()) != 0) throw Exception();
    // skip family name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip opening parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('(' != m_tok->separatorToken()) throw Exception();
    // skip keyword
    if (StreamTokenizer::TT_WORD !=m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILES) != 0) throw Exception();
    parse2ndTiles();

    // clearAll out everything (temporary data and pointers)
    clearAll();
}