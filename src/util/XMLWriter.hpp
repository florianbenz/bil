/**
* \file XMLWriter.hpp
* \brief Contains declaration of XMLWriter class.
*/

#pragma once
#ifndef BIL_XMLWRITER_HPP
#define BIL_XMLWRITER_HPP

#include <cstring>
#include <ostream>
#include <stack>
#include <string>


namespace bil {

    /**
    * \brief A simple XML stream writer.
    *
    * This XML writer is for simple and fast writing of XML data. It is
    * initialized over an output stream, which is used for all writing. Because
    * it writes directly to the stream, no data (except the tag hierarchy stack)
    * is cached and it is possible to write even very large files with almost no
    * memory consumption. It also ensures syntactic correctness of generated XML
    * data: When tags are closed, they get the the right tag name (through
    * tracking of the hierarchy levels and names). Every XML element has its own
    * writing functions: If syntactical correct tag/attribute names and data are
    * given, the output will also be correct. Also indentation will be done
    * automatically.
    */
    class XMLWriter {
    public:

        /**
        * \brief Creates a new XMLWriter instance.
        * \param os The stream to use for XML output.
        * \param baseIndent Number of space chars to prepend every line.
        * \param levelIndent Number of space chars to insert for every level.
        */
        explicit XMLWriter(std::ostream& os, size_t baseIndent = 0, size_t levelIndent = 2);


        /**
        * \brief Begins a new element.
        * \details Writes the start of an opening tag. The opening tag is not
        *          finished, because attributes (via addAttribute()) may follow.
        *          When the methods beginElement(), endElement(), addData(), and
        *          addProcessingInstruction() will later be called, the opening
        *          tag will automatically be finished.
        * \param name Name of element to begin.
        * \param newLine Specifies if a line break should be inserted before.
        */
        void beginElement(const std::string& name, bool newLine = true);

        /**
        * \brief Ends the current element.
        * \details If the current element has no content, no separate ending tag
        *          is created. Instead, the opening tag is finished with an
        *          empty element marker.
        * \throws .
        */
        void endElement(bool newLine = true);


        /**
        * \brief Adds an string attribute to the current opening tag.
        * \details Because attributes can only be placed inside an opening tag,
        *          addAttribute() can only be called directly after
        *          beginElement() or addAttribute().
        * \param name The attribute name.
        * \param value The attribute value.
        * \throws .
        */
        void addAttribute(const std::string& name, const std::string& value);

        /**
        * \brief Adds an unsigned attribute to the current opening tag.
        * \details Because attributes can only be placed inside an opening tag,
        *          addAttribute() can only be called directly after
        *          beginElement() or addAttribute().
        * \param name The attribute name.
        * \param value The attribute value.
        * \throws .
        */
        void addAttribute(const std::string& name, unsigned value);


        /**
        * \brief Adds data into the current element.
        * \details Because data can only be placed inside an element, addData()
        *          can be only called directly after beginElement() or
        *          addAttribute(), thereby closing the beginning tag.
        * \param data The data.
        * \param newLine Specifies if a line break should be inserted before.
        * \throws .
        */
        void addData(const std::string& data, bool newLine = true);


        /**
        * \brief Adds a processing instruction element.
        * \param target Target of the processing instruction.
        * \param newLine Specifies if a line break should be inserted before.
        * \param instruction The instruction.
        */
        void addProcessingInstruction(const std::string& target, const std::string& instruction, bool newLine = true);


        /**
        * \brief Gets the current element depth.
        * \return The element depth.
        */
        size_t depth() const;

        /**
        * \brief Gets the current element name.
        * \return The element name.
        */
        std::string element() const;


    private:

        XMLWriter(const XMLWriter&);
        XMLWriter& operator=(const XMLWriter&);


        std::ostream& m_outputStream;

        std::stack<std::string> m_elementStack;
        bool m_insideOpeningTag;

        size_t m_levelIndent;
        std::string m_lineIndentString;

    };

}

#endif
