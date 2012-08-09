/**
* \file BitFileXMLWriter.hpp
* \brief Function for writing bitfile meta data into XML.
*/

#pragma once
#ifndef BIL_BITFILEXMLWRITER_HPP
#define BIL_BITFILEXMLWRITER_HPP

#include <string>


namespace bil {

    class XMLWriter;
    class BitFileData;


    /**
    * \brief Writes bitfile meta data out to XML using a given XML writer.
    * \param xmlWriter XMLWriter instance to be used.
    * \param bfd The bitfile data.
    * \throws .
    */
    void writeBitFileMetaXML(const BitFileData& bfd, XMLWriter& xmlWriter);

}

#endif
