/**
* \file V5FrameAddress.cpp
* \brief Contains definition of V5FrameAddress class.
*/

#include <configuration/V5FrameAddress.hpp>
#include <exception/Exception.hpp>

using namespace bil;

const unsigned BLOCK_BITSHIFT = 21;
const boost::uint32_t BLOCK_BITMASK = 0x7;
const unsigned LOWERHALF_BITSHIFT = 20;
const boost::uint32_t LOWERHALF_BITMASK = 0x1;
const unsigned ROW_BITSHIFT = 15;
const boost::uint32_t ROW_BITMASK = 0x1f;
const unsigned COLUMN_BITSHIFT = 7;
const boost::uint32_t COLUMN_BITMASK = 0xff;
const boost::uint32_t FRAME_BITMASK = 0x7f;


V5FrameAddress::V5FrameAddress():
  m_addressLayout(0),
  m_block(0),
  m_lowerHalf(false),
  m_rowIndex(0),
  m_columnIndex(0),
  m_frameIndex(0)
{
    // set to start address
    first();
}


V5FrameAddress::V5FrameAddress(const V5AddressLayout* layout):
  m_addressLayout(layout),
  m_block(0),
  m_lowerHalf(false),
  m_rowIndex(0),
  m_columnIndex(0),
  m_frameIndex(0)
{
    // set to start address
    first();
}


void V5FrameAddress::addressLayout(const V5AddressLayout* layout)
{
    m_addressLayout = layout;
}


const V5AddressLayout* V5FrameAddress::addressLayout() const
{
    return m_addressLayout;
}


void V5FrameAddress::block(V5CfgBlock::block_t block)
{
    if (BLOCK_MAX < block) throw Exception();
    m_block = block;
}


V5CfgBlock::block_t V5FrameAddress::block() const
{
    return m_block;
}


void V5FrameAddress::lowerHalf(bool lower)
{
    m_lowerHalf = lower;
}


bool V5FrameAddress::lowerHalf() const
{
    return m_lowerHalf;
}


void V5FrameAddress::rowIndex(unsigned char ri)
{
    if (ROWINDEX_MAX < ri) throw Exception();
    m_rowIndex = ri;
}


unsigned char V5FrameAddress::rowIndex() const
{
    return m_rowIndex;
}


void V5FrameAddress::columnIndex(unsigned char ci)
{
    if (COLUMNINDEX_MAX < ci) throw Exception();
    m_columnIndex = ci;
}


unsigned char V5FrameAddress::columnIndex() const
{
    return m_columnIndex;
}


void V5FrameAddress::frameIndex(unsigned char fi)
{
    if (FRAMEINDEX_MAX < fi) throw Exception();
    m_frameIndex = fi;
}


unsigned char V5FrameAddress::frameIndex() const
{
    return m_frameIndex;
}


void V5FrameAddress::first()
{
    m_block = V5CfgBlock::INTERCONNECT_AND_CFG;
    m_lowerHalf = false;
    m_rowIndex = 0;
    m_columnIndex = 0;
    m_frameIndex = 0;
}


void V5FrameAddress::last()
{
    // last address can only be determined if specific address layout is present
    if (0 == m_addressLayout) throw Exception();

    // set last address
    m_block = V5CfgBlock::BRAM_NONCFGDATA;
    m_lowerHalf = true;
    m_rowIndex = static_cast<unsigned char>(m_addressLayout->rowCount(false) - 1);
    m_columnIndex = static_cast<unsigned char>(m_addressLayout->columnCount(V5CfgBlock::BRAM_NONCFGDATA) - 1);
    V5CfgColumn::column_t ct = m_addressLayout->columnType(V5CfgBlock::BRAM_NONCFGDATA, m_columnIndex);
    m_frameIndex = static_cast<unsigned char>(m_addressLayout->frameCount(V5CfgBlock::BRAM_NONCFGDATA, ct) - 1);
}


bool V5FrameAddress::next()
{
    // increment only a valid address
    if (!isValid()) throw Exception();

    // increment frame index
    ++m_frameIndex;
    // return if no frame index overflow occurred
    V5CfgColumn::column_t ct = m_addressLayout->columnType(m_block, m_columnIndex);
    if (m_addressLayout->frameCount(m_block, ct) > m_frameIndex) return true;

    // reset frame index to zero and increment column index
    m_frameIndex = 0;
    ++m_columnIndex;
    // return if no column index overflow occurred
    if (m_addressLayout->columnCount(m_block) > m_columnIndex) return true;

    // reset column index to zero and increment row index
    m_columnIndex = 0;
    ++m_rowIndex;
    // return if no row index overflow occurred
    if (m_addressLayout->rowCount(m_lowerHalf) > m_rowIndex) return true;

    // reset row index to zero and increment upper/lower flag
    m_rowIndex = 0;
    m_lowerHalf = !m_lowerHalf;
    // return if no upper/lower flag overflow occurred
    if (m_lowerHalf) return true;

    // increment block
    ++m_block;
    // If block has no columns, this can only happen for BRAM_CONTENT and
    // BRAM_NONCFGDATA block on a device with no BRAMs. So increment block a
    // second time, in order to go to the next block.
    if (0 == m_addressLayout->columnCount(m_block)) ++m_block;
    // return if no block overflow occurred
    if (V5CfgBlock::BRAM_NONCFGDATA >= m_block) return true;

    // reached end of address space
    return false;
}


bool V5FrameAddress::isValid() const
{
    // address can only be valid under a specific address layout
    if (0 == m_addressLayout) return false;

    // test if rowIndex count is valid
    if (m_addressLayout->rowCount(m_lowerHalf) <= m_rowIndex) return false;
    // test if columnIndex count and block type is valid
    if (m_addressLayout->columnCount(m_block) <= m_columnIndex) return false;
    // test if frameIndex count is valid
    V5CfgColumn::column_t ct = m_addressLayout->columnType(m_block, m_columnIndex);
    if (m_addressLayout->frameCount(m_block, ct) <= m_frameIndex) return false;

    // valid!
    return true;
}


V5CfgColumn::column_t V5FrameAddress::columnType() const
{
    // type can only be determined if specific address layout is present
    if (0 == m_addressLayout) throw Exception();

    // test if rowIndex count is valid
    if (m_addressLayout->rowCount(m_lowerHalf) <= m_rowIndex) throw Exception();
    // test if columnIndex count and block type is valid
    if (m_addressLayout->columnCount(m_block) <= m_columnIndex) throw Exception();
    // test if frameIndex count is valid
    V5CfgColumn::column_t ct = m_addressLayout->columnType(m_block, m_columnIndex);
    if (m_addressLayout->frameCount(m_block, ct) <= m_frameIndex) throw Exception();

    // return resource type
    return ct;
}


void V5FrameAddress::rawAddress(boost::uint32_t ra)
{
    // decode raw address
    m_block = (ra >> BLOCK_BITSHIFT) & BLOCK_BITMASK;
    m_lowerHalf = ((ra >> LOWERHALF_BITSHIFT) & LOWERHALF_BITMASK) == 1;
    m_rowIndex = (ra >> ROW_BITSHIFT) & ROW_BITMASK;
    m_columnIndex = (ra >> COLUMN_BITSHIFT) & COLUMN_BITMASK;
    m_frameIndex = ra & FRAME_BITMASK;
}


boost::uint32_t V5FrameAddress::rawAddress() const
{
    // encode raw address from address parts
    return (m_block << BLOCK_BITSHIFT) |
        ((m_lowerHalf ? 1 : 0) << LOWERHALF_BITSHIFT) |
        (m_rowIndex << ROW_BITSHIFT) |
        (m_columnIndex << COLUMN_BITSHIFT) |
        m_frameIndex;
}