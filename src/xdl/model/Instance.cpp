/**
* \file Instance.cpp
* \brief Contains definition of Instance class.
*/

#include <xdl/model/Instance.hpp>

using namespace bil;


Instance::Instance():
  m_name(),
  m_attributes(),
  m_tileIndex(0),
  m_primitiveTypeIndex(0),
  m_primitiveSiteIndex(0),
  m_placed(false),
  m_bonded(false)
{

}


std::string& Instance::name()
{
    return m_name;
}


const std::string& Instance::name() const
{
    return m_name;
}


void Instance::primitiveTypeIndex(size_t index)
{
    m_primitiveTypeIndex = index;
}


size_t Instance::primitiveTypeIndex() const
{
    return m_primitiveTypeIndex;
}


void Instance::placed(bool placed)
{
    m_placed = placed;
}


bool Instance::placed() const
{
    return m_placed;
}


void Instance::bonded(bool bonded)
{
    m_bonded = bonded;
}


bool Instance::bonded() const
{
    return m_bonded;
}


void Instance::tileIndex(size_t index)
{
    m_tileIndex = index;
}


size_t Instance::tileIndex() const
{
    return m_tileIndex;
}


void Instance::primitiveSiteIndex(size_t index)
{
    m_primitiveSiteIndex = index;
}


size_t Instance::primitiveSiteIndex() const
{
    return m_primitiveSiteIndex;
}


std::string& Instance::attributes()
{
    return m_attributes;
}


const std::string& Instance::attributes() const
{
    return m_attributes;
}


void Instance::clear()
{
    m_name.clear();
    m_primitiveTypeIndex = 0;
    m_placed = false;
    m_bonded = false;
    m_tileIndex = 0;
    m_primitiveSiteIndex = 0;
    m_attributes.clear();
}