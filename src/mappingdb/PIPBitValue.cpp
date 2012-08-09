/**
* \file PIPBitValue.cpp
* \brief Contains definition of PIPBitValue class.
*/

#include <mappingdb/PIPBitValue.hpp>

using namespace bil;


PIPBitValue::PIPBitValue():
  m_pipIndex(0),
  m_bitValue(0)
{

}


void PIPBitValue::pipIndex(size_t index)
{
    m_pipIndex = index;
}


size_t PIPBitValue::pipIndex() const
{
    return m_pipIndex;
}


void PIPBitValue::bitValue(boost::uint32_t value)
{
    m_bitValue = value;
}


boost::uint32_t PIPBitValue::bitValue() const
{
    return m_bitValue;
}


void PIPBitValue::clear()
{
    m_pipIndex = 0;
    m_bitValue = 0;
}