/**
* \file DeviceRegistry.cpp
* \brief Contains definition of DeviceRegistry class.
*/

#include <iterator>
#include <utility>
#include <deviceinfo/DeviceRegistry.hpp>
#include <exception/Exception.hpp>

using namespace bil;


DeviceRegistry::DeviceRegistry()
{

}


void DeviceRegistry::insert(DeviceID::ID_t deviceID, const std::string& deviceName)
{
    // device name must not be empty
    if (0 == deviceID) throw Exception();
    if (deviceName.empty()) throw Exception();

    // check if ID is already in use
    IDMap_t::iterator lbID = m_idMap.lower_bound(deviceID);
    if ((m_idMap.end() != lbID) && (deviceID == lbID->first)) throw Exception();

    // check if name is already in use
    NameMap_t::iterator lbName = m_nameMap.lower_bound(deviceName);
    if ((m_nameMap.end() != lbName) && (deviceName == lbName->first)) throw Exception();

    // insert device info into both maps
    m_idMap.insert(lbID, std::make_pair(deviceID, deviceName));
    m_nameMap.insert(lbName, std::make_pair(deviceName, deviceID));
}


bool DeviceRegistry::erase(DeviceID::ID_t deviceID)
{
    // search given ID in ID map
    IDMap_t::iterator itID = m_idMap.find(deviceID);
    if (m_idMap.end() == itID) return false;

    // search for ID's name in name map
    NameMap_t::iterator itName = m_nameMap.find(itID->second);

    // delete entries from both maps
    m_idMap.erase(itID);
    m_nameMap.erase(itName);
    return true;
}


bool DeviceRegistry::erase(const std::string& deviceName)
{
    // search given name in name map
    NameMap_t::iterator itName = m_nameMap.find(deviceName);
    if (m_nameMap.end() == itName) return false;

    // search for name's ID in ID map
    IDMap_t::iterator itID = m_idMap.find(itName->second);

    // delete entries from both maps
    m_idMap.erase(itID);
    m_nameMap.erase(itName);
    return true;
}


void DeviceRegistry::clear()
{
    m_idMap.clear();
    m_nameMap.clear();
}


size_t DeviceRegistry::size() const
{
    return m_idMap.size();
}


const DeviceRegistry::pair_t& DeviceRegistry::at(size_t index) const
{
    // check if index is in valid range
    if (m_idMap.size() <= index) throw Exception();
    // get map entry at index
    IDMap_t::const_iterator it = m_idMap.begin();
    std::advance(it, index);
    return *it;
}


std::string DeviceRegistry::lookup(DeviceID::ID_t deviceID) const
{
    // search for ID in map
    IDMap_t::const_iterator it = m_idMap.find(deviceID);
    // if found, return device name copy; else return an empty string
    if (m_idMap.end() == it) return std::string();
    return it->second;
}


DeviceID::ID_t DeviceRegistry::lookup(const std::string& deviceName) const
{
    // search for ID in map
    NameMap_t::const_iterator it = m_nameMap.find(deviceName);
    // if found, return device ID; else return 0
    if (m_nameMap.end() == it) return 0;
    return it->second;
}