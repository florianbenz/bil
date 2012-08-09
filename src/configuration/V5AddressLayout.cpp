/**
* \file V5AddressLayout.cpp
* \brief Contains definition of V5AddressLayout class.
*/

#include <configuration/V5AddressLayout.hpp>
#include <exception/Exception.hpp>

using namespace bil;

// the following constants tell how much frames a resource needs per column type
// and per block:
// in INTERCONNECT_AND_CFG block
const unsigned CLB_CFG_FRAMES = 36;
const unsigned DSP_CFG_FRAMES = 28;
const unsigned BRAM_CFG_FRAMES = 30;
const unsigned IOB_CFG_FRAMES = 54;
const unsigned CLK_CFG_FRAMES = 4;
const unsigned SERIAL_CFG_FRAMES = 32;
// in BRAM_CONTENT block
const unsigned BRAM_CNT_FRAMES = 128;
// in SPECIAL block
const unsigned ALL_SPECIAL_FRAMES = 1;
// in BRAM_NONCFGDATA block
const unsigned BRAM_NONCFG_FRAMES = 1;


V5AddressLayout::V5AddressLayout():
  m_upperRowCount(1),
  m_lowerRowCount(1),
  m_columns(1, V5CfgColumn::CLB),
  m_bramCount(0)
{

}


V5AddressLayout::V5AddressLayout(unsigned upperRowCount, unsigned lowerRowCount, const V5CfgColumnSequence& columnSequence):
  m_upperRowCount(upperRowCount),
  m_lowerRowCount(lowerRowCount),
  m_columns(columnSequence), 
  m_bramCount(countBRAMs(columnSequence))
{
    // at least one row, at most ROWCOUNT_MAX rows
    if (0 == m_upperRowCount) throw Exception();
    if (ROWCOUNT_MAX < m_upperRowCount) throw Exception();
    // at least one row, at most ROWCOUNT_MAX rows
    if (0 == m_lowerRowCount) throw Exception();
    if (ROWCOUNT_MAX < m_lowerRowCount) throw Exception();
    // at least one column, at most COLUMNCOUNT_MAX rows
    if (0 == m_columns.size()) throw Exception();
    if (COLUMNCOUNT_MAX < m_columns.size()) throw Exception();
}


void V5AddressLayout::upperRowCount(unsigned count)
{
    // at least one row, at most ROWCOUNT_MAX rows
    if (0 == count) throw Exception();
    if (ROWCOUNT_MAX < count) throw Exception();
    m_upperRowCount = count;
}


unsigned V5AddressLayout::upperRowCount() const
{
    return m_upperRowCount;
}


void V5AddressLayout::lowerRowCount(unsigned count)
{
    // at least one row, at most ROWCOUNT_MAX rows
    if (0 == count) throw Exception();
    if (ROWCOUNT_MAX < count) throw Exception();
    m_lowerRowCount = count;
}


unsigned V5AddressLayout::lowerRowCount() const
{
    return m_lowerRowCount;
}


void V5AddressLayout::columnSequence(const V5CfgColumnSequence& columns)
{
    // at least one column, at most COLUMNCOUNT_MAX rows
    if (0 == columns.size()) throw Exception();
    if (COLUMNCOUNT_MAX < columns.size()) throw Exception();
    m_columns = columns;
    m_bramCount = countBRAMs(m_columns);
}


const V5CfgColumnSequence& V5AddressLayout::columnSequence() const
{
    return m_columns;
}


unsigned V5AddressLayout::rowCount(bool lowerHalf) const
{
    if (lowerHalf) return m_lowerRowCount;
    return m_upperRowCount;
}


unsigned V5AddressLayout::columnCount(V5CfgBlock::block_t block) const
{
    switch (block)
    {
    // Interconnection and configuration subspace and dynamic reconfiguration
    // subspace share the same columns. Return the size of the stored row.
    case V5CfgBlock::INTERCONNECT_AND_CFG: ;
    case V5CfgBlock::SPECIAL: return m_columns.size();

    // BRAM content and non-configuration subspace: return BRAM column count.
    case V5CfgBlock::BRAM_CONTENT: ;
    case V5CfgBlock::BRAM_NONCFGDATA: return m_bramCount;

    // invalid block: zero columns
    default: return 0;
    }
}


unsigned V5AddressLayout::frameCount(V5CfgBlock::block_t block, V5CfgColumn::column_t column) const
{
    switch (block)
    {
    // Interconnection and configuration subspace: every column type has its
    // specific number of frames per resource.
    case V5CfgBlock::INTERCONNECT_AND_CFG:
        switch (column)
        {
        case V5CfgColumn::CLB: return CLB_CFG_FRAMES;
        case V5CfgColumn::DSP: return DSP_CFG_FRAMES;
        case V5CfgColumn::BRAM: return BRAM_CFG_FRAMES;
        case V5CfgColumn::IOB: return IOB_CFG_FRAMES;
        case V5CfgColumn::CLK: return CLK_CFG_FRAMES;
        case V5CfgColumn::SERIAL: return SERIAL_CFG_FRAMES;
        default: return 0;
        };

    // BRAM content subspace: each BRAM needs 128 frames of memory data.
    // All other column types have no frames.
    case V5CfgBlock::BRAM_CONTENT:
        if (V5CfgColumn::BRAM == column) return BRAM_CNT_FRAMES;
        else return 0;

    // Dynamic reconfiguration subspace: one frame per column.
    case V5CfgBlock::SPECIAL:
        switch (column)
        {
        case V5CfgColumn::CLB: ;
        case V5CfgColumn::DSP: ;
        case V5CfgColumn::BRAM: ;
        case V5CfgColumn::IOB: ;
        case V5CfgColumn::CLK: ;
        case V5CfgColumn::SERIAL: return ALL_SPECIAL_FRAMES;
        default: return 0;
        };

    // BRAM non-configuration subspace: each BRAM needs 1 frame.
    // All other columns have no frames.
    case V5CfgBlock::BRAM_NONCFGDATA:
        if (V5CfgColumn::BRAM == column) return BRAM_NONCFG_FRAMES;
        else return 0;

    // invalid block: zero frames
    default: return 0;
    }
}


V5CfgColumn::column_t V5AddressLayout::columnType(V5CfgBlock::block_t block, size_t columnIndex) const
{
    switch (block)
    {
    // Interconnection and configuration subspace and dynamic reconfiguration
    // subspace share the same columns. Lookup column type and return it.
    case V5CfgBlock::INTERCONNECT_AND_CFG: ;
    case V5CfgBlock::SPECIAL:
        // test if columnIndex is valid
        if ((m_columns.size()) <= columnIndex) throw Exception();
        return m_columns[columnIndex];

    // BRAM content and non-configuration subspace subspace: return BRAM type.
    case V5CfgBlock::BRAM_CONTENT: ;
    case V5CfgBlock::BRAM_NONCFGDATA:
        // test if columnIndex is valid
        if (columnIndex >= m_bramCount) throw Exception();
        return V5CfgColumn::BRAM;

    // invalid block: nothing to return
    default: throw ;
    }
}


unsigned V5AddressLayout::countBRAMs(const V5CfgColumnSequence& columns) const
{
    // loop over given columns, count BRAM columns, and return their number
    unsigned count = 0;
    size_t columnCount = columns.size();
    for (size_t i = 0; i < columnCount; ++i)
        if (V5CfgColumn::BRAM == columns[i]) ++count;
    return count;
}