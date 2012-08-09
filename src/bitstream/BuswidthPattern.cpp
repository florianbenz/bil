/**
* \file BuswidthPattern.cpp
* \brief Contains definition of BuswidthPattern class.
*/

#include <bitstream/BuswidthPattern.hpp>
#include <bitstream/PacketVisitor.hpp>

using namespace bil;


BuswidthPattern* BuswidthPattern::clone() const
{
    return new BuswidthPattern(*this);
}


void BuswidthPattern::accept(PacketVisitor& visitor) const
{
    visitor.visit(*this);
}