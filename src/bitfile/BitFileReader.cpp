/**
* \file BitFileReader.cpp
* \brief Function for reading a bitfile from a stream.
*/

#include <boost/scoped_array.hpp>
#include <bitfile/BitFileData.hpp>
#include <bitfile/BitFileSections.hpp>
#include <bitfile/BitFileReader.hpp>
#include <exception/IOException.hpp>
#include <util/EndianConversion.hpp>

using namespace bil;


static void readStringSection(std::string& s, std::istream& inputStream)
{
    // read two byte string length
    boost::uint16_t len;
    if (!inputStream.read(reinterpret_cast<char*>(&len), sizeof(len)))
        throw IOException();
    // swap bytes
    size_t length = swapBigEndian(len);
    // set up temporary char buffer and read into it
    boost::scoped_array<char> buffer(new char[length]);
    char* bufPtr = buffer.get();
    if (!inputStream.read(bufPtr, length)) throw IOException();
    // test if string has got content
    if (1 < length)
    {
        // null terminate buffer and copy it to string
        bufPtr[length-1] = 0;
        s.assign(bufPtr);
    }
    else s.clear();
}


static void readDataSection(BitFileData& bitFileData, std::istream& inputStream)
{
    // read four byte byte count
    boost::uint32_t len;
    if (!inputStream.read(reinterpret_cast<char*>(&len), sizeof(len)))
        throw IOException();
    // swap bytes
    size_t length = swapBigEndian(len);
    // convert byte count to word count
    if ((length & 0x3) != 0) throw Exception();
    size_t wordCount = length >> 2;
    // read data
    bitFileData.bitstreamWordCount(wordCount);
    boost::uint32_t* dataPtr = bitFileData.bitstreamWords();
    if (!inputStream.read(reinterpret_cast<char*>(dataPtr), length))
        throw IOException();
    // correct endianess
    for (size_t i = 0; i < wordCount; ++i)
    {
        *dataPtr = swapBigEndian(*dataPtr);
        dataPtr++;
    }
}


void bil::readBitfile(BitFileData& bitFileData, std::istream& inputStream)
{
    // read and check header
    boost::uint8_t header[sizeof(BITFILE_HEADER)];
    if (!inputStream.read(reinterpret_cast<char*>(header), sizeof(BITFILE_HEADER)))
        throw IOException();
    // check contents
    if (0 != memcmp(header, BITFILE_HEADER, sizeof(BITFILE_HEADER)))
        throw Exception();

    // read sections
    boost::uint8_t sectionKey;
    while (inputStream.read(reinterpret_cast<char*>(&sectionKey), 1))
    {
        // read section designated by section key
        switch(sectionKey)
        {
        case BITFILE_KEY_SOURCEFILENAME:
            readStringSection(bitFileData.sourceFileName(), inputStream);
            break;

        case BITFILE_KEY_TARGETDEVICENAME:
            readStringSection(bitFileData.targetDeviceName(), inputStream);
            break;

        case BITFILE_KEY_CREATIONDATE:
            readStringSection(bitFileData.creationDate(), inputStream);
            break;

        case BITFILE_KEY_CREATIONTIME:
            readStringSection(bitFileData.creationTime(), inputStream);
            break;

        case BITFILE_KEY_BITSTREAM:
            readDataSection(bitFileData, inputStream);
            break;

        default: throw Exception();
        }
    }

    // check if eof reached
    if (!inputStream.eof()) throw IOException();
}