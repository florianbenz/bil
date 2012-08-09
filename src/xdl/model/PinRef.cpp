/**
* \file PinRef.cpp
* \brief Contains definition of PinRef class.
*/

#include <xdl/model/PinRef.hpp>

using namespace bil;


PinRef::PinRef():
  m_instanceIndex(0),
  m_pinIndex(0)
{

}


void PinRef::instanceIndex(size_t index)
{
    m_instanceIndex = index;
}


size_t PinRef::instanceIndex() const
{
    return m_instanceIndex;
}


void PinRef::pinIndex(size_t index)
{
    m_pinIndex = index;
}


size_t PinRef::pinIndex() const
{
    return m_pinIndex;
}


void PinRef::clear()
{
    m_instanceIndex = 0;
    m_pinIndex = 0;
}