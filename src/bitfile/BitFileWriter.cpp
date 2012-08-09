/**
* \file BitFileWriter.cpp
* \brief Function for writing a bitfile to a stream.
*/

#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileSections.hpp>
#include <bitfile/BitFileWriter.hpp>
#include <exception/IOException.hpp>
#include <util/EndianConversion.hpp>

using namespace bil;


static void writeStringSection(const std::string& s, std::ostream& outputStream)
{
    // get string length (only up to first zero char) including trailing zero
    size_t slen = strlen(s.c_str()) + 1;
    // test if that fits in two bytes and convert it
    if (0xffff < slen) throw Exception();
    boost::uint16_t len = swapBigEndian(static_cast<boost::uint16_t>(slen));
    // write two bytes length
    if (!outputStream.write(reinterpret_cast<char*>(&len), sizeof(len)))
        throw IOException();
    // write string data including trailing zero
    if (!outputStream.write(s.c_str(), slen)) throw IOException();
}


static void writeDataSection(const boost::uint32_t* words, size_t wordCount, std::ostream& outputStream)
{
    // convert word count to four byte byte count
    boost::uint32_t w = swapBigEndian(static_cast<boost::uint32_t>(wordCount << 2));
    // write it
    if (!outputStream.write(reinterpret_cast<char*>(&w), sizeof(w)))
        throw IOException();
    // write swapped data words
    for (size_t i = 0; i < wordCount; ++i)
    {
        w = swapBigEndian(*words++);
        if (!outputStream.write(reinterpret_cast<const char*>(&w), sizeof(w)))
            throw IOException();
    }
}


void bil::writeBitfile(const BitFileData& bitFileData, std::ostream& outputStream)
{
    // write file header
    if (!outputStream.write(reinterpret_cast<const char*>(BITFILE_HEADER), sizeof(BITFILE_HEADER)))
        throw IOException();

    // write source filename section
    if (!outputStream.write(reinterpret_cast<const char*>(&BITFILE_KEY_SOURCEFILENAME), 1))
        throw IOException();
    writeStringSection(bitFileData.sourceFileName(), outputStream);
    // write target device name section
    if (!outputStream.write(reinterpret_cast<const char*>(&BITFILE_KEY_TARGETDEVICENAME), 1))
        throw IOException();
    writeStringSection(bitFileData.targetDeviceName(), outputStream);
    // write creation date section
    if (!outputStream.write(reinterpret_cast<const char*>(&BITFILE_KEY_CREATIONDATE), 1))
        throw IOException();
    writeStringSection(bitFileData.creationDate(), outputStream);
    // write creation time section
    if (!outputStream.write(reinterpret_cast<const char*>(&BITFILE_KEY_CREATIONTIME), 1))
        throw IOException();
    writeStringSection(bitFileData.creationTime(), outputStream);

    // write raw bitstream
    if (!outputStream.write(reinterpret_cast<const char*>(&BITFILE_KEY_BITSTREAM), 1))
        throw IOException();
    writeDataSection(bitFileData.bitstreamWords(), bitFileData.bitstreamWordCount(), outputStream);
}