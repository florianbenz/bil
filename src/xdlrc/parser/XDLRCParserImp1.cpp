/**
* \file XDLRCParserImp1.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>
#include <xdlrc/util/NameSplit.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


void XDLRCParserImp::parse1stTiles()
{
    // read row count
    unsigned rows;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(rows)) throw Exception();

    // read column count
    unsigned cols;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(cols)) throw Exception();

    // reserve tile memory
    m_tiles->reserve(rows * cols);

    // parse tiles
    for (;;)
    {
        // skip opening parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILE) != 0) throw Exception();
        parse1stTile();
    }
}


void XDLRCParserImp::parse1stTile()
{
    // read row position
    unsigned x;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(x)) throw Exception();

    // read column position
    unsigned y;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(y)) throw Exception();

    // read tile name and create new tile from it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    addTile(m_tok->wordToken());
    m_tile->row(static_cast<unsigned short>(x));
    m_tile->column(static_cast<unsigned short>(y));
    if (!extractPosition(m_tok->wordToken(), x, y)) throw Exception();
    m_tile->siteX(static_cast<unsigned short>(x));
    m_tile->siteY(static_cast<unsigned short>(y));

    // read tile type name and create/find corresponding type
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    addTileType(m_tok->wordToken());
    // set tile type
    m_tile->typeIndex(static_cast<unsigned short>(m_tileType->tag()));

    // read primitive site count and reserve site names
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    m_sites->reserve(count);

    // parse primitive sites
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken())  throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // parse primitive site if keyword matches
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PRIMITIVE_SITE) != 0) break;
        parse1stPrimitiveSite();
    }

    // parse wires
    for (;;)
    {
        // parse a wire if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::WIRE) != 0) break;
        parse1stWire();

        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    }

    // parse PIPs
    for (;;)
    {
        // parse a PIP if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PIP) != 0) break;
        parse1stPIP();

        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    }

    // skip keyword
    if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILE_SUMMARY) != 0) throw Exception();
    // parse tile summary
    parseTileSummary();

    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
}


void XDLRCParserImp::parse1stPrimitiveSite()
{
    // create new primitive site
    size_t count = m_sites->size();
    m_sites->push_back(PrimitiveSite());
    PrimitiveSite& primitiveSite = ((*m_sites)[count]);

    // read site name and set it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    (primitiveSite.name()).assign(m_tok->wordToken());

    // skip site type
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // read bonded flag and set it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    const char* s = m_tok->wordToken();
    if (strcmp(s, XDLRCKeywords::INTERNAL) == 0) primitiveSite.isBonded(false);
    else if (strcmp(s, XDLRCKeywords::BONDED) == 0) primitiveSite.isBonded(true);
    else if (strcmp(s, XDLRCKeywords::UNBONDED) == 0) primitiveSite.isBonded(false);
    else throw Exception();

    // skip pin wire count
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // pin wires
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PINWIRE) != 0) throw Exception();

        // skip pin name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip in/out keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        s = m_tok->wordToken();
        if ((strcmp(s, XDLRCKeywords::INPUT) != 0) &&
            (strcmp(s, XDLRCKeywords::OUTPUT) != 0))
            throw Exception();

        // skip wire name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();
    }
}


void XDLRCParserImp::parse1stWire()
{
    // read wire name and create/find it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    addWire(m_tok->wordToken());

    // skip connection count
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // connections
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::CONN) != 0) throw Exception();

        // skip destination tile name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip destination wire name
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();
    }
}


void XDLRCParserImp::parse1stPIP()
{
    // skip tile name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // read start wire and search for it on current tile
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    size_t startWireIndex = findWire(m_tok->wordToken(), *m_wireMap);

    // read PIP direction keyword
    m_tok->wordChar('=');
    m_tok->wordChar('>');
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    PIPDirection::direction_t dir = PIPDirection::fromString(m_tok->wordToken());
    m_tok->separatorChar('=');
    m_tok->separatorChar('>');

    // read end wire and search for it on current tile
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    size_t endWireIndex = findWire(m_tok->wordToken(), *m_wireMap);

    // create new PIP
    PIP pip;
    pip.startWireIndex(static_cast<unsigned short>(startWireIndex));
    pip.direction(dir);
    pip.endWireIndex(static_cast<unsigned short>(endWireIndex));
    // add it (if not already present)
    addPIP(pip);

    // skip parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' == m_tok->separatorToken()) return;
    if ('(' != m_tok->separatorToken()) throw Exception();

    // skip route-through name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    // skip route-through site type
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
    // skip closing parenthesis
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (')' != m_tok->separatorToken()) throw Exception();
}