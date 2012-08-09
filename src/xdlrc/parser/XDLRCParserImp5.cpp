/**
* \file XDLRCParserImp5.cpp
* \brief Contains definition of XDLRCParserImp class.
*/

#include <algorithm>
#include <exception/Exception.hpp>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCKeywords.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;
using namespace bil::xdlrcparser_detail;


void XDLRCParserImp::clearAll()
{
    // second pass not possible after clearing temp data
    m_secondPassEnabled = false;

    // clear all temporary data of the parser
    m_tileMap.clear();
    m_tileTypeMap.clear();
    m_tileTypesEx.clear();
    m_primitiveTypeMap.clear();
    m_pinMaps.clear();

    // clear all pointers
    m_tok = 0;
    m_device = 0;
    m_tiles = 0;
    m_tileTypes = 0;
    m_primitiveTypes = 0;
    resetTempPointers();
}


void XDLRCParserImp::resetTempPointers()
{
    // reset pointers for safety (excluding the ones that must preserved)
    m_tile = 0;
    m_sites = 0;
    m_tileType = 0;
    m_siteTypes = 0;
    m_siteType = 0;
    m_pinWires = 0;
    m_wires = 0;
    m_connections = 0;
    m_pips = 0;
    m_primitiveType = 0;
    m_pins = 0;
    m_pin = 0;
    m_elements = 0;
    m_tileTypeEx = 0;
    m_wireMap = 0;
    m_pipSet = 0;
    m_pinMap = 0; 
}


void XDLRCParserImp::setupSyntax()
{
    m_tok->resetSyntax();
    m_tok->commentChar('#');
    m_tok->whitespaceChar(' ');
    m_tok->whitespaceChar('\t');
    m_tok->whitespaceChar('\n');
    m_tok->whitespaceChar('\r');
    m_tok->wordChars('a', 'z');
    m_tok->wordChars('A', 'Z');
    m_tok->wordChars('0', '9');
    m_tok->wordChar('_');
    m_tok->wordChar('-');
    m_tok->wordChar('.');
}


void XDLRCParserImp::addTile(const char* tileName)
{
    // check, if given name is not already in use
    tileMap_t::iterator lb = m_tileMap.lower_bound(tileName);
    if ((m_tileMap.end() != lb) && (tileName == lb->first)) throw Exception();

    // create new tile, set its name, cache pointer to its sites
    size_t count = m_tiles->size();
    m_tiles->push_back(Tile());
    m_tile = &((*m_tiles)[count]);
    (m_tile->name()).assign(tileName);
    m_sites = &(m_tile->primitiveSites());

    // insert tile name and index into map
    m_tileMap.insert(lb, std::make_pair(tileName, count));
}


void XDLRCParserImp::addTileType(const char* typeName)
{
    // Check, if given type already exists: if not, create it.
    tileTypeMap_t::iterator lb = m_tileTypeMap.lower_bound(typeName);
    if ((m_tileTypeMap.end() == lb) || (typeName != lb->first))
    {
        // create a new tile type
        size_t count = m_tileTypes->size();
        m_tileTypes->push_back(TileType());
        m_tileType = &((*m_tileTypes)[count]);
        // set its name and tag it with its type index
        (m_tileType->name()).assign(typeName);
        m_tileType->tag(count);

        // create also extended info for it
        m_tileTypesEx.push_back(TileTypeEx());
        m_tileTypeEx = &(m_tileTypesEx[count]);
        m_tileTypeEx->writeSiteTypes = true;

        // create a new entry in tile type map
        tileTypeMap_t::iterator it =
            m_tileTypeMap.insert(lb, std::make_pair(typeName, count));
    }
    else
    {
        // fetch tile type index from map
        size_t tileTypeIndex = lb->second;
        // get pointers to tile type and its extended info
        m_tileType = &((*m_tileTypes)[tileTypeIndex]);
        m_tileTypeEx = &(m_tileTypesEx[tileTypeIndex]);
    }

    // cache pointers to wires and pips of current tile type
    m_wires = &(m_tileType->wires());
    m_pips = &(m_tileType->pips());
    // cache pointers to wire and pip maps
    m_wireMap = &(m_tileTypeEx->wireMap);
    m_pipSet = &(m_tileTypeEx->pipSet);
}


void XDLRCParserImp::addWire(const char* wireName)
{
    // Check, if a wire with given name already exists: if not, create it.
    wireMap_t::iterator lb = m_wireMap->lower_bound(wireName);
    if ((m_wireMap->end() != lb) && (wireName == lb->first)) return;

    // create a new wire and set its name
    size_t count = m_wires->size();
    m_wires->push_back(Wire());
    Wire& wire = (*m_wires)[count];
    (wire.name()).assign(wireName);

    // create a new entry for that wire in map
    m_wireMap->insert(lb, std::make_pair(wireName, count));
}


void XDLRCParserImp::addConnection(WireConnection& connection)
{
    // add connection, if not already in list
    WireConnections::const_iterator itBegin = m_connections->begin();
    WireConnections::const_iterator itEnd = m_connections->end();
    if (std::find(itBegin, itEnd, connection) == itEnd)
        m_connections->push_back(connection);
}


void XDLRCParserImp::addPIP(const PIP& pip)
{
    // check, if given PIP is already in PIP set
    pipSet_t::iterator lb = m_pipSet->lower_bound(pip);
    if ((m_pipSet->end() != lb) && (pip == (*lb))) return;

    // if not, copy it to PIP list and add it to set
    m_pips->push_back(pip);
    m_pipSet->insert(lb, pip);
}


void XDLRCParserImp::addPrimitiveType(const char* typeName)
{
    // check, if given type name is not already in use
    primitiveTypeMap_t::iterator lb = m_primitiveTypeMap.lower_bound(typeName);
    if ((m_primitiveTypeMap.end() != lb) && (typeName == lb->first)) throw Exception();

    // create new primitive type
    size_t count = m_primitiveTypes->size();
    m_primitiveTypes->push_back(PrimitiveType());
    m_primitiveType = &((*m_primitiveTypes)[count]);

    // set its name and tag it with its type index
    (m_primitiveType->name()).assign(typeName);
    m_primitiveType->tag(count);

    // create also pin map for it
    m_pinMaps.push_back(pinMap_t());

    // insert primitive type name and index into map
    m_primitiveTypeMap.insert(lb, std::make_pair(typeName, count));

    // cache pointers to pins and elements of current primitive type
    m_pins = &(m_primitiveType->pins());
    m_elements = &(m_primitiveType->elements());
    // cache pointers to pin map
    m_pinMap = &(m_pinMaps[count]);
}


void XDLRCParserImp::addPin(const char* pinName)
{
    // check, if given pin name is not already in use
    pinMap_t::iterator lb = m_pinMap->lower_bound(pinName);
    if ((m_pinMap->end() != lb) && (pinName == lb->first)) throw Exception();

    // create a new pin and set its name
    size_t count = m_pins->size();
    m_pins->push_back(Pin());
    m_pin = &((*m_pins)[count]);
    (m_pin->externalName()).assign(pinName);

    // create a new entry for that pin in map
    m_pinMap->insert(lb, std::make_pair(pinName, count));
}


size_t XDLRCParserImp::findTile(const char* tileName)
{
    // search for tile with given name
    tileMap_t::const_iterator it = m_tileMap.find(tileName);
    if (m_tileMap.end() == it) throw Exception();
    // return index of found tile
    return (it->second);
}


size_t XDLRCParserImp::findWire(const char* wireName, wireMap_t& wireMap)
{
    // search for wire with given name
    wireMap_t::const_iterator it = wireMap.find(wireName);
    if (wireMap.end() == it) throw Exception();
    // return index of found wire
    return it->second;
}


size_t XDLRCParserImp::findPrimitiveType(const char* typeName)
{
    // search for primitive type with given name
    primitiveTypeMap_t::const_iterator it = m_primitiveTypeMap.find(typeName);
    if (m_primitiveTypeMap.end() == it) throw Exception();
    // return index of found primitive type
    return it->second;
}


size_t XDLRCParserImp::findPin(const char* pinName)
{
    // search for pin with given name
    pinMap_t::const_iterator it = m_pinMap->find(pinName);
    if (m_pinMap->end() == it) throw Exception();
    // return index of found pin
    return it->second;
}