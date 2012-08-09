/**
* \file PIPControlSet.cpp
* \brief Contains definition of PIPControlSet class.
*/

#include <mappingdb/PIPControlSet.hpp>

using namespace bil;


PIPControlSet::PIPControlSet():
  m_bitPositions(),
  m_pipBitValues()
{

}


BitPositions& PIPControlSet::bitPositions()
{
    return m_bitPositions;
}


const BitPositions& PIPControlSet::bitPositions() const
{
    return m_bitPositions;
}


PIPBitValues& PIPControlSet::pipBitValues()
{
    return m_pipBitValues;
}


const PIPBitValues& PIPControlSet::pipBitValues() const
{
    return m_pipBitValues;
}


void PIPControlSet::clear()
{
    m_bitPositions.clear();
    m_pipBitValues.clear();
}