/**
* \file XDLParserImp0.cpp
* \brief Contains definition of XDLParserImp class.
*/

#include <utility>
#include <exception/Exception.hpp>
#include <xdl/parser/XDLParserImp.hpp>

using namespace bil;
using namespace bil::xdlparser_detail;


XDLParserImp::XDLParserImp():
  m_headerParsed(false),
  m_quoteBuffer(0),
  m_tileMap(),
  m_wirePIPMaps(),
  m_pinMaps(),
  m_primitiveTypesMap(),
  m_instanceMap(),
  m_netSet()
{
    m_quoteBuffer = new char[QUOTE_BUFFER_SIZE+1];
}


XDLParserImp::~XDLParserImp()
{
    delete[] m_quoteBuffer;
    m_quoteBuffer = 0;
}


void XDLParserImp::setupSyntax()
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


void XDLParserImp::fillDeviceLookups()
{
    // clear all maps
    clearTemporaryData();

    // fill tile map
    const Tiles& tiles = m_device->tiles();
    size_t count = tiles.size();
    for (size_t i = 0; i < count; ++i)
    {
        const Tile& tile = tiles[i];
        m_tileMap.insert(std::make_pair(tile.name(), i));
    }

    // fill wire and pip maps
    const TileTypes& tileTypes = m_device->tileTypes();
    count = tileTypes.size();
    m_wirePIPMaps.resize(count);
    for (size_t i = 0; i < count; ++i)
    {
        // get current tile type and its maps
        TileTypeEx& tileTypeEx = m_wirePIPMaps[i];
        const TileType& tileType = tileTypes[i];

        // fill wire map
        nameIndexMap_t& wireMap = tileTypeEx.wireMap;
        const Wires& wires = tileType.wires();
        size_t wireCount = wires.size();
        for (size_t j = 0; j < wireCount; ++j)
        {
            const Wire& wire = wires[j];
            wireMap.insert(std::make_pair(wire.name(), j));
        }

        // fill PIP map
        pipIndexMap_t& pipMap = tileTypeEx.pipMap;
        const PIPs& pips = tileType.pips();
        size_t pipCount = pips.size();
        for (size_t j = 0; j < pipCount; ++j)
        {
            const PIP& pip = pips[j];
            pipMap.insert(std::make_pair(pip, j));
        }
    }

    // fill primitive type map and primitive pin maps
    const PrimitiveTypes& primitiveTypes = m_device->primitiveTypes();
    count = primitiveTypes.size();
    m_pinMaps.resize(count);
    for (size_t i = 0; i < count; ++i)
    {
        // get primitive type and insert it into map
        const PrimitiveType& primitiveType = primitiveTypes[i];
        m_primitiveTypesMap.insert(std::make_pair(primitiveType.name(), i));

        // get pin map of current primitive type
        nameIndexMap_t& pinMap = m_pinMaps[i];
        // get pins of current primitive type and add them into map
        const Pins& pins = primitiveType.pins();
        size_t pinCount = pins.size();
        for (size_t j = 0; j < pinCount; ++j)
        {
            const Pin& pin = pins[j];
            pinMap.insert(std::make_pair(pin.externalName(), j));
        }
    }
}


void XDLParserImp::clearAll()
{
    // header must be parsed again
    m_headerParsed = false;
    // reset all pointers
    m_tok = 0;
    m_device = 0;
    m_tiles = 0;
    m_design = 0;
    m_instances = 0;
    m_instance = 0;
    m_nets = 0;
    m_net = 0;
    // clear data
    clearTemporaryData();
}


void XDLParserImp::clearTemporaryData()
{
    // clear maps
    m_tileMap.clear();
    m_wirePIPMaps.clear();
    m_pinMaps.clear();
    m_primitiveTypesMap.clear();
    m_instanceMap.clear();
    m_netSet.clear();
}


void XDLParserImp::addInstance(const char* instanceName)
{
    // check, if given instance name is not already in use
    nameIndexMap_t::iterator lb = m_instanceMap.lower_bound(instanceName);
    if ((m_instanceMap.end() != lb) && (instanceName == lb->first)) throw Exception();

    // create new instance and set its name
    size_t count = m_instances->size();
    m_instances->push_back(Instance());
    m_instance = &((*m_instances)[count]);
    (m_instance->name()).assign(instanceName);

    // insert tile name and index into map
    m_instanceMap.insert(lb, std::make_pair(instanceName, count));
}


void XDLParserImp::addNet(const char* netName)
{
    // check, if given net name is not already in use
    nameSet_t::iterator lb = m_netSet.lower_bound(netName);
    if ((m_netSet.end() != lb) && (netName == *lb)) throw Exception();

    // create new instance and set its name
    size_t count = m_nets->size();
    m_nets->push_back(Net());
    m_net = &((*m_nets)[count]);
    (m_net->name()).assign(netName);

    // insert net into set
    m_netSet.insert(lb, netName);
}


size_t XDLParserImp::findTile(const char* tileName) const
{
    // search for tile name
    nameIndexMap_t::const_iterator it = m_tileMap.find(tileName);
    if (m_tileMap.end() == it) throw Exception();
    // return its index
    return it->second;
}


size_t XDLParserImp::findWire(const char* wireName, const nameIndexMap_t& wireMap) const
{
    // search for wire name
    nameIndexMap_t::const_iterator it = wireMap.find(wireName);
    if (wireMap.end() == it) throw Exception();
    // return its index
    return it->second;
}


size_t XDLParserImp::findPIP(const PIP& pip, const pipIndexMap_t& pipMap) const
{
    // search for PIP
    pipIndexMap_t::const_iterator it = pipMap.find(pip);
    if (pipMap.end() == it) throw Exception();
    // return its index
    return it->second;
}


size_t XDLParserImp::findPrimitiveSite(const char* siteName, size_t tileIndex) const
{
    // get primitive sites of given tile
    const Tile& tile = m_tiles->at(tileIndex);
    const PrimitiveSites& sites = tile.primitiveSites();
    // search for site of given name
    size_t count = sites.size();
    for (size_t i = 0; i < count; ++i)
        if (0 == ((sites[i]).name()).compare(siteName))
            return i;
    // not found
    throw Exception();
}


size_t XDLParserImp::findPrimitiveType(const char* typeName) const
{
    // search for primitive type
    nameIndexMap_t::const_iterator it = m_primitiveTypesMap.find(typeName);
    if (m_primitiveTypesMap.end() == it) throw Exception();
    // return its index
    return it->second;
}


size_t XDLParserImp::findInstance(const char* instanceName) const
{
    // search for instance name
    nameIndexMap_t::const_iterator it = m_instanceMap.find(instanceName);
    if (m_instanceMap.end() == it) throw Exception();
    // return its index
    return it->second;
}


size_t XDLParserImp::findPin(const char* pinName, size_t instanceIndex) const
{
    // get pin map of instance's primitive type
    const Instance& instance = m_instances->at(instanceIndex);
    size_t primitiveTypeIndex = instance.primitiveTypeIndex();
    const nameIndexMap_t& pinMap = m_pinMaps.at(primitiveTypeIndex);
    // search in map
    nameIndexMap_t::const_iterator it = pinMap.find(pinName);
    if (pinMap.end() == it) throw Exception();
    // return its index
    return it->second;
}