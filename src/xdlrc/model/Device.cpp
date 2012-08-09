/**
* \file Device.cpp
* \brief Contains definition of Device class.
*/

#include <xdlrc/model/Device.hpp>

using namespace bil;


Device::Device():
  m_name(),
  m_tiles(),
  m_tileTypes(),
  m_primitiveTypes()
{

}


std::string& Device::name()
{
    return m_name;
}


const std::string& Device::name() const
{
    return m_name;
}


Tiles& Device::tiles()
{
    return m_tiles;
}


const Tiles& Device::tiles() const
{
    return m_tiles;
}


unsigned Device::maxRowIndex() const
{
    unsigned rowIndex = 0;
    size_t tileCount = m_tiles.size();
    for (size_t i = 0; i < tileCount; ++i)
    {
        const Tile& tile = m_tiles[i];
        if (tile.row() > rowIndex) rowIndex = tile.row();
    }
    return rowIndex;
}


unsigned Device::maxColumnIndex() const
{
    unsigned columnIndex = 0;
    size_t tileCount = m_tiles.size();
    for (size_t i = 0; i < tileCount; ++i)
    {
        const Tile& tile = m_tiles[i];
        if (tile.column() > columnIndex) columnIndex = tile.column();
    }
    return columnIndex;
}


TileTypes& Device::tileTypes()
{
    return m_tileTypes;
}


const TileTypes& Device::tileTypes() const
{
    return m_tileTypes;
}


PrimitiveTypes& Device::primitiveTypes()
{
    return m_primitiveTypes;
}


const PrimitiveTypes& Device::primitiveTypes() const
{
    return m_primitiveTypes;
}


void Device::clear()
{
    m_name.clear();
    m_tiles.clear();
    m_tileTypes.clear();
    m_primitiveTypes.clear();
}