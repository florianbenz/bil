/**
* \file V5PacketVisitor.cpp
* \brief Contains definition of V5PacketVisitor class.
*/

#include <bitstream/V5PacketVisitor.hpp>
#include <exception/Exception.hpp>

using namespace bil;


void V5PacketVisitor::visit(const BuswidthPattern&)
{
    // do nothing since this is a valid packet for Virtex-5 bitstreams
}


void V5PacketVisitor::visit(const DummyWord&)
{
    // do nothing since this is a valid packet for Virtex-5 bitstreams
}


void V5PacketVisitor::visit(const SyncWord&)
{
    // do nothing since this is a valid packet for Virtex-5 bitstreams
}


void V5PacketVisitor::visit(const Type1Packet&)
{
    // do nothing since this is a valid packet for Virtex-5 bitstreams
}


void V5PacketVisitor::visit(const Type2Packet&)
{
    // do nothing since this is a valid packet for Virtex-5 bitstreams
}


void V5PacketVisitor::visit(const Packet&)
{
    // this is not valid in a Virtex-5 bitstream
    throw Exception();
}