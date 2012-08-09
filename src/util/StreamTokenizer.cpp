/**
* \file StreamTokenizer.cpp
* \brief Contains definition of StreamTokenizer class.
*/

#include <cstdlib>
#include <exception/IOException.hpp>
#include <util/StreamTokenizer.hpp>

using namespace bil;

const unsigned char AT_SEPARATOR = 0;
const unsigned char AT_WORD = 1;
const unsigned char AT_WHITESPACE = 2;
const unsigned char AT_COMMENT = 3;

const size_t BUFFER_SIZE = 0x1000000;
const size_t TOKEN_MAX_SIZE = 0x7fe;


StreamTokenizer::StreamTokenizer(std::istream& inputStream):
  m_inputStream(&inputStream),
  m_buffer(0),
  m_bufferSize(0),
  m_readIndex(0),
  m_tokenType(TT_NONE),
  m_separatorToken(0),
  m_wordBuffer(0),
  m_wordBufferSize(0)
{
    m_buffer = new char[BUFFER_SIZE];
    m_wordBuffer = new char[TOKEN_MAX_SIZE+1];
    resetSyntax();
}


StreamTokenizer::~StreamTokenizer()
{
    delete[] m_wordBuffer;
    m_wordBuffer = 0;
    delete[] m_buffer;
    m_buffer = 0;
}


void StreamTokenizer::inputStream(std::istream& inputStream)
{
    m_inputStream = &inputStream;
    reset();
}


void StreamTokenizer::reset()
{
    m_bufferSize = 0;
    m_readIndex = 0;
    m_tokenType = TT_NONE;
    m_separatorToken = 0;
    m_wordBufferSize = 0;
}


void StreamTokenizer::separatorChar(char c)
{
    m_syntaxTable[static_cast<unsigned char>(c)] = AT_SEPARATOR;
}


void StreamTokenizer::separatorChars(char firstChar, char lastChar)
{
    for (char c = firstChar; c <= lastChar; ++c)
        m_syntaxTable[static_cast<unsigned char>(c)] = AT_SEPARATOR;
}


void StreamTokenizer::wordChar(char c)
{
    m_syntaxTable[static_cast<unsigned char>(c)] = AT_WORD;
}


void StreamTokenizer::wordChars(char firstChar, char lastChar)
{
    for (char c = firstChar; c <= lastChar; ++c)
        m_syntaxTable[static_cast<unsigned char>(c)] = AT_WORD;
}


void StreamTokenizer::whitespaceChar(char c)
{
    m_syntaxTable[static_cast<unsigned char>(c)] = AT_WHITESPACE;
}


void StreamTokenizer::commentChar(char c)
{
    m_syntaxTable[static_cast<unsigned char>(c)] = AT_COMMENT;
}


void StreamTokenizer::resetSyntax()
{
    for (unsigned c = 0; c < 0xff; ++c)
        m_syntaxTable[c] = AT_SEPARATOR;
}


StreamTokenizer::token_t StreamTokenizer::nextToken()
{
    for (;;)
    {
        // read character from buffer at current read index
        if (0 == checkBuffer()) return TT_EOF;
        char c = m_buffer[m_readIndex];

        // classify read character
        switch (m_syntaxTable[static_cast<unsigned char>(c)])
        {
            case AT_WHITESPACE:
                // skip whitespace char
                ++m_readIndex;
                continue;

            case AT_WORD:
                // accumulate following word chars into one word
                m_tokenType = TT_WORD;
                m_wordBufferSize = 0;
                do
                {
                    if (m_wordBufferSize < TOKEN_MAX_SIZE) m_wordBuffer[m_wordBufferSize++] = c;
                    ++m_readIndex;
                    if (0 == checkBuffer()) return TT_WORD;
                    c = m_buffer[m_readIndex];
                }
                while (AT_WORD == (m_syntaxTable[static_cast<unsigned char>(c)]));
                return TT_WORD;

            case AT_SEPARATOR:
                // separator char
                m_tokenType = TT_SEPARATOR;
                m_separatorToken = c;
                ++m_readIndex;
                return TT_SEPARATOR;

            case AT_COMMENT:
                // skip everything until next new line char
                do
                {
                    ++m_readIndex;
                    if (0 == checkBuffer())
                    {
                        m_tokenType = TT_EOF;
                        return TT_EOF;
                    }
                    c = m_buffer[m_readIndex];
                }
                while ('\n' != c);
                continue;
        }
    }
}


StreamTokenizer::token_t StreamTokenizer::tokenType() const
{
    return m_tokenType;
}


char StreamTokenizer::separatorToken() const
{
    return m_separatorToken;
}


const char* StreamTokenizer::wordToken() const
{
    m_wordBuffer[m_wordBufferSize] = 0;
    return m_wordBuffer;
}


size_t StreamTokenizer::wordTokenSize() const
{
    return m_wordBufferSize;
}


bool StreamTokenizer::uintToken(unsigned& val) const
{
    m_wordBuffer[m_wordBufferSize] = 0;
    char* endPtr;
    val = strtol(m_wordBuffer, &endPtr, 10);
    return ((0 != endPtr) && (0 == *endPtr));
}


size_t StreamTokenizer::checkBuffer()
{
    // check if read index is out of buffer
    if (m_bufferSize > m_readIndex) return m_bufferSize;
    // if yes, refill buffer
    m_inputStream->read(m_buffer, BUFFER_SIZE);
    m_readIndex = 0;
    m_bufferSize = m_inputStream->gcount();
    // check for errors
    if (m_inputStream->bad()) throw IOException();
    // return the fill state of buffer
    return m_bufferSize;
}