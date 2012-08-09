/**
* \file v5cfgmap_genAlgo.cpp
* \brief Function for filling a V5CfgTileMap with data.
*/

#include <datagen/v5cfgmap_gen/v5cfgmap_genAlgo.hpp>
#include <datagen/v5cfgmap_gen/v5cfgmap_genData.hpp>
#include <exception/Exception.hpp>
#include <xdlrc/util/TileLookup2D.hpp>

using namespace bil;


const char* const NULL_TYPENAME = "NULL";
const char* const T_TERM_INT_D_TYPENAME = "T_TERM_INT_D";
const char* const CLK_TERM_TOP_TYPENAME = "CLK_TERM_TOP";
const char* const INT_TYPENAME = "INT";

static size_t nullTypeIndex;
static size_t tTermIntDTypeIndex;
static size_t clkTermTopTypeIndex;
static size_t intTypeIndex;
static size_t intInterfaceTypeIndex;


static size_t getTileTypeIndex(const char* tileTypeName, const TileTypes& types)
{
    size_t tileTypeCount = types.size();
    for (size_t i = 0; i < tileTypeCount; ++i)
    {
        const std::string& typeName = (types[i]).name();
        if (0 == typeName.compare(tileTypeName)) return i;
    }
    throw Exception();
}


static size_t getTileTypeIndex(unsigned row, unsigned column, const TileLookup2D& tileLookup)
{
    const Tile* tile = tileLookup.lookup(row, column);
    if (0 == tile) throw Exception();
    return tile->typeIndex();
}


static void initMap(V5CfgTileMap& map)
{
    // clear all map entries and make them reference no data
    unsigned rowCount = map.rowCount();
    unsigned columnCount = map.columnCount();
    for (unsigned column = 0; column < columnCount; ++column)
    {
        for (unsigned row = 0; row < rowCount; ++row)
        {
            V5CfgTileMapEntry& entry = map.entries(row, column);
            entry.columnIndex = 0;
            entry.lowerHalf = false;
            entry.rowIndex = 0;
            entry.frameBeginIndex = 1;
            entry.frameEndIndex = 0;
            entry.wordBeginOffset = 1;
            entry.wordEndOffset = 0;
        }
    }
}


static void writeCfgColumnIndices(V5CfgTileMap& map, const TileLookup2D& tileLookup)
{
    // init column index and first T_TERM_INT_D flag
    unsigned char cfgColIndex = 0;
    bool firstTTermIntD = true;

    // walk along first row from left to right
    unsigned rowCount = tileLookup.rowCount();
    unsigned columnCount = tileLookup.columnCount();
    for (unsigned column = 0; column < columnCount; ++column)
    {
        // Get tile on top of current column and check its type: Only
        // T_TERM_INT_D, CLK_TERM_TOP, and NULL tile types must occur.
        // T_TERM_INT_D and CLK_TERM_TOP indicate the beginning of next
        // configuration column.
        size_t tileTypeIndex = getTileTypeIndex(0, column, tileLookup);
        if (tileTypeIndex != nullTypeIndex)
        {
            if (tileTypeIndex == tTermIntDTypeIndex)
            {
                // First T_TERM_INT_D does not begin a new configuration column.
                if (!firstTTermIntD) ++cfgColIndex;
                firstTTermIntD = false;
            }
            else if (tileTypeIndex == clkTermTopTypeIndex) ++cfgColIndex;
            else throw Exception();
        }
        // copy data to current column
        for (unsigned row = 0; row < rowCount; ++row)
        {
            V5CfgTileMapEntry& entry = map.entries(row, column);
            entry.columnIndex = cfgColIndex;
        }
    }
}


static void writeTileColumns(V5CfgTileMap& map, const TileLookup2D& tileLookup,
  unsigned upperCfgRows, unsigned lowerCfgRows)
{
    // walk along from left to right
    unsigned rowCount = tileLookup.rowCount();
    unsigned columnCount = tileLookup.columnCount();
    for (unsigned column = 0; column < columnCount; ++column)
    {
        size_t frameIndexBegin;
        size_t frameIndexEnd;
        const FrameOffsets* frameOffsets;

        // get type of tiles in current tile column and select the appropriate
        // tile column pattern
        size_t tileTypeIndex = getTileTypeIndex(5, column, tileLookup);
        if (tileTypeIndex == intTypeIndex)
        {
            // INT tiles (correlation gets good results on this type, so tag
            // these tiles with the configuration addresses)
            frameIndexBegin = V5_INT_FRAMEINDEX_BEGIN;
            frameIndexEnd = V5_INT_FRAMEINDEX_END;
            frameOffsets = V5_INT_TILECOLUMN;
        }
        else
        {
            // all others (correlation doesn't work at the moment with all other
            // tile types, so don't tag them with configuration addresses)
            frameIndexBegin = V5_NULL_FRAMEINDEX_BEGIN;
            frameIndexEnd = V5_NULL_FRAMEINDEX_END;
            frameOffsets = V5_NULL_TILECOLUMN;
        }

        // walk down the column row by row, and apply the previously selected
        // pattern
        bool lowerHalf = false;
        size_t cfgRowIndex = upperCfgRows - 1;
        size_t rowState = 0;
        for (unsigned row = 0; row < rowCount; ++row)
        {
            // copy temp vars into map entry
            V5CfgTileMapEntry& entry = map.entries(row, column);
            entry.lowerHalf = lowerHalf;
            entry.rowIndex = static_cast<unsigned char>(cfgRowIndex);
            entry.frameBeginIndex = static_cast<unsigned char>(frameIndexBegin);
            entry.frameEndIndex = static_cast<unsigned char>(frameIndexEnd);

            // state machine for applying pattern
            if (0 == rowState)
            {
                // tiles in the upper half of a configuration row
                entry.wordBeginOffset = 1;
                entry.wordEndOffset = 0;
                ++rowState;
            }
            else if (rowState <= V5_FRAME_TILESPAN)
            {
                // middle HCLK row
                const FrameOffsets& offsets = frameOffsets[rowState-1];
                entry.wordBeginOffset = static_cast<unsigned char>(offsets.wordBeginOffset);
                entry.wordEndOffset = static_cast<unsigned char>(offsets.wordEndOffset);
                ++rowState;
            }
            else
            {
                // tiles in lower half of configuration row
                entry.wordBeginOffset = 1;
                entry.wordEndOffset = 0;
                // handle configuration row count and upper/lower flag
                if (lowerHalf)
                {
                    if (lowerCfgRows > cfgRowIndex) ++cfgRowIndex;
                    else throw Exception();
                }
                else
                {
                    if (0 != cfgRowIndex) --cfgRowIndex;
                    else lowerHalf = true;
                }
                rowState = 1;
            }
        }

        // if the bottom most tile is reached, only this state is valid
        if (1 != rowState) throw Exception();
    }
}


void generateCfgTileMap(V5CfgTileMap& map, const Device& device,
  const V5AddressLayout& addressLayout)
{
    // tiles of these types mark configuration column sections
    const TileTypes& tileTypes = device.tileTypes();
    nullTypeIndex = getTileTypeIndex(NULL_TYPENAME, tileTypes);
    tTermIntDTypeIndex = getTileTypeIndex(T_TERM_INT_D_TYPENAME, tileTypes);
    clkTermTopTypeIndex = getTileTypeIndex(CLK_TERM_TOP_TYPENAME, tileTypes);

    // these tile types are important for detecting known tile columns
    intTypeIndex = getTileTypeIndex(INT_TYPENAME, tileTypes);

    // build tile lookup
    TileLookup2D tileLookup;
    tileLookup.reset(device);

    // check grid extends
    unsigned rowCount = tileLookup.rowCount();
    if (0 == rowCount) return;
    unsigned columnCount = tileLookup.columnCount();
    if (0 == columnCount) return;

    // set map size according to tile grid
    map.resize(rowCount, columnCount);

    // fill map with data
    initMap(map);
    writeCfgColumnIndices(map, tileLookup);
    writeTileColumns(map, tileLookup, addressLayout.upperRowCount(), addressLayout.lowerRowCount());
}