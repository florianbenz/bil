/**
* \file Packet.cpp
* \brief Contains definition of Packet class.
*/

#include <bitstream/Packet.hpp>

using namespace bil;


Packet::~Packet()
{

}


Packet* new_clone(const Packet& src)
{
    return src.clone();
}