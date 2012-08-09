/**
* \file V5BitstreamXMLWriter.cpp
* \brief Contains definition of V5BitstreamXMLWriter class.
*/

#include <bitstream/Bitstream.hpp>
#include <bitstream/PacketOpcode.hpp>
#include <bitstream/V5BitstreamXMLWriter.hpp>
#include <configuration/V5FrameAddress.hpp>
#include <configuration/V5FrameAddressString.hpp>
#include <packetprocessor/V5CommandCode.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>
#include <util/HexPrint.hpp>
#include <util/XMLWriter.hpp>

using namespace bil;


const char TAGNAME_BUSWIDTHPATTERN[] = "buswidthpattern";
const char TAGNAME_DUMMYWORD[] = "dummyword";
const char TAGNAME_SYNCWORD[] = "syncword";
const char TAGNAME_TYPE1PACKET[] = "type1packet";
const char TAGNAME_TYPE2PACKET[] = "type2packet";

const char ATTRIBNAME_OPCODE[] = "opcode";
const char ATTRIBNAME_REGISTER[] = "register";
const char ATTRIBNAME_WORDCOUNT[] = "wordcount";


V5BitstreamXMLWriter::V5BitstreamXMLWriter(XMLWriter& xmlWriter):
  m_xmlWriter(xmlWriter)
{

}


void V5BitstreamXMLWriter::visit(const BuswidthPattern& buswidthPattern)
{
    V5BitstreamSyntaxChecker::visit(buswidthPattern);
    writePacketTag(buswidthPattern);
}


void V5BitstreamXMLWriter::visit(const DummyWord& dummyWord)
{
    V5BitstreamSyntaxChecker::visit(dummyWord);
    writePacketTag(dummyWord);
}


void V5BitstreamXMLWriter::visit(const SyncWord& syncWord)
{
    V5BitstreamSyntaxChecker::visit(syncWord);
    writePacketTag(syncWord);
}


void V5BitstreamXMLWriter::visit(const Type1Packet& type1Packet)
{
    V5BitstreamSyntaxChecker::visit(type1Packet);
    writePacketTag(TAGNAME_TYPE1PACKET, type1Packet);
}


void V5BitstreamXMLWriter::visit(const Type2Packet& type2Packet)
{
    V5BitstreamSyntaxChecker::visit(type2Packet);
    writePacketTag(TAGNAME_TYPE2PACKET, type2Packet);
}


void V5BitstreamXMLWriter::writePacketTag(const BuswidthPattern&)
{
    m_xmlWriter.beginElement(TAGNAME_BUSWIDTHPATTERN, true);
    m_xmlWriter.endElement(false);
}


void V5BitstreamXMLWriter::writePacketTag(const DummyWord& dummyWord)
{
    m_xmlWriter.beginElement(TAGNAME_DUMMYWORD, true);
    m_xmlWriter.addData(hexString(dummyWord.value()), false);
    m_xmlWriter.endElement(false);
}


void V5BitstreamXMLWriter::writePacketTag(const SyncWord&)
{
    m_xmlWriter.beginElement(TAGNAME_SYNCWORD, true);
    m_xmlWriter.endElement(false);
}


void V5BitstreamXMLWriter::writePacketTag(const std::string& tagName, const Type2Packet& type2Packet)
{
    // write opening tag
    m_xmlWriter.beginElement(tagName, true);

    // get opcode string representation. if that fails, take hex value.
    std::string tempStr(PacketOpcode::toString(type2Packet.opcode()));
    if (tempStr.empty()) tempStr = hexString(type2Packet.opcode());
    // write opcode attribute
    m_xmlWriter.addAttribute(ATTRIBNAME_OPCODE, tempStr);

    // if packet is NO_OP packet, then there is nothing more to write
    if (PacketOpcode::NO_OP != type2Packet.opcode())
    {
        // get register string representation. if that fails, take hex value.
        tempStr = V5RegisterAddress::toString(lastType1Address());
        if (tempStr.empty()) tempStr = hexString(lastType1Address());
        // write register attribute
        m_xmlWriter.addAttribute(ATTRIBNAME_REGISTER, tempStr);

        // write word count
        m_xmlWriter.addAttribute(ATTRIBNAME_WORDCOUNT, type2Packet.wordCount());

        // write element data if present
        if (PacketOpcode::REGISTER_WRITE == type2Packet.opcode())
            writeData(type2Packet.dataWords(), type2Packet.wordCount());
    }

    // close packet tag
    m_xmlWriter.endElement(false);
}


void V5BitstreamXMLWriter::writeData(const boost::uint32_t* words, size_t wordCount)
{
    // data for CMD register: write command name
    if ((V5RegisterAddress::CMD == lastType1Address()) && (1 == wordCount))
    {
        std::string cmdStr(V5CommandCode::toString(*words));
        if (cmdStr.empty()) cmdStr = hexString(*words);
        m_xmlWriter.addData(cmdStr, false);
    }
    // data for FAR register: write address
    else if ((V5RegisterAddress::FAR == lastType1Address()) && (1 == wordCount))
    {
        V5FrameAddress fa;
        fa.rawAddress(*words);
        m_xmlWriter.addData(toExpandedString(fa), false);
    }
    // all other data: write hex values
    else m_xmlWriter.addData(hexString(words, wordCount), false);
}


void bil::writeV5BitstreamXML(XMLWriter& xmlWriter, const Bitstream& bs)
{
    V5BitstreamXMLWriter bsXMLWriter(xmlWriter);
    bs.runVisitor(bsXMLWriter);
}