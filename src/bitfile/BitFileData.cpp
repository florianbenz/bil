/**
* \file BitFileData.cpp
* \brief Contains definition of BitFileData class.
*/

#include <bitfile/BitFileData.hpp>

using namespace bil;


std::string& BitFileData::sourceFileName()
{
    return m_sourceFileName;
}


const std::string& BitFileData::sourceFileName() const
{
    return m_sourceFileName;
}


std::string& BitFileData::targetDeviceName()
{
    return m_targetDeviceName;
}


const std::string& BitFileData::targetDeviceName() const
{
    return m_targetDeviceName;
}


std::string& BitFileData::creationDate()
{
    return m_creationDate;
}


const std::string& BitFileData::creationDate() const
{
    return m_creationDate;
}


std::string& BitFileData::creationTime()
{
    return m_creationTime;
}


const std::string& BitFileData::creationTime() const
{
    return m_creationTime;
}


void BitFileData::bitstreamWordCount(size_t size)
{
    m_bitstream.resize(size);
}


size_t BitFileData::bitstreamWordCount() const
{
    return m_bitstream.size();
}


boost::uint32_t* BitFileData::bitstreamWords()
{
    // if there is bitstream data, return pointer to it
    if (0 < m_bitstream.size()) return &(m_bitstream[0]);
    else return 0;
}


const boost::uint32_t* BitFileData::bitstreamWords() const
{
    // if there is bitstream data, return pointer to it
    if (0 < m_bitstream.size()) return &(m_bitstream[0]);
    else return 0;
}


void BitFileData::clear()
{
    m_sourceFileName.clear();
    m_targetDeviceName.clear();
    m_creationDate.clear();
    m_creationTime.clear();
    m_bitstream.clear();
}