/**
* \file V5AddressLayoutRegistry.cpp
* \brief Contains definition of V5AddressLayoutRegistry class.
*/

#include <iterator>
#include <configuration/V5AddressLayoutRegistry.hpp>
#include <exception/Exception.hpp>

using namespace bil;


V5AddressLayoutRegistry::V5AddressLayoutRegistry():
  m_idMap()
{

}


void V5AddressLayoutRegistry::insert(DeviceID::ID_t deviceID, const V5AddressLayout& layout)
{
    // check if ID is already in use
    const IDMap_t::iterator lbID = m_idMap.lower_bound(deviceID);
    if ((m_idMap.end() != lbID) && (deviceID == lbID->first)) throw Exception();
    // insert address layout into map
    m_idMap.insert(lbID, std::make_pair(deviceID, layout));
}


bool V5AddressLayoutRegistry::erase(DeviceID::ID_t deviceID)
{
    // search given ID in name map
    const IDMap_t::iterator itID = m_idMap.find(deviceID);
    if (m_idMap.end() == itID) return false;
    // delete entry from map
    m_idMap.erase(itID);
    return true;
}


void V5AddressLayoutRegistry::clear()
{
    m_idMap.clear();
}


size_t V5AddressLayoutRegistry::size() const
{
    return m_idMap.size();
}


V5AddressLayoutRegistry::pair_t& V5AddressLayoutRegistry::at(size_t index)
{
    // check if index is in valid range
    if (m_idMap.size() <= index) throw Exception();
    // get map entry at index
    IDMap_t::iterator it = m_idMap.begin();
    std::advance(it, index);
    return *it;
}


const V5AddressLayoutRegistry::pair_t& V5AddressLayoutRegistry::at(size_t index) const
{
    // check if index is in valid range
    if (m_idMap.size() <= index) throw Exception();
    // get map entry at index
    IDMap_t::const_iterator it = m_idMap.begin();
    std::advance(it, index);
    return *it;
}


V5AddressLayout* V5AddressLayoutRegistry::lookup(DeviceID::ID_t deviceID)
{
    // search for ID in map
    const IDMap_t::iterator it = m_idMap.find(deviceID);
    // if found, return pointer to associated layout, else return 0
    if (m_idMap.end() == it) return 0;
    return &(it->second);
}


const V5AddressLayout* V5AddressLayoutRegistry::lookup(DeviceID::ID_t deviceID) const
{
    // search for ID in map
    const IDMap_t::const_iterator it = m_idMap.find(deviceID);
    // if found, return const pointer to associated layout, else return 0
    if (m_idMap.end() == it) return 0;
    return &(it->second);
}