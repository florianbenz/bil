/**
* \file XDLRCParser.cpp
* \brief Contains definition of XDLRCParser class.
*/

#include <util/StreamTokenizer.hpp>
#include <xdlrc/parser/XDLRCParser.hpp>
#include <xdlrc/parser/XDLRCParserImp.hpp>

using namespace bil;


XDLRCParser::XDLRCParser():
  m_tokenizer(0),
  m_parserImp(0)
{
    m_parserImp = new xdlrcparser_detail::XDLRCParserImp();
}


XDLRCParser::~XDLRCParser()
{
    delete m_parserImp;
    m_parserImp = 0;
    delete m_tokenizer;
    m_tokenizer = 0;
}


void XDLRCParser::parseFirstPass(std::istream& inputStream, Device& device)
{
    if (0 != m_tokenizer) m_tokenizer->inputStream(inputStream);
    else m_tokenizer = new StreamTokenizer(inputStream);
    m_parserImp->parseFirstPass(*m_tokenizer, device);
}


void XDLRCParser::parseSecondPass()
{
    if (0 != m_tokenizer) m_tokenizer->reset();
    m_parserImp->parseSecondPass();
}