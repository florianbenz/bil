/**
* \file XMLWriter.cpp
* \brief Contains definition of XMLWriter class.
*/

#include <util/XMLWriter.hpp>

using namespace bil;


const char OPENINGTAG_START = '<';
const char OPENINGTAG_ENDEMPTY[] = " />";
const char TAG_END = '>';
const char CLOSINGTAG_START[] = "</";

const char ATTRIB_START[] = "=\"";
const char ATTRIB_END[] = "\"";

const char PINST_START[] = "<?";
const char PINST_END[] = "?>";

const char INDENT_CHAR = ' ';


XMLWriter::XMLWriter(std::ostream& os, size_t baseIndent, size_t levelIndent):
  m_outputStream(os),
  m_elementStack(),
  m_insideOpeningTag(false),
  m_lineIndentString(baseIndent, INDENT_CHAR),
  m_levelIndent(levelIndent)
{
    // write out first indent without line break
    m_outputStream << m_lineIndentString;
    // then add line break to indent string
    m_lineIndentString.insert(0, 1, '\n');
}


void XMLWriter::beginElement(const std::string& name, bool newLine)
{
    // finish an eventually unfinished opening tag
    if (m_insideOpeningTag) m_outputStream << TAG_END;

    // if new line is wanted write line break and indent
    if (newLine) m_outputStream << m_lineIndentString;

    // write tag and push tag name onto stack
    m_outputStream << OPENINGTAG_START << name;
    m_elementStack.push(name);
    // set inside opening tag flag
    m_insideOpeningTag = true;

    // update indent string: add indent for opening level
    m_lineIndentString.append(m_levelIndent, INDENT_CHAR);
}


void XMLWriter::endElement(bool newLine)
{
    // throw if no element is open
    if (0 >= m_elementStack.size()) throw ;

    // update indent string: remove indent for closing level
    m_lineIndentString.resize(m_lineIndentString.size() - m_levelIndent);

    // Test if a full closing element is necessary: If not, mark opening element
    // as empty; else write full closing element.
    if (m_insideOpeningTag) m_outputStream << OPENINGTAG_ENDEMPTY;
    else
    {
        // if new line is wanted write line break and indent
        if (newLine) m_outputStream << m_lineIndentString;
        m_outputStream << CLOSINGTAG_START << m_elementStack.top() << TAG_END;
    }

    // remove tag name from stack
    m_elementStack.pop();

    // clear inside opening tag flag
    m_insideOpeningTag = false;
}


void XMLWriter::addAttribute(const std::string& name, const std::string& value)
{
    // test if attribute can now be written (must be inside an opening tag) and
    // write it
    if (!m_insideOpeningTag) throw ;
    m_outputStream << ' ' << name << ATTRIB_START << value << ATTRIB_END;
}


void XMLWriter::addAttribute(const std::string& name, unsigned value)
{
    // test if attribute can now be written (must be inside an opening tag) and
    // write it
    if (!m_insideOpeningTag) throw ;
    m_outputStream << ' ' << name << ATTRIB_START << value << ATTRIB_END;
}


void XMLWriter::addData(const std::string& data, bool newLine)
{
    // finish an eventually unfinished opening tag
    if (m_insideOpeningTag) m_outputStream << TAG_END;
    m_insideOpeningTag = false;

    // if new line is wanted write line break and indent
    if (newLine) m_outputStream << m_lineIndentString;

    // write data
    m_outputStream << data;
}


void XMLWriter::addProcessingInstruction(const std::string& target, const std::string& instruction, bool newLine)
{
    // finish an eventually unfinished opening tag
    if (m_insideOpeningTag) m_outputStream << TAG_END;
    m_insideOpeningTag = false;

    // if new line is wanted write line break and indent
    if (newLine) m_outputStream << m_lineIndentString;

    // write PI
    m_outputStream << PINST_START << target << ' ' << instruction << PINST_END;
}


size_t XMLWriter::depth() const
{
    return m_elementStack.size();
}


std::string XMLWriter::element() const
{
    return m_elementStack.top();
}