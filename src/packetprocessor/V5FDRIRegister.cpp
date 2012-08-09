/**
* \file V5FDRIRegister.cpp
* \brief Contains definition of V5FDRIRegister class.
*/

#include <exception/Exception.hpp>
#include <packetprocessor/V5CMDRegister.hpp>
#include <packetprocessor/V5FARRegister.hpp>
#include <packetprocessor/V5FDRIRegister.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>

using namespace bil;


V5FDRIRegister::V5FDRIRegister(const V5CMDRegister& cmdReg, V5FARRegister& farReg):
  Register(V5RegisterAddress::FDRI, V5RegisterAddress::FDRI_STRING, true, false),
  m_configuration(),
  m_cmdReg(cmdReg),
  m_farReg(farReg),
  m_previousFrame()
{
    // copy address layout into FAR's address instance
    V5FrameAddress& fa = m_farReg.frameAddress();
    fa.addressLayout(&(m_configuration.addressLayout()));
}


void V5FDRIRegister::write(const boost::uint32_t* words, size_t wordCount)
{
    Register::write(words, wordCount);

    // writing 0 words does nothing
    if (0 == wordCount) return;

    // check that wordCount denotes an integer number of frames
    if (0 != wordCount % V5CfgFrame::WORDCOUNT) throw Exception();
    // check that CMD register is in WCFG state
    if (V5CommandCode::WCFG != m_cmdReg.commandCode()) throw Exception();

    // get frame address from FAR register
    V5FrameAddress& fa = m_farReg.frameAddress();

    // loop over given data frame by frame
    V5CfgFrame frame;
    const boost::uint32_t* wordsLast = 0;
    const boost::uint32_t* wordsEnd = words + wordCount;
    while (words < wordsEnd)
    {
        // load frame
        memcpy(frame.data(), words, V5CfgFrame::WORDCOUNT << 2);
        wordsLast = words;
        words += V5CfgFrame::WORDCOUNT;

        // copy frame at FAR frame address into configuration object
        m_configuration.insert(fa, frame);

        // auto increment frame address and skip if necessary padding frames
        // (after every row there are 2 padding frames)
        unsigned prevRow = fa.rowIndex();
        fa.next();
        if (fa.rowIndex() != prevRow) words += (V5CfgFrame::WORDCOUNT << 1);
    }

    // cache last written frame data for later use
    memcpy(m_previousFrame.data(), wordsLast, V5CfgFrame::WORDCOUNT << 2);
}


void V5FDRIRegister::writePreviousFrame()
{
    // get frame address from FAR register
    V5FrameAddress& fa = m_farReg.frameAddress();
    // copy frame at FAR frame address into configuration object
    m_configuration.insert(fa, m_previousFrame);
}


V5Configuration& V5FDRIRegister::configuration()
{
    return m_configuration;
}


const V5Configuration& V5FDRIRegister::configuration() const
{
    return m_configuration;
}


const V5CMDRegister& V5FDRIRegister::cmdRegister() const
{
    return m_cmdReg;
}


V5FARRegister& V5FDRIRegister::farRegister() const
{
    return m_farReg;
}