/**
* \file XDLRCParser.hpp
* \brief Contains declaration of XDLRCParser class.
*/

#pragma once
#ifndef BIL_XDLRCPARSER_HPP
#define BIL_XDLRCPARSER_HPP

#include <istream>


namespace bil {

    class Device;
    class StreamTokenizer;

    namespace xdlrcparser_detail {
        class XDLRCParserImp;
    }


    /**
    * \brief Parser for XDLRC text file format.
    *
    * This parser is able to read in XDLRC text files and store their data into
    * an Device structure. The parsing is done in two passes: The first pass
    * reads most of the data (tiles and primitive definitions), the second pass
    * only finishes work (connections between wires and primitive sites). While
    * it checks syntax completely, it does not check the data semantics. Though
    * some checking is done (necessary because of conversion to Device model),
    * the obtained data should be checked later thoroughly.
    */
    class XDLRCParser {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new XDLRCParser instance.
        */
        XDLRCParser();

        /**
        * \brief Destructs a XDLRCParser instance.
        */
        XDLRCParser::~XDLRCParser();


        /**********************************************************************/
        /* PARSING                                                            */
        /**********************************************************************/

        /**
        * \brief Parses the XDLRC data out of the stream.
        * \details The does the first parsing pass reading most of the XDLRC
        *          data (all data objects inside the Device object gets filled
        *          except the WireConnections and the PrimitiveSiteTypes).
        * \param inputStream Stream to read from.
        * \param device Device instance to refill with data.
        * \throws .
        */
        void parseFirstPass(std::istream& inputStream, Device& device);

        /**
        * \brief Parses the XDLRC data out of the stream.
        * \details The does the second parsing pass filling the WireConnections
        *          and the PrimitiveSiteTypes. It uses the input stream and 
        *          Device instance given in first call.
        * \throws .
        */
        void parseSecondPass();


    private:

        XDLRCParser(const XDLRCParser&);
        XDLRCParser& operator=(const XDLRCParser&);

        StreamTokenizer* m_tokenizer;
        xdlrcparser_detail::XDLRCParserImp* m_parserImp;

    };

}

#endif
