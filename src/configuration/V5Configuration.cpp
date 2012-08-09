/**
* \file V5Configuration.cpp
* \brief Contains definition of V5Configuration class.
*/

#include <iterator>
#include <utility>
#include <configuration/V5Configuration.hpp>
#include <exception/Exception.hpp>

using namespace bil;


V5Configuration::V5Configuration():
  m_addressLayout(),
  m_configuration()
{

}


V5Configuration::V5Configuration(const V5AddressLayout& layout):
  m_addressLayout(layout),
  m_configuration()
{

}


V5Configuration::V5Configuration(const V5Configuration& src):
  m_addressLayout(src.m_addressLayout),
  m_configuration()
{
    // copy all map contents, but set addresses to this address layout
    container_t::iterator itDst = m_configuration.begin();
    container_t::const_iterator itSrc = src.m_configuration.begin();
    const container_t::const_iterator itSrcEnd = src.m_configuration.end();
    for (; itSrc != itSrcEnd; ++itSrc)
    {
        // make temporary copy of source address and set it to new layout
        V5FrameAddress address = itSrc->first;
        address.addressLayout(&m_addressLayout);
        // insert it into destination map
        itDst = m_configuration.insert(itDst, std::make_pair(address, itSrc->second));
    }
}


V5Configuration& V5Configuration::operator=(const V5Configuration& src)
{
    // copy address layout
    m_addressLayout = src.m_addressLayout;

    // copy all map contents, but set addresses to this address layout
    m_configuration.clear();
    container_t::iterator itDst = m_configuration.begin();
    container_t::const_iterator itSrc = src.m_configuration.begin();
    const container_t::const_iterator itSrcEnd = src.m_configuration.end();
    for (; itSrc != itSrcEnd; ++itSrc)
    {
        // make temporary copy of source address and set it to new layout
        V5FrameAddress address = itSrc->first;
        address.addressLayout(&m_addressLayout);
        // insert it into destination map
        itDst = m_configuration.insert(itDst, std::make_pair(address, itSrc->second));
    }

    // return self-reference
    return *this;
}


void V5Configuration::addressLayout(const V5AddressLayout& layout)
{
    // only take action if layouts differ
    if (layout == m_addressLayout) return;
    // delete current contents and copy new layout
    clear();
    m_addressLayout = layout;
}


const V5AddressLayout& V5Configuration::addressLayout() const
{
    return m_addressLayout;
}


bool V5Configuration::insert(const V5FrameAddress& address, const V5CfgFrame& frame)
{
    // create a temporary copy of given address and set its address layout
    // pointer to the one currently used
    V5FrameAddress tempAddr = address;
    tempAddr.addressLayout(&m_addressLayout);
    // test its validity under that layout
    if (!tempAddr.isValid()) throw Exception();

    // Check if map contains already a frame for given frame address. If so,
    // copy the new frame into the old one. Else create a new pair using given
    // frame address and frame.
    const container_t::iterator lb = m_configuration.lower_bound(tempAddr);
    if ((m_configuration.end() != lb) && (tempAddr == lb->first))
    {
        lb->second = frame;
        return false;
    }
    else
    {
        m_configuration.insert(lb, std::make_pair(tempAddr, frame));
        return true;
    }
}


bool V5Configuration::erase(const V5FrameAddress& address)
{
    return (0 != m_configuration.erase(address));
}


void V5Configuration::clear()
{
    m_configuration.clear();
}


size_t V5Configuration::size() const
{
    return m_configuration.size();
}


V5Configuration::pairptrs_t V5Configuration::contents()
{
    // create vector for holding the address references
    pairptrs_t ret;
    ret.reserve(m_configuration.size());

    // fill it
    container_t::iterator it = m_configuration.begin();
    const container_t::iterator itEnd = m_configuration.end();
    for (; it != itEnd; ++it) ret.push_back(&(*it));

    // return it
    return ret;
}


V5Configuration::pairconstptrs_t V5Configuration::contents() const
{
    // create vector for holding the address references
    pairconstptrs_t ret;
    ret.reserve(m_configuration.size());

    // fill it
    container_t::const_iterator it = m_configuration.begin();
    const container_t::const_iterator itEnd = m_configuration.end();
    for (; it != itEnd; ++it) ret.push_back(&(*it));

    // return it
    return ret;
}


V5CfgFrame* V5Configuration::lookup(const V5FrameAddress& address)
{
    // search for frame address in map
    const container_t::iterator it = m_configuration.find(address);
    // if found, return pointer to associated frame, else 0
    if (m_configuration.end() == it) return 0;
    return &(it->second);
}


const V5CfgFrame* V5Configuration::lookup(const V5FrameAddress& address) const
{
    // search for frame address in map
    const container_t::const_iterator it = m_configuration.find(address);
    // if found, return pointer to associated frame, else 0
    if (m_configuration.end() == it) return 0;
    return &(it->second);
}