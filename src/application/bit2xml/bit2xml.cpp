/**
* \file bit2xml.cpp
* \brief Contains the main method of the bit2xml program.
* \details The bit2xml program converts a bitfile into a XML representation. The
*          generated XML can optionally be linked to a XSL and a CSS stylesheet
*          for viewing.
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <application/bit2xml/bit2xmlArgs.hpp>
#include <application/bit2xml/bit2xmlData.hpp>
#include <application/bit2xml/bit2xmlMsgs.hpp>
#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileReader.hpp>
#include <bitfile/BitFileXMLWriter.hpp>
#include <bitstream/V5BitstreamReader.hpp>
#include <bitstream/V5BitstreamXMLWriter.hpp>
#include <exception/CommandLineException.hpp>
#include <exception/IOException.hpp>
#include <util/XMLWriter.hpp>


int main(int argc, char** argv)
{
    using namespace bil;

    try
    {
        // process command line
        std::cout << SPLASH_MSG;
        parseCommandLine(argc, argv);

        // load bitfile
        std::cout << LOADING_BITFILE_MSG;
        BitFileData bfd;
        std::ifstream bitfileStream(bitFileName.c_str(), std::ios::binary);
        readBitfile(bfd, bitfileStream);

        // construct bitstream from bitfile raw data
        std::cout << DECODING_BITSTREAM_MSG;
        Bitstream bs;
        readV5Bitstream(bs, bfd.bitstreamWords(), bfd.bitstreamWordCount());
        bfd.bitstreamWordCount(0);

        // get bitfile name without path
        size_t pos = bitFileName.find_last_of("/\\") + 1;
        std::string bitFileNameWithoutPath(bitFileName.substr(pos));

        // write XML file containing bitfile meta data and bitstream contents
        std::cout << WRITING_XML_MSG;
        std::ofstream ofXml(xmlFileName.c_str());
        XMLWriter xmlWriter(ofXml);
        xmlWriter.addProcessingInstruction(XML_HEADER, XML_HEADER_DATA, false);
        if (addStylesheet) xmlWriter.addProcessingInstruction(XML_STYLESHEET_HEADER, XML_STYLESHEET_HEADER_DATA);
        xmlWriter.beginElement(XML_ELEMENT_BITFILE);
        xmlWriter.addAttribute(XML_ELEMENT_FILENAME, bitFileNameWithoutPath);
        xmlWriter.beginElement(XML_ELEMENT_META);
        writeBitFileMetaXML(bfd, xmlWriter);
        xmlWriter.endElement();
        xmlWriter.beginElement(XML_ELEMENT_PACKETS);
        writeV5BitstreamXML(xmlWriter, bs);
        xmlWriter.endElement();
        xmlWriter.endElement();

        // create XSL and CSS style sheets for XML display
        if (addStylesheet)
        {
            std::cout << WRITING_STYLESHEETS_MSG;

            pos = xmlFileName.find_last_of("/\\") + 1;
            std::string xmlFilePath(xmlFileName.substr(0, pos));

            std::string xslFileName(xmlFilePath);
            xslFileName.append(XSL_FILENAME);
            std::ofstream ofXSL(xslFileName.c_str(), std::ios::binary);
            ofXSL.write(reinterpret_cast<const char*>(DISASSEMBLY_XSL), DISASSEMBLY_XSL_SIZE);
            if (!ofXSL) throw IOException();

            std::string cssFileName(xmlFilePath);
            cssFileName.append(CSS_FILENAME);
            std::ofstream ofCSS(cssFileName.c_str(), std::ios::binary);
            ofCSS.write(reinterpret_cast<const char*>(DISASSEMBLY_CSS), DISASSEMBLY_CSS_SIZE);
            if (!ofCSS) throw IOException();
        }

        // finished
        std::cout << FINISHED_MSG;
    }
    catch (const CommandLineException& e)
    {
        std::cout << ERROR_MSG << e.what() << INFO_MSG;
        return EXIT_FAILURE;
    }
    catch (...)
    {
        std::cout << ERROR_UNKNOWN_MSG;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}