/**
* \file StreamTokenizer.hpp
* \brief Contains declaration of StreamTokenizer class.
*/

#pragma once
#ifndef BIL_STREAMTOKENIZER_HPP
#define BIL_STREAMTOKENIZER_HPP

#include <cstring>
#include <istream>


namespace bil {

    /**
    * \brief Reads data from a stream and returns it token by token.
    *
    * The tokenization is controlled by attributes assigned to characters and
    * can be changed while tokenization is in progress. For better speed all
    * read operations on the stream are buffered.
    */
    class StreamTokenizer {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new StreamTokenizer instance.
        * \param inputStream Stream to read from.
        */
        explicit StreamTokenizer(std::istream& inputStream);

        /**
        * \brief Destructs a StreamTokenizer instance.
        */
        StreamTokenizer::~StreamTokenizer();


        /**********************************************************************/
        /* INPUT STREAM                                                       */
        /**********************************************************************/

        /**
        * \brief Sets the input stream.
        * \details Will call reset().
        * \param inputStream The input stream.
        */
        void inputStream(std::istream& inputStream);


        /**********************************************************************/
        /* TOKENIZER STATE                                                    */
        /**********************************************************************/

        /**
        * \brief Resets all internal state (except syntax).
        * \details All internal buffers are flushed and the tokenization state
        *          is set back to default values. Next data will be read from
        *          current stream position.
        */
        void reset();


        /**********************************************************************/
        /* SYNTAX SETUP                                                       */
        /**********************************************************************/

        /**
        * \brief Sets separator attribute for given character.
        * \details A char of this attribute will be returned as one token of
        *          TT_SEPARATOR type.
        * \param c The char which attribute is to be set.
        */
        void separatorChar(char c);

        /**
        * \brief Sets separator attribute for given range of characters.
        * \details A char of this attribute will be returned as one token of
        *          TT_SEPARATOR type.
        * \param firstChar First char in range which attribute is to be set.
        * \param lastChar Last char in range which attribute is to be set.
        */
        void separatorChars(char firstChar, char lastChar);

        /**
        * \brief Sets word attribute for given character.
        * \details Word chars make up words and so a whole consecutive sequence
        *          of word chars will be returned as one token of TT_WORD type.
        * \param c The char which attribute is to be set.
        */
        void wordChar(char c);

        /**
        * \brief Sets word attribute for given range of characters.
        * \details Word chars make up words and so a whole consecutive sequence
        *          of word chars will be returned as one token of TT_WORD type.
        * \param firstChar First char in range which attribute is to be set.
        * \param lastChar Last char in range which attribute is to be set.
        */
        void wordChars(char firstChar, char lastChar);

        /**
        * \brief Sets whitespace attribute for given character.
        * \details Whitespace chars will be ignored and not returned as tokens.
        * \param c The char which attribute is to be set.
        */
        void whitespaceChar(char c);

        /**
        * \brief Sets comment attribute for given character.
        * \details Comment chars and all following chars will be ignored until
        *          the next new line.
        * \param c The char which attribute is to be set.
        */
        void commentChar(char c);

        /**
        * \brief Resets all characters to default attributes.
        * \details By default all chars have got the separator attribute.
        */
        void resetSyntax();


        /**********************************************************************/
        /* TOKEN RETRIEVAL                                                    */
        /**********************************************************************/

        /// type for describing type of token
        typedef unsigned token_t;

        /// invalid token
        const static token_t TT_NONE = 0;

        /// end of file token
        const static token_t TT_EOF = 1;

        /// separator token
        const static token_t TT_SEPARATOR = 2;

        /// word token
        const static token_t TT_WORD = 3;

        /**
        * \brief Reads next token from stream.
        * \details The token type and the token itself are saved and available
        *          via tokenType(), separatorToken() and wordToken().
        * \return The type of the read token.
        * \throws .
        */
        token_t nextToken();


        /**********************************************************************/
        /* CURRENT TOKEN                                                      */
        /**********************************************************************/

        /**
        * \brief Gets the type of current token.
        * \return The token type.
        */
        token_t tokenType() const;


        /**
        * \brief Gets current separator token.
        * \return The token.
        */
        char separatorToken() const;


        /**
        * \brief Gets pointer to current word token.
        * \return The token.
        */
        const char* wordToken() const;

        /**
        * \brief Gets size of current word token.
        * \return The token size.
        */
        size_t wordTokenSize() const;


        /**
        * \brief Gets the current word token as integer.
        * \param val Reference to variable to hold value.
        * \return True, if conversion suceeded; false otherwise.
        */
        bool uintToken(unsigned& val) const;


    private:

        StreamTokenizer(const StreamTokenizer&);
        StreamTokenizer& operator=(const StreamTokenizer&);

        size_t checkBuffer();

        std::istream* m_inputStream;
        char* m_buffer;
        size_t m_bufferSize;
        size_t m_readIndex;

        unsigned char m_syntaxTable[0xff];

        token_t m_tokenType;
        char m_separatorToken;
        char* m_wordBuffer;
        size_t m_wordBufferSize;

    };

}

#endif
