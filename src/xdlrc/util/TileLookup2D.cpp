/**
* \file TileLookup2D.cpp
* \brief Contains definition of TileLookup2D class.
*/

#include <xdlrc/model/Device.hpp>
#include <xdlrc/util/TileLookup2D.hpp>

using namespace bil;


TileLookup2D::TileLookup2D():
  m_rowCount(0),
  m_columnCount(0),
  m_tiles()
{

}


unsigned TileLookup2D::rowCount() const
{
    return m_rowCount;
}


unsigned TileLookup2D::columnCount() const
{
    return m_columnCount;
}


const Tile* TileLookup2D::lookup(unsigned row, unsigned column) const
{
    if (row >= m_rowCount) return 0;
    if (column >= m_columnCount) return 0;
    return m_tiles[(row * m_columnCount) + column];
}


void TileLookup2D::reset(const Device& device)
{
    // get device row and col count
    unsigned rowCount = device.maxRowIndex() + 1;
    unsigned columnCount = device.maxColumnIndex() + 1;

    // set lookup size according to row and col count
    m_tiles.clear();
    m_tiles.resize(rowCount * columnCount, 0);
    m_rowCount = rowCount;
    m_columnCount = columnCount;

    // set pointers to tiles
    const Tiles& tiles = device.tiles();
    size_t tilesSize = tiles.size();
    for (size_t i = 0; i < tilesSize; ++i)
    {
        const Tile& tile = tiles[i];
        size_t index = (tile.row() * m_columnCount) + tile.column();
        m_tiles[index] = &tile;
    }
}


void TileLookup2D::clear()
{
    m_rowCount = 0;
    m_columnCount = 0;
    m_tiles.clear();
}