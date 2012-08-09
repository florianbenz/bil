/**
* \file V5CfgFrame.cpp
* \brief Contains definition of V5CfgFrame class.
*/

#include <configuration/V5CfgFrame.hpp>

using namespace bil;


V5CfgFrame::V5CfgFrame()
{
    reset();
}


void V5CfgFrame::reset()
{
    memset(m_data, 0, WORDCOUNT);
}


boost::uint32_t* V5CfgFrame::data()
{
    return m_data;
}


const boost::uint32_t* V5CfgFrame::data() const
{
    return m_data;
}