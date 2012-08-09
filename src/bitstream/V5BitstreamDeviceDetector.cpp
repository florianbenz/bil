/**
* \file V5BitstreamDeviceDetector.cpp
* \brief Contains definition of V5BitstreamDeviceDetector class.
*/

#include <bitstream/Bitstream.hpp>
#include <bitstream/V5BitstreamDeviceDetector.hpp>
#include <packetprocessor/V5RegisterAddress.hpp>
#include <exception/Exception.hpp>

using namespace bil;


V5BitstreamDeviceDetector::V5BitstreamDeviceDetector()
{
    reset();
}


DeviceID::ID_t V5BitstreamDeviceDetector::deviceID() const
{
    return m_id;
}


void V5BitstreamDeviceDetector::reset()
{
    V5BitstreamSyntaxChecker::reset();
    m_id = 0;
}


void V5BitstreamDeviceDetector::visit(const Type1Packet& type1Packet)
{
    V5BitstreamSyntaxChecker::visit(type1Packet);
    checkDeviceID(type1Packet);
}


void V5BitstreamDeviceDetector::visit(const Type2Packet& type2Packet)
{
    V5BitstreamSyntaxChecker::visit(type2Packet);
    checkDeviceID(type2Packet);
}


void V5BitstreamDeviceDetector::checkDeviceID(const Type2Packet& type2Packet)
{
    // only writes to IDCODE register contain the device ID
    if (PacketOpcode::REGISTER_WRITE != type2Packet.opcode()) return;
    if (V5RegisterAddress::IDCODE != lastType1Address()) return;
    if (1 != type2Packet.wordCount()) return;

    // device ID found
    const DeviceID::ID_t id = *(type2Packet.dataWords());
    // check for multiple contradicting device IDs
    if ((0 != m_id) && (id != m_id)) throw Exception();
    // store device ID
    m_id = id;
}


DeviceID::ID_t bil::detectV5DeviceType(Bitstream& bitstream)
{
    V5BitstreamDeviceDetector deviceDetector;
    bitstream.runVisitor(deviceDetector);
    return deviceDetector.deviceID();
}