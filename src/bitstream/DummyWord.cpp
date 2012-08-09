/**
* \file DummyWord.cpp
* \brief Contains definition of DummyWord class.
*/

#include <bitstream/DummyWord.hpp>
#include <bitstream/PacketVisitor.hpp>

using namespace bil;


DummyWord::DummyWord():
  m_value()
{

}


DummyWord* DummyWord::clone() const
{
    return new DummyWord(*this);
}


void DummyWord::accept(PacketVisitor& visitor) const
{
    visitor.visit(*this);
}


void DummyWord::value(boost::uint32_t dummyValue)
{
    m_value = dummyValue;
}


boost::uint32_t DummyWord::value() const
{
    return m_value;
}