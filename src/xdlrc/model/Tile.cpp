/**
* \file Tile.cpp
* \brief Contains definition of Tile class.
*/

#include <xdlrc/model/Tile.hpp>

using namespace bil;


Tile::Tile():
  m_name(),
  m_primitiveSites(),
  m_row(0),
  m_column(0),
  m_siteX(0),
  m_siteY(0),
  m_typeIndex(0)
{

}


std::string& Tile::name()
{
    return m_name;
}


const std::string& Tile::name() const
{
    return m_name;
}


PrimitiveSites& Tile::primitiveSites()
{
    return m_primitiveSites;
}


const PrimitiveSites& Tile::primitiveSites() const
{
    return m_primitiveSites;
}


void Tile::row(unsigned short row)
{
    m_row = row;
}


unsigned short Tile::row() const
{
    return m_row;
}


void Tile::column(unsigned short column)
{
    m_column = column;
}


unsigned short Tile::column() const
{
    return m_column;
}


void Tile::siteX(unsigned short x)
{
    m_siteX = x;
}


unsigned short Tile::siteX() const
{
    return m_siteX;
}


void Tile::siteY(unsigned short y)
{
    m_siteY = y;
}


unsigned short Tile::siteY() const
{
    return m_siteY;
}


void Tile::typeIndex(unsigned short index)
{
    m_typeIndex = index;
}


unsigned short Tile::typeIndex() const
{
    return m_typeIndex;
}


void Tile::clear()
{
    m_name.clear();
    m_primitiveSites.clear();
    m_row = 0;
    m_column = 0;
    m_siteX = 0;
    m_siteY = 0;
    m_typeIndex = 0;
}