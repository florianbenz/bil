/**
* \file SyncWord.cpp
* \brief Contains definition of SyncWord class.
*/

#include <bitstream/PacketVisitor.hpp>
#include <bitstream/SyncWord.hpp>

using namespace bil;


SyncWord* SyncWord::clone() const
{
    return new SyncWord(*this);
}


void SyncWord::accept(PacketVisitor& visitor) const
{
    visitor.visit(*this);
}