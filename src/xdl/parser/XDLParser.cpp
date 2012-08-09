/**
* \file XDLParser.cpp
* \brief Contains definition of XDLParser class.
*/

#include <util/StreamTokenizer.hpp>
#include <xdl/parser/XDLParser.hpp>
#include <xdl/parser/XDLParserImp.hpp>

using namespace bil;


XDLParser::XDLParser():
  m_tokenizer(0),
  m_parserImp(0)
{
    m_parserImp = new xdlparser_detail::XDLParserImp();
}


XDLParser::~XDLParser()
{
    delete m_parserImp;
    m_parserImp = 0;
    delete m_tokenizer;
    m_tokenizer = 0;
}


void XDLParser::parseHeader(std::istream& inputStream, Design& design)
{
    if (0 != m_tokenizer) m_tokenizer->inputStream(inputStream);
    else m_tokenizer = new StreamTokenizer(inputStream);
    m_parserImp->parseHeader(*m_tokenizer, design);
}


void XDLParser::parseBody(const Device& device)
{
    m_parserImp->parseBody(device);
}