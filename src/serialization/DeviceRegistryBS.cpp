/**
* \file DeviceRegistryBS.cpp
* \brief Contains binary serialization functions for DeviceRegistry class.
*/

#include <serialization/DeviceRegistryBS.hpp>
#include <util/BinarySerialization.hpp>
#include <deviceinfo/DeviceRegistry.hpp>

using namespace bil;


void bil::writeBinary(const DeviceRegistry& data, std::ostream& outputStream)
{
    writeBinary(data.m_idMap, outputStream);
}


void bil::readBinary(DeviceRegistry& data, std::istream& inputStream)
{
    readBinary(data.m_idMap, inputStream);

    // clear name map
    DeviceRegistry::NameMap_t& nameMap = data.m_nameMap;
    nameMap.clear();

    // refill name map
    DeviceRegistry::IDMap_t& idMap = data.m_idMap;
    DeviceRegistry::IDMap_t::const_iterator it = idMap.begin();
    DeviceRegistry::IDMap_t::const_iterator itEnd = idMap.end();
    for (; it != itEnd; ++it)
        nameMap.insert(std::make_pair(it->second, it->first));
}