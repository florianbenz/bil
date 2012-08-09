/**
* \file V5CfgTileMapEntry.cpp
* \brief Contains definition of V5CfgTileMapEntry class.
*/

#include <configuration/V5Configuration.hpp>
#include <configuration/V5FrameAddress.hpp>
#include <correlation/cfgextraction/V5CfgTileMapEntry.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void V5CfgTileMapEntry::clear()
{
    lowerHalf = false;
    rowIndex = 0;
    columnIndex = 0;
    frameBeginIndex = 1;
    frameEndIndex = 0;
    wordBeginOffset = 1;
    wordEndOffset = 0;
}


size_t bil::getCfgDataWordCount(const V5CfgTileMapEntry& where)
{
    // calculate the amount of referenced words
    if (where.wordEndOffset < where.wordBeginOffset) return 0;
    size_t wordsPerFrame = (where.wordEndOffset - where.wordBeginOffset) + 1;
    if (where.frameEndIndex < where.frameBeginIndex) return 0;
    size_t frameCount = (where.frameEndIndex - where.frameBeginIndex) + 1;
    return frameCount * wordsPerFrame;
}


size_t bil::getCfgData(boost::uint32_t* data, size_t dataWordCount,
                        const V5Configuration& src, const V5CfgTileMapEntry& where)
{
    // get begin address of frame range
    V5FrameAddress address(&(src.addressLayout()));
    address.block(V5CfgBlock::INTERCONNECT_AND_CFG);
    address.lowerHalf(where.lowerHalf);
    address.rowIndex(where.rowIndex);
    address.columnIndex(where.columnIndex);
    address.frameIndex(where.frameBeginIndex);

    // get end address of frame range
    V5FrameAddress endAdddress = address;
    endAdddress.frameIndex(where.frameEndIndex);

    // get begin and end word offset
    size_t wordOffset = where.wordBeginOffset;
    if (V5CfgFrame::WORDCOUNT <= wordOffset) throw Exception();
    size_t wordEndOffset = where.wordEndOffset;
    if (V5CfgFrame::WORDCOUNT <= wordEndOffset) throw Exception();
    if (wordEndOffset < wordOffset) return 0;

    // loop over all frames in designated range
    boost::uint32_t* dataStart = data;
    boost::uint32_t* dataEnd = data + dataWordCount;
    while (address <= endAdddress)
    {
        // get frame at current address
        const V5CfgFrame* frame = src.lookup(address);
        if (0 == frame) throw Exception();

        // get pointers to designated range of data words
        const boost::uint32_t* frameData = frame->data();
        const boost::uint32_t* frameDataEnd = frameData + wordEndOffset;
        frameData += wordOffset;

        // copy range
        while (frameData <= frameDataEnd)
        {
            if (data >= dataEnd) throw Exception();
            *(data++) = *(frameData++);
        }

        // advance to next frame address
        address.next();
    }

    // return count of extracted words
    return (data - dataStart);
}