/**
* \file XDLRCParserImp3.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


void XDLRCParserImp::parse2ndTiles()
{
    // skip row count
    unsigned rows;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(rows)) throw Exception();

    // skip column count
    unsigned cols;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(cols)) throw Exception();

    // parse tiles
    m_tileIndex = 0;
    for (;;)
    {
        // skip opening parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::TILE) != 0) throw Exception();
        parse2ndTile();
        // keep track of tile index
        ++m_tileIndex;
    }
}


void XDLRCParserImp::parse2ndTile()
{
    // fetch corresponding tile and its primitive sites
    m_tile = &(m_tiles->at(m_tileIndex));
    m_sites = &(m_tile->primitiveSites());
    // get its tile type
    m_tileType = &(m_tileTypes->at(m_tile->typeIndex()));
    m_tileTypeEx = &(m_tileTypesEx.at(m_tile->typeIndex()));
    // get site types, wires and wire map of tile type
    m_siteTypes = &(m_tileType->siteTypes());
    m_wires = &(m_tileType->wires());
    m_wireMap = &(m_tileTypeEx->wireMap);

    // read row position and check it
    unsigned pos;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(pos)) throw Exception();
    if (m_tile->row() != pos) throw Exception();

    // read column position and check it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(pos)) throw Exception();
    if (m_tile->column() != pos) throw Exception();

    // read tile name and check it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if ((m_tile->name()).compare(m_tok->wordToken()) != 0) throw Exception();

    // read tile type name and check it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if ((m_tileType->name()).compare(m_tok->wordToken()) != 0) throw Exception();

    // skip primitive site count
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();

    // parse primitive sites
    m_primitiveSiteIndex = 0;
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // parse primitive site if keyword matches
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PRIMITIVE_SITE) != 0) break;
        // determine if site type has to be written
        if (m_tileTypeEx->writeSiteTypes) parse2ndPrimitiveSite();
        else parse2ndPrimitiveSiteSkip();
        // keep track of site index
        ++m_primitiveSiteIndex;
    }
    // a site type is only written once
    m_tileTypeEx->writeSiteTypes = false;

    // parse wires
    for (;;)
    {
        // parse a wire if keyword matches
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::WIRE) != 0) break;
        parse2ndWire();

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
        parse2ndPIP();

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


void XDLRCParserImp::parse2ndPrimitiveSite()
{
    // fetch corresponding primitive site
    PrimitiveSite& site = m_sites->at(m_primitiveSiteIndex);

    // read site name and check it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if ((site.name()).compare(m_tok->wordToken()) != 0) throw Exception();

    // read primitive type name and get its index
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    size_t primitiveTypeIndex = findPrimitiveType(m_tok->wordToken());
    // get primitive type, its pin list and pin map
    m_primitiveType = &(m_primitiveTypes->at(primitiveTypeIndex));
    m_pins = &(m_primitiveType->pins());
    m_pinMap = &(m_pinMaps.at(m_primitiveType->tag()));

    // read keyword and check bonded flag
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    const char* s = m_tok->wordToken();
    bool bonded;
    if (strcmp(s, XDLRCKeywords::INTERNAL) == 0) bonded = false;
    else if (strcmp(s, XDLRCKeywords::BONDED) == 0) bonded = true;
    else if (strcmp(s, XDLRCKeywords::UNBONDED) == 0) bonded = false;
    else throw Exception();
    if (site.isBonded() != bonded) throw Exception();

    // create new site type
    size_t siteTypeCount = m_siteTypes->size();
    m_siteTypes->push_back(PrimitiveSiteType());
    m_siteType = &((*m_siteTypes)[siteTypeCount]);
    // set its primitive type index
    m_siteType->primitiveTypeIndex(static_cast<unsigned short>(primitiveTypeIndex));
    // cache pointer to its pin wires
    m_pinWires = &(m_siteType->pinWires());

    // read pin wire count (lower bound)
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    m_pinWires->reserve(count);

    // pin wires
    PinWire pinWire;
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::PINWIRE) != 0) throw Exception();

        // read pin name, get pin index and pin
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t pinIndex = findPin(m_tok->wordToken());
        m_pin = &(m_pins->at(pinIndex));

        // read in/out keyword and check
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        s = m_tok->wordToken();
        bool inputFlag;
        if (strcmp(s, XDLRCKeywords::INPUT) == 0) inputFlag = true;
        else if (strcmp(s, XDLRCKeywords::OUTPUT) == 0) inputFlag = false;
        else throw Exception();
        if (m_pin->isInput() != inputFlag) throw Exception();

        // read wire name and search it in current tile types wire map
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t wireIndex = findWire(m_tok->wordToken(), *m_wireMap);

        // create and add pin wire
        pinWire.pinIndex(static_cast<unsigned short>(pinIndex));
        pinWire.wireIndex(static_cast<unsigned short>(wireIndex));
        m_pinWires->push_back(pinWire);

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();
    }
}


void XDLRCParserImp::parse2ndPrimitiveSiteSkip()
{
    // skip site name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip primitive type name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip keyword and check bonded flag
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    const char* s = m_tok->wordToken();
    if ((strcmp(s, XDLRCKeywords::INTERNAL) != 0) &&
        (strcmp(s, XDLRCKeywords::BONDED) != 0) &&
        (strcmp(s, XDLRCKeywords::UNBONDED) != 0))
    throw Exception();

    // skip pin wire count
    size_t count;
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


void XDLRCParserImp::parse2ndWire()
{
    // read wire name and find it
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    size_t wireIndex = findWire(m_tok->wordToken(), *m_wireMap);
    Wire& wire = m_wires->at(wireIndex);
    m_connections = &(wire.connections());

    // read connection count and reserve it (min value)
    size_t count;
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (!m_tok->uintToken(count)) throw Exception();
    m_connections->reserve(count);

    // connections
    WireConnection connection;
    for (;;)
    {
        // skip parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' == m_tok->separatorToken()) return;
        if ('(' != m_tok->separatorToken()) throw Exception();

        // skip keyword
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        if (strcmp(m_tok->wordToken(), XDLRCKeywords::CONN) != 0) throw Exception();

        // read destination tile name and find tile
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        size_t tileIndex = findTile(m_tok->wordToken());
        Tile& tile = m_tiles->at(tileIndex);
        size_t tileTypeIndex = tile.typeIndex();
        // set connection tile type and offset
        connection.xOffset(tile.siteX() - (m_tile->siteX()));
        connection.yOffset(tile.siteY() - (m_tile->siteY()));
        connection.tileTypeIndex(static_cast<unsigned short>(tileTypeIndex));

        // get destination tile type
        TileTypeEx& tileTypeEx = m_tileTypesEx.at(tileTypeIndex);
        // read destination wire name and find it
        if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
        wireIndex = findWire(m_tok->wordToken(), tileTypeEx.wireMap);
        // set connection wire index
        connection.wireIndex(static_cast<unsigned short>(wireIndex));

        // add connection to current wire
        addConnection(connection);

        // skip closing parenthesis
        if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
        if (')' != m_tok->separatorToken()) throw Exception();
    }
}


void XDLRCParserImp::parse2ndPIP()
{
    // skip tile name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip  start wire
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

    // skip keyword
    m_tok->wordChar('=');
    m_tok->wordChar('>');
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    PIPDirection::fromString(m_tok->wordToken());
    m_tok->separatorChar('=');
    m_tok->separatorChar('>');

    // skip end wire
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();

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