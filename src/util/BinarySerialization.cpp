/**
* \file BinarySerialization.cpp
* \brief Contains functions for binary stream reading and writing.
*/

#include <climits>
#include <boost/scoped_array.hpp>
#include <exception/IOException.hpp>
#include <util/BinarySerialization.hpp>


void bil::writeBinary(const std::string& data, std::ostream& outputStream)
{
    // string length is 255 chars max
    size_t l = data.size();
    if (l > UCHAR_MAX) l = UCHAR_MAX;
    // write string length
    unsigned char length = static_cast<unsigned char>(l);
    outputStream.write(reinterpret_cast<const char*>(&length), sizeof(length));
    if (!outputStream) throw IOException();
    // write string data as one block
    if (0 < length)
    {
        outputStream.write(data.c_str(), length);
        if (!outputStream) throw IOException();
    }
}


void bil::readBinary(std::string& data, std::istream& inputStream)
{
    // read string length
    unsigned char length;
    inputStream.read(reinterpret_cast<char*>(&length), sizeof(length));
    if (!inputStream) throw IOException();
    if (0 < length)
    {
        // create buffer
        boost::scoped_array<char> buffer(new char[length]);
        char* bufferPtr = buffer.get();
        // read data into buffer
        inputStream.read(bufferPtr, length);
        if (!inputStream) throw IOException();
        // copy buffer into string
        data.assign(bufferPtr, length);
    }
    else data.clear();
}