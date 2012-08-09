/**
* \file XDLParserImp1.cpp
* \brief Contains definition of XDLParserImp class.
*/

#include <exception/Exception.hpp>
#include <xdl/parser/XDLKeywords.hpp>
#include <xdl/parser/XDLParserImp.hpp>

using namespace bil;
using namespace bil::xdlparser_detail;

const size_t INSTANCES_PREALLOCATION_COUNT = 8000;
const size_t NETS_PREALLOCATION_COUNT = 8000;


void XDLParserImp::parseHeader(StreamTokenizer& tokenizer, Design& design)
{
    // clear out parser
    clearAll();

    // save stream tokenizer pointer and prepare it
    m_tok = &tokenizer;
    setupSyntax();

    // save design pointer and clear out design
    m_design = &design;
    m_instances = &(design.instances());
    m_nets = &(design.nets());
    design.clear();

    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLKeywords::DESIGN) != 0) throw Exception();

    // read design name
    parseQuotedString();
    (design.name()).assign(m_quoteBuffer);

    // read target device name
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    (design.deviceName()).assign(m_tok->wordToken());

    // read NCD version string
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    (design.ncdVersion()).assign(m_tok->wordToken());

    // skip comma
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (',' != m_tok->separatorToken()) throw Exception();

    // skip keyword
    if (StreamTokenizer::TT_WORD != m_tok->nextToken()) throw Exception();
    if (strcmp(m_tok->wordToken(), XDLKeywords::CFG) != 0) throw Exception();

    // read design attributes
    parseQuotedString();
    (design.attributes()).assign(m_quoteBuffer);

    // skip semicolon
    if (StreamTokenizer::TT_SEPARATOR != m_tok->nextToken()) throw Exception();
    if (';' != m_tok->separatorToken()) throw Exception();

    // success
    m_headerParsed = true;
}


void XDLParserImp::parseBody(const Device& device)
{
    // check if body can no be parsed
    if (!m_headerParsed) throw Exception();
    m_headerParsed = false;

    // prepare stream tokenizer
    setupSyntax();

    // save pointer and fill device lookup structures
    m_device = &device;
    m_tiles = &(device.tiles());
    fillDeviceLookups();

    // preallocate memory for instances and nets
    m_instances->reserve(INSTANCES_PREALLOCATION_COUNT);
    m_nets->reserve(NETS_PREALLOCATION_COUNT);

    // parse instances
    StreamTokenizer::token_t tokenType;
    const char* keyword = 0;
    for (;;)
    {
        // get next token
        tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_WORD != tokenType) break;
        keyword = m_tok->wordToken();

        // check if current token is instance keyword
        if ((strcmp(keyword, XDLKeywords::INST) != 0) &&
            (strcmp(keyword, XDLKeywords::INSTANCE) != 0)) break;

        // if so, parse instance
        parseInstance();
    }

    // parse nets
    for (;;)
    {
        // check if current token is net keyword
        if (StreamTokenizer::TT_WORD != tokenType) break;
        if (strcmp(keyword, XDLKeywords::NET) != 0) break;

        // if so, parse net
        parseNet();

        // get next token
        tokenType = m_tok->nextToken();
        if (StreamTokenizer::TT_WORD != tokenType) break;
        keyword = m_tok->wordToken();
    }

    // check end of file
    if (StreamTokenizer::TT_EOF != tokenType) throw Exception();

    // reset parser
    clearAll();
}