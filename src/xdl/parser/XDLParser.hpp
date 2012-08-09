/**
* \file XDLParser.hpp
* \brief Contains declaration of XDLParser class.
*/

#pragma once
#ifndef BIL_XDLPARSER_HPP
#define BIL_XDLPARSER_HPP

#include <istream>


namespace bil {

    class Design;
    class Device;
    class StreamTokenizer;

    namespace xdlparser_detail {
        class XDLParserImp;
    }


    /**
    * \brief Parser for XDL text file format.
    *
    * This parser is able to read in XDL design files and store their data into
    * an Design structure. It checks the syntax of given data completely, but
    * does not check its semantics. Out of the known XDL constructs it can not
    * parse module definitions and modules (not needed at the moment).
    */
    class XDLParser {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new XDLParser instance.
        */
        XDLParser();

        /**
        * \brief Destructs a XDLParser instance.
        */
        XDLParser::~XDLParser();


        /**********************************************************************/
        /* PARSING                                                            */
        /**********************************************************************/

        /**
        * \brief Parses the XDL data out of the stream.
        * \details Parses only the XDL header and fills the design with name,
        *          target device name, NCD version string, and attribute string.
        *          For parsing the remainder of the XDL, call parseBody.
        * \param inputStream Stream to read from.
        * \param design Design instance to fill with data.
        * \throws .
        */
        void parseHeader(std::istream& inputStream, Design& design);

        /**
        * \brief Parses the XDL data out of the stream.
        * \details Should be called after parseHeader. Uses the in the first
        *          call given input stream and design. The device should match
        *          the target device of the XDL, in order to successfully parse.
        * \param device Device the XDL to parse is for.
        * \throws .
        */
        void parseBody(const Device& device);


    private:

        XDLParser(const XDLParser&);
        XDLParser& operator=(const XDLParser&);

        StreamTokenizer* m_tokenizer;
        xdlparser_detail::XDLParserImp* m_parserImp;

    };

}

#endif
