/**
* \file XDLParserImp2.cpp
* \brief Contains definition of XDLParserImp class.
*/

#include <exception/Exception.hpp>
#include <xdl/parser/XDLKeywords.hpp>
#include <xdl/parser/XDLParserImp.hpp>
#include <xdlrc/model/PIPDirection.hpp>

using namespace bil;
using namespace bil::xdlparser_detail;


void XDLParserImp::parseInstance()
{
    // read instance name and create new instance
    parseQuotedString();
    addInstance(m_quoteBuffer);

    // read primitive type name
    parseQuotedString();
    m_instance->primitiveTypeIndex(findPrimitiveType(m_quoteBuffer));

    // skip comma
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (',' != m_tok->separatorToken()) throw Exception();

    // read placement flag
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    const char* keyword = m_tok->wordToken();
    if (strcmp(keyword, XDLKeywords::PLACED) == 0)
    {
        // set placement flag
        m_instance->placed(true);
        m_instance->bonded(false);

        // read tile name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t tileIndex = findTile(m_tok->wordToken());
        m_instance->tileIndex(tileIndex);

        // read primitive site name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t siteIndex = findPrimitiveSite(m_tok->wordToken(), tileIndex);
        m_instance->primitiveSiteIndex(siteIndex);

        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();
    }
    else if (strcmp(keyword, XDLKeywords::UNPLACED) == 0)
    {
        // set placement flag
        m_instance->placed(false);

        StreamTokenizer::token_t tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_SEPARATOR == tokenType)
        {
            // no bonded flag, just comma
            m_instance->bonded(true);
            if (',' != m_tok->separatorToken()) throw Exception();
        }
        else if (StreamTokenizer::TT_WORD == tokenType)
        {
            // bonded flag present, check it
            keyword = m_tok->wordToken();
            if (strcmp(keyword, XDLKeywords::BONDED) == 0) m_instance->bonded(true);
            else if (strcmp(keyword, XDLKeywords::UNBONDED) == 0) m_instance->bonded(false);
            else throw Exception();

            // skip comma
            if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
            if (',' != m_tok->separatorToken()) throw Exception();
        }
        else throw Exception();
    }
    else throw Exception();

    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLKeywords::CFG) != 0) throw Exception();

    // skip cfg string
    parseQuotedString();
    (m_instance->attributes()).assign(m_quoteBuffer);

    // skip semicolon
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (';' != m_tok->separatorToken()) throw Exception();
}


void XDLParserImp::parseNet()
{
    // read net name and create new net
    parseQuotedString();
    addNet(m_quoteBuffer);
    // cache references to its pins and pips
    PinRefs& pinRefs = m_net->pinRefs();
    PIPRefs& pipRefs = m_net->pipRefs();

    // check if net type present
    StreamTokenizer::token_t tokenType = m_tok->nextToken();
    if (StreamTokenizer::TT_WORD == tokenType)
    {
        // read net type and set it
        m_net->type(NetType::fromString(m_tok->wordToken()));
        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();
    }
    else
    {
        // default net type
        m_net->type(NetType::WIRE);
        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != tokenType) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();
    }

    // parse out pins
    const char* keyword = 0;
    PinRef pinRef;
    for (;;)
    {
        // get next token
        tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_WORD != tokenType) break;
        keyword = m_tok->wordToken();

        // check if current token is out pin keyword
        if (strcmp(keyword, XDLKeywords::OUTPIN)) break;

        // parse instance name
        parseQuotedString();
        size_t instanceIndex = findInstance(m_quoteBuffer);
        pinRef.instanceIndex(instanceIndex);

        // read pin name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t pinIndex = findPin(m_tok->wordToken(), instanceIndex);
        pinRef.pinIndex(pinIndex);

        // add pin to net
        pinRefs.push_back(pinRef);

        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();
    }

    // parse in pins
    for (;;)
    {
        // check if current token is in pin keyword
        if (StreamTokenizer::TT_WORD != tokenType) break;
        if (strcmp(keyword, XDLKeywords::INPIN) != 0) break;

        // parse instance name
        parseQuotedString();
        size_t instanceIndex = findInstance(m_quoteBuffer);
        pinRef.instanceIndex(instanceIndex);

        // read pin name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t pinIndex = findPin(m_tok->wordToken(), instanceIndex);
        pinRef.pinIndex(pinIndex);

        // add pin to net
        pinRefs.push_back(pinRef);

        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();

        // get next token
        tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_WORD != tokenType) break;
        keyword = m_tok->wordToken();
    }

    // parse PIPs
    PIPRef pipRef;
    PIP pip;
    for (;;)
    {
        // check if current token is in PIP keyword
        if (StreamTokenizer::TT_WORD != tokenType) break;
        if (strcmp(keyword, XDLKeywords::PIP) != 0) break;

        // read tile name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t tileIndex = findTile(m_tok->wordToken());
        pipRef.tileIndex(tileIndex);
        // get tile
        const Tile& tile = m_tiles->at(tileIndex);
        // get tile type and its maps
        TileTypeEx& tileTypeEx = m_wirePIPMaps.at(tile.typeIndex());
        nameIndexMap_t& wireMap = tileTypeEx.wireMap;
        pipIndexMap_t& pipMap = tileTypeEx.pipMap;

        // read start wire
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t wireIndex = findWire(m_tok->wordToken(), wireMap);
        pip.startWireIndex(static_cast<unsigned short>(wireIndex));

        // read PIP direction keyword
        m_tok->wordChar('=');
        m_tok->wordChar('>');
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        pip.direction(PIPDirection::fromString(m_tok->wordToken()));
        m_tok->separatorChar('=');
        m_tok->separatorChar('>');

        // read end wire
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        wireIndex = findWire(m_tok->wordToken(), wireMap);
        pip.endWireIndex(static_cast<unsigned short>(wireIndex));

        // lookup PIP index, and add PIPRef to net
        pipRef.pipIndex(findPIP(pip, pipMap));
        pipRefs.push_back(pipRef);

        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();

        // get next token
        tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_WORD != tokenType) break;
        keyword = m_tok->wordToken();
    }

    // parse cfg node
    if (StreamTokenizer::TT_WORD == tokenType)
    {
        // skip keyword
        if (strcmp(keyword, XDLKeywords::CFG) != 0) throw Exception();
        // parse cfg string
        parseQuotedString();
        (m_net->attributes()).assign(m_quoteBuffer);
        // skip comma
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (',' != m_tok->separatorToken()) throw Exception();
        // read next token
        tokenType = m_tok->nextToken();
    }

    // skip semicolon
    if (StreamTokenizer::TT_SEPARATOR != tokenType) throw Exception();
    if (';' != m_tok->separatorToken()) throw Exception();
}


void XDLParserImp::parseQuotedString()
{
    // clear buffer
    char* quotePtr = m_quoteBuffer;
    char* quoteBufferEnd = quotePtr + QUOTE_BUFFER_SIZE;

    // skip double quote beginning
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if ('"' != m_tok->separatorToken()) throw Exception();

    // parse contents char by char
    m_tok->resetSyntax();
    bool escapeChar = false;
    for (;;)
    {
        // get next char
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken())
            throw Exception();
        char c = m_tok->separatorToken();

        // examine current char based on escape state
        if (escapeChar)
        {
            escapeChar = false;
            if ('"' == c)
            {
                if (quotePtr < quoteBufferEnd) *(quotePtr++) = '"';
            }
            else
            {
                if (quotePtr < quoteBufferEnd) *(quotePtr++) = '\\';
                if (quotePtr < quoteBufferEnd) *(quotePtr++) = c;
            }
        }
        else
        {
            if ('"' == c) break;
            else if ('\\' == c) escapeChar = true;
            else
            {
                if (quotePtr < quoteBufferEnd) *(quotePtr++) = c;
            }
        }
    }

    // terminate quote
    *quotePtr = 0;
    // restore normal syntax
    setupSyntax();
}