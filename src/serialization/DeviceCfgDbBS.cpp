/**
* \file DeviceCfgDbBS.cpp
* \brief Contains binary serialization functions for DeviceCfgDb class.
*/

#include <serialization/DeviceCfgDbBS.hpp>
#include <util/BinarySerialization.hpp>
#include <mappingdb/DeviceCfgDb.hpp>

using namespace bil;


void bil::writeBinary(const DeviceCfgDb& data, std::ostream& outputStream)
{
    writeBinary(data.m_tileTypeDbs, outputStream);
}


void bil::readBinary(DeviceCfgDb& data, std::istream& inputStream)
{
    readBinary(data.m_tileTypeDbs, inputStream);
}