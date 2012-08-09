/**
* \file BitFileXMLWriter.cpp
* \brief Function for writing bitfile meta data into XML.
*/

#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileXMLWriter.hpp>
#include <util/XMLWriter.hpp>

using namespace bil;


const char TAGNAME_SOURCEFILENAME[] = "sourcefilename";
const char TAGNAME_TARGETDEVICENAME[] = "targetdevicename";
const char TAGNAME_CREATIONDATE[] = "creationdate";
const char TAGNAME_CREATIONTIME[] = "creationtime";


void bil::writeBitFileMetaXML(const BitFileData& bfd, XMLWriter& xmlWriter)
{
    xmlWriter.beginElement(TAGNAME_SOURCEFILENAME);
    xmlWriter.addData(bfd.sourceFileName(), false);
    xmlWriter.endElement(false);

    xmlWriter.beginElement(TAGNAME_TARGETDEVICENAME);
    xmlWriter.addData(bfd.targetDeviceName(), false);
    xmlWriter.endElement(false);

    xmlWriter.beginElement(TAGNAME_CREATIONDATE);
    xmlWriter.addData(bfd.creationDate(), false);
    xmlWriter.endElement(false);

    xmlWriter.beginElement(TAGNAME_CREATIONTIME);
    xmlWriter.addData(bfd.creationTime(), false);
    xmlWriter.endElement(false);
}