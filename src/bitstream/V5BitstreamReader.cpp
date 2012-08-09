/**
* \file V5BitstreamReader.cpp
* \brief Contains definition of V5BitstreamReader class.
*/

#include <bitstream/BuswidthPatternRawData.hpp>
#include <bitstream/SyncWordRawData.hpp>
#include <bitstream/Type1PacketRawData.hpp>
#include <bitstream/Type2PacketRawData.hpp>
#include <bitstream/V5BitstreamReader.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void V5BitstreamReader::read(Bitstream& bitstream, const boost::uint32_t* words, size_t wordCount)
{
    // reset syntax checker
    m_syntaxChecker.reset();

    // load packets one by one
    std::auto_ptr<Packet> newPacketPtr;
    while (wordCount > 0)
    {
        // try to extract a packet
        size_t wordAdvance = extractPacket(words, wordCount, newPacketPtr);

        // check advance
        if (0 == wordAdvance) throw Exception();
        else if (wordAdvance > wordCount) throw Exception();
        // advance in bitstream
        words += wordAdvance;
        wordCount -= wordAdvance;

        // check if packet returned
        if (0 == newPacketPtr.get()) continue;
        // do syntax check to know, if packet type is allowed at this state
        newPacketPtr->accept(m_syntaxChecker);
        // add packet to bitstream
        bitstream.append(newPacketPtr);
    }
}


size_t V5BitstreamReader::extractPacket(const boost::uint32_t* words, size_t wordCount, std::auto_ptr<Packet>& packetPtr)
{
    // behind sync word: look for type 1 packets, type 2 packets, and dummy
    // words with value of 0x00000000
    if (behindSyncWord())
    {
        // check if given data words start with a type 1 packet
        if (0 < isType1Packet(words, wordCount))
        {
            packetPtr.reset(new Type1Packet());
            return readType1Packet(*(static_cast<Type1Packet*>(packetPtr.get())), words, wordCount);
        }
        // if directly after a type 1 packet: check if given data words start
        // with a type 2 packet
        if ((lastPacketWasType1()) && (0 < isType2Packet(words, wordCount)))
        {
            packetPtr.reset(new Type2Packet());
            return readType2Packet(*(static_cast<Type2Packet*>(packetPtr.get())), words, wordCount);
        }
        // check if given data words start with a dummy word of 0x00000000
        if ((0 < wordCount) && (DummyWord::NULL_WORD == *words))
        {
            packetPtr.reset(new DummyWord());
            (static_cast<DummyWord*>(packetPtr.get()))->value(*words);
            return 1;
        }
    }
    // in front of sync word: look for buswidth pattern, sync word, and dummy
    // words with value of 0xffffffff
    else
    {
        // check if given data words start with a dummy word of 0xffffffff
        if ((0 < wordCount) && (DummyWord::FULL_WORD == *words))
        {
            packetPtr.reset(new DummyWord());
            (static_cast<DummyWord*>(packetPtr.get()))->value(*words);
            return 1;
        }
        // check if given data words start with buswidth pattern
        size_t packetWordCount = isBuswidthPattern(words, wordCount);
        if (0 < packetWordCount)
        {
            packetPtr.reset(new BuswidthPattern());
            return packetWordCount;
        }
        // check if given data words start with sync word
        packetWordCount = isSyncWord(words, wordCount);
        if (0 < packetWordCount)
        {
            packetPtr.reset(new SyncWord());
            return packetWordCount;
        }
    }

    // no matching packet found
    packetPtr.reset();
    return 0;
}


bool V5BitstreamReader::behindSyncWord() const
{
    return m_syntaxChecker.behindSyncWord();
}


bool V5BitstreamReader::lastPacketWasType1() const
{
    return m_syntaxChecker.lastPacketWasType1();
}


RegisterAddress::address_t V5BitstreamReader::lastType1Address() const
{
    return m_syntaxChecker.lastType1Address();
}


void bil::readV5Bitstream(Bitstream& bitstream, const boost::uint32_t* words, size_t wordCount)
{
    V5BitstreamReader bsr;
    bsr.read(bitstream, words, wordCount);
}