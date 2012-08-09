/**
* \file XDLRCParserImp2.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


void XDLRCParserImp::parse1stPrimitiveDefs()
{
    // read primitive definition count
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    // reserve memory for primitive definitions and pin maps
    m_primitiveTypes->reserve(count);
    m_pinMaps.reserve(count);

    // parse primitive definitions
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PRIMITIVE_DEF) != 0) throw Exception();
        parse1stPrimitiveDef();
    }
}


void XDLRCParserImp::parse1stPrimitiveDef()
{
    // read primitive type name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    addPrimitiveType(m_tok->wordToken());

    // read pin count and reserve pins
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    m_pins->reserve(count);

    // read element count and reserve elements
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    m_elements->reserve(count);

    // parse pins
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken())  throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // parse pin if keyword matches
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PIN) != 0) break;
        parse1stPin();
    }

    // parse elements
    for (;;)
    {
        // parse an element if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::ELEMENT) != 0) break;
        parse1stElement();

        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    }
}


void XDLRCParserImp::parse1stPin()
{
    // read external pin name and create pin from it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    addPin(m_tok->wordToken());

    // skip internal name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // read input/output keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    const char* s = m_tok->wordToken();
    if (strcmp(s, XDLRCKeywords::INPUT) == 0) m_pin->isInput(true);
    else if (strcmp(s, XDLRCKeywords::OUTPUT) == 0) m_pin->isInput(false);
    else throw Exception();

    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
}


void XDLRCParserImp::parse1stElement()
{
    // add element
    size_t count = m_elements->size();
    m_elements->push_back(Element());
    Element& element = (*m_elements)[count];
    ConfigurationOptions& options = element.options();

    // read element name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    (element.name()).assign(m_tok->wordToken());

    // skip  pin/connection count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // parse pins
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PIN) != 0) break;

        // skip name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip input/output keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        const char* s = m_tok->wordToken();
        if ((strcmp(s, XDLRCKeywords::INPUT) != 0) &&
            (strcmp(s, XDLRCKeywords::OUTPUT) != 0))
            throw Exception();

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();
    }

    // parse configuration options
    for (;;)
    {
        // parse a configuration option if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::CFG) != 0) break;

        // parse option list
        m_tok->wordChar('#');
        m_tok->wordChar('<');
        m_tok->wordChar('>');
        m_tok->wordChar(':');
        for (;;)
        {
            if (StreamTokenizer::TT_SEPARATOR == m_tok->nextToken()) break;
            if (StreamTokenizer::TT_WORD != m_tok->tokenType()) throw Exception();
            options.push_back(m_tok->wordToken());
        }
        m_tok->commentChar('#');
        m_tok->separatorChar('<');
        m_tok->separatorChar('>');
        m_tok->separatorChar(':');
        if (')' != m_tok->separatorToken()) throw Exception();

        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    }

    // parse connections
    for (;;)
    {
        // parse a connection if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::CONN) != 0) break;

        // skip source element name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip source element pin
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip connection symbol
        m_tok->wordChar('=');
        m_tok->wordChar('<');
        m_tok->wordChar('>');
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        const char* s = m_tok->wordToken();
        if ((strcmp(s, XDLRCKeywords::CONN_R_SYMBOL) != 0) &&
            (strcmp(s, XDLRCKeywords::CONN_L_SYMBOL) != 0))
            throw Exception();
        m_tok->separatorChar('=');
        m_tok->separatorChar('<');
        m_tok->separatorChar('>');

        // skip destination element name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip destination element pin
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();

        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    }
}