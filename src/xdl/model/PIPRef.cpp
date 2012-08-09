/**
* \file PIPRef.cpp
* \brief Contains definition of PIPRef class.
*/

#include <xdl/model/PIPRef.hpp>

using namespace bil;


PIPRef::PIPRef():
  m_tileIndex(0),
  m_pipIndex(0)
{

}


void PIPRef::tileIndex(size_t index)
{
    m_tileIndex = index;
}


size_t PIPRef::tileIndex() const
{
    return m_tileIndex;
}


void PIPRef::pipIndex(size_t index)
{
    m_pipIndex = index;
}


size_t PIPRef::pipIndex() const
{
    return m_pipIndex;
}


void PIPRef::clear()
{
    m_tileIndex = 0;
    m_pipIndex = 0;
}