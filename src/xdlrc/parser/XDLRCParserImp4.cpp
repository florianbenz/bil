/**
* \file XDLRCParserImp4.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


void XDLRCParserImp::parseTileSummary()
{
    // skip site name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip site type
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip pin count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    size_t count;
    if (!m_tok->uintToken(count)) throw Exception();

    // skip wire count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip pip count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
}


void XDLRCParserImp::parseSummary()
{
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILES) != 0) throw Exception();
    // skip equal sign
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('=' != m_tok->separatorToken()) throw Exception();
    // skip tile count
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::SITES) != 0) throw Exception();
    // skip equal sign
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('=' != m_tok->separatorToken()) throw Exception();
    // skip primitive site count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::SITEDEFS) != 0) throw Exception();
    // skip equal sign
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('=' != m_tok->separatorToken()) throw Exception();
    // skip primitive definition count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip closing parenthesis (summary may end here)
    if ((StreamTokenizer::TT_SEPARATOR == m_tok->nextToken()) &&
        (')' == m_tok->separatorToken())) return;
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->tokenType()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::NUMPINS) != 0) throw Exception();
    // skip equal sign
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('=' != m_tok->separatorToken()) throw Exception();
    // skip pin definition count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip closing parenthesis (summary may end here)
    if ((StreamTokenizer::TT_SEPARATOR == m_tok->nextToken()) &&
        (')' == m_tok->separatorToken())) return;
    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->tokenType()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::NUMPIPS) != 0) throw Exception();
    // skip equal sign
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('=' != m_tok->separatorToken()) throw Exception();
    // skip pin definition count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
}