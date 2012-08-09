/**
* \file XDLRCParserImp.hpp
* \brief Contains declaration of XDLRCParserImp class.
*/

#pragma once
#ifndef BIL_XDLRCPARSERIMP_HPP
#define BIL_XDLRCPARSERIMP_HPP

#include <map>
#include <set>
#include <util/StreamTokenizer.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil { namespace xdlrcparser_detail {

    typedef std::map<std::string, size_t> tileMap_t;
    typedef std::map<std::string, size_t> tileTypeMap_t;
    typedef std::map<std::string, size_t> wireMap_t;
    typedef std::set<PIP> pipSet_t;
    typedef std::map<std::string, size_t> primitiveTypeMap_t;
    typedef std::map<std::string, size_t> pinMap_t;

    struct TileTypeEx {
        wireMap_t wireMap;
        pipSet_t pipSet;
        bool writeSiteTypes;
    };


    /**
    * \brief Private XDLRC parser implementation.
    *
    * This class is not used directly, but by the public XDLRCParser class.
    */
    class XDLRCParserImp {
    public:

        XDLRCParserImp();

        void parseFirstPass(StreamTokenizer& tokenizer, Device& device);
        void parseSecondPass();

    private:

        XDLRCParserImp(const XDLRCParserImp&);
        XDLRCParserImp& operator=(const XDLRCParserImp&);

        void clearAll();
        void resetTempPointers();
        void setupSyntax();

        void parse1stTiles();
        void parse1stTile();
        void parse1stPrimitiveSite();
        void parse1stWire();
        void parse1stPIP();
        void parse1stPrimitiveDefs();
        void parse1stPrimitiveDef();
        void parse1stPin();
        void parse1stElement();

        void parse2ndTiles();
        void parse2ndTile();
        void parse2ndPrimitiveSite();
        void parse2ndPrimitiveSiteSkip();
        void parse2ndWire();
        void parse2ndPIP();

        void parseTileSummary();
        void parseSummary();

        void addTile(const char* tileName);
        void addTileType(const char* typeName);
        void addWire(const char* wireName);
        void addConnection(WireConnection& connection);
        void addPIP(const PIP& pip);
        void addPrimitiveType(const char* typeName);
        void addPin(const char* pinName);

        size_t findTile(const char* tileName);
        size_t findWire(const char* wireName, wireMap_t& wireMap);
        size_t findPrimitiveType(const char* typeName);
        size_t findPin(const char* pinName);

        StreamTokenizer* m_tok;
        bool m_secondPassEnabled;

        Device* m_device;
        Tiles* m_tiles;
        Tile* m_tile;
        PrimitiveSites* m_sites;
        TileTypes* m_tileTypes;
        TileType* m_tileType;
        PrimitiveSiteTypes* m_siteTypes;
        PrimitiveSiteType* m_siteType;
        PinWires* m_pinWires;
        Wires* m_wires;
        WireConnections* m_connections;
        PIPs* m_pips;
        PrimitiveTypes* m_primitiveTypes;
        PrimitiveType* m_primitiveType;
        Pins* m_pins;
        Pin* m_pin;
        Elements* m_elements;

        tileMap_t m_tileMap;
        tileTypeMap_t m_tileTypeMap;
        std::vector<TileTypeEx> m_tileTypesEx;
        primitiveTypeMap_t m_primitiveTypeMap;
        std::vector<pinMap_t> m_pinMaps;

        TileTypeEx* m_tileTypeEx;
        wireMap_t* m_wireMap;
        pipSet_t* m_pipSet;
        pinMap_t* m_pinMap;

        size_t m_tileIndex;
        size_t m_primitiveSiteIndex;

    };

}}

#endif
