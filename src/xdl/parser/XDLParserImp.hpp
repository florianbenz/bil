/**
* \file XDLParserImp.hpp
* \brief Contains declaration of XDLParserImp class.
*/

#pragma once
#ifndef BIL_XDLPARSERIMP_HPP
#define BIL_XDLPARSERIMP_HPP

#include <map>
#include <set>
#include <util/StreamTokenizer.hpp>
#include <xdl/model/Design.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil { namespace xdlparser_detail {

    typedef std::map<std::string, size_t> nameIndexMap_t;
    typedef std::map<PIP, size_t> pipIndexMap_t;
    typedef std::set<std::string> nameSet_t;

    struct TileTypeEx {
        nameIndexMap_t wireMap;
        pipIndexMap_t pipMap;
    };


    /**
    * \brief Private XDL parser implementation.
    *
    * This class is not used directly, but by the public XDLParser class.
    */
    class XDLParserImp {
    public:

        XDLParserImp();
        ~XDLParserImp();

        void parseHeader(StreamTokenizer& tokenizer, Design& design);
        void parseBody(const Device& device);

    private:

        XDLParserImp(const XDLParserImp&);
        XDLParserImp& operator=(const XDLParserImp&);

        void setupSyntax();
        void fillDeviceLookups();
        void clearAll();
        void clearTemporaryData();

        void parseInstance();
        void parseNet();
        void parseQuotedString();

        void addInstance(const char* instanceName);
        void addNet(const char* netName);

        size_t findTile(const char* tileName) const;
        size_t findWire(const char* wireName, const nameIndexMap_t& wireMap) const;
        size_t findPIP(const PIP& pip, const pipIndexMap_t& pipMap) const;
        size_t findPrimitiveSite(const char* siteName, size_t tileIndex) const;
        size_t findPrimitiveType(const char* typeName) const;
        size_t findInstance(const char* instanceName) const;
        size_t findPin(const char* pinName, size_t instanceIndex) const;

        bool m_headerParsed;
        StreamTokenizer* m_tok;
        char* m_quoteBuffer;
        static const size_t QUOTE_BUFFER_SIZE = 0x1ffff;

        const Device* m_device;
        const Tiles* m_tiles;

        Design* m_design;
        Instances* m_instances;
        Instance* m_instance;
        Nets* m_nets;
        Net* m_net;

        nameIndexMap_t m_tileMap;
        std::vector<TileTypeEx> m_wirePIPMaps;
        std::vector<nameIndexMap_t> m_pinMaps;
        nameIndexMap_t m_primitiveTypesMap;
        nameIndexMap_t m_instanceMap;
        nameSet_t m_netSet;
    };

}}

#endif
