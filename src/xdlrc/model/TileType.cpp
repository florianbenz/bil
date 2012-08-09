/**
* \file TileType.cpp
* \brief Contains definition of TileType class.
*/

#include <xdlrc/model/TileType.hpp>

using namespace bil;


TileType::TileType():
  m_name(),
  m_siteTypes(),
  m_wires(),
  m_pips(),
  m_tag(0)
{

}


std::string& TileType::name()
{
    return m_name;
}


const std::string& TileType::name() const
{
    return m_name;
}


PrimitiveSiteTypes& TileType::siteTypes()
{
    return m_siteTypes;
}


const PrimitiveSiteTypes& TileType::siteTypes() const
{
    return m_siteTypes;
}


Wires& TileType::wires()
{
    return m_wires;
}


const Wires& TileType::wires() const
{
    return m_wires;
}


PIPs& TileType::pips()
{
    return m_pips;
}


const PIPs& TileType::pips() const
{
    return m_pips;
}


void TileType::tag(size_t t)
{
    m_tag = t;
}


size_t TileType::tag() const
{
    return m_tag;
}


void TileType::clear()
{
    m_name.clear();
    m_siteTypes.clear();
    m_wires.clear();
    m_pips.clear();
    m_tag = 0;
}