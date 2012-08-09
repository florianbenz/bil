/**
* \file WireConnection.cpp
* \brief Contains definition of WireConnection class.
*/

#include <xdlrc/model/WireConnection.hpp>

using namespace bil;


WireConnection::WireConnection():
  m_xOffset(0),
  m_yOffset(0),
  m_tileTypeIndex(0),
  m_wireIndex(0)
{

}


void WireConnection::xOffset(short offset)
{
    m_xOffset = offset;
}


short WireConnection::xOffset() const
{
    return m_xOffset;
}


void WireConnection::yOffset(short offset)
{
    m_yOffset = offset;
}


short WireConnection::yOffset() const
{
    return m_yOffset;
}


void WireConnection::tileTypeIndex(unsigned short index)
{
    m_tileTypeIndex = index;
}


unsigned short WireConnection::tileTypeIndex() const
{
    return m_tileTypeIndex;
}


void WireConnection::wireIndex(unsigned short index)
{
    m_wireIndex = index;
}


unsigned short WireConnection::wireIndex() const
{
    return m_wireIndex;
}


void WireConnection::clear()
{
    m_xOffset = 0;
    m_yOffset = 0;
    m_tileTypeIndex = 0;
    m_wireIndex = 0;
}