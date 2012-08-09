/**
* \file v5cfgmap_genData.hpp
* \brief Contains Virtex-5 tile columns.
*/

#pragma once
#ifndef V5CFGMAP_GENDATA_HPP
#define V5CFGMAP_GENDATA_HPP

#include <cstring>


/**
* \brief Describes the position of a chunk of data inside a frame.
*/
struct FrameOffsets {
    size_t wordBeginOffset;
    size_t wordEndOffset;
};


/**
* \brief Amount of tiles a frame spans vertically.
* \details This constant tells, how much tiles a frame spans vertically (i.e.
*          the height of a configuration row in tiles). The spacing NULL or HBRK
*          tiles are excluded.
*/
const size_t V5_FRAME_TILESPAN = 21;


//------------------------------------------------------------------------------

/// First frame index in an NULL tile column.
const size_t V5_NULL_FRAMEINDEX_BEGIN = 1;

/// Last frame index in an NULL tile column.
const size_t V5_NULL_FRAMEINDEX_END = 0;

/**
* \brief Offsets of the associated frame words for an NULL tile column.
* \details Can also be used for tile columns, that should be excluded from
*          correlation, since no frame data will be assigned to those tiles.
*/
extern const FrameOffsets V5_NULL_TILECOLUMN[V5_FRAME_TILESPAN];


//------------------------------------------------------------------------------

/// First frame index in an INT tile column.
const size_t V5_INT_FRAMEINDEX_BEGIN = 0;

/// Last frame index in an INT tile column.
const size_t V5_INT_FRAMEINDEX_END = 25;

/**
* \brief Offsets of the associated frame words for an INT tile column.
* \details Can also be used for tile columns of other types, on which the
*          configuration frame is evenly distributed over all tiles inside the
*          configuration row (e.g. CLBLM, CLBLL, IOB, ...).
*/
extern const FrameOffsets V5_INT_TILECOLUMN[V5_FRAME_TILESPAN];


//------------------------------------------------------------------------------

/// First frame index in an INT_INTERFACE tile column.
const size_t V5_INT_INTERFACE_FRAMEINDEX_BEGIN = 26;

/// Last frame index in an INT_INTERFACE tile column.
const size_t V5_INT_INTERFACE_FRAMEINDEX_END = 27;

/**
* \brief Offsets of the associated frame words for an INT_INTERFACE tile column.
* \details Can also be used for tile columns of other types, on which tiles in
*          groups of five share the same data of the configuration frame.
*/
extern const FrameOffsets V5_INT_INTERFACE_TILECOLUMN[V5_FRAME_TILESPAN];


//------------------------------------------------------------------------------

/// First frame index in an BRAM tile column.
const size_t V5_BRAM_FRAMEINDEX_BEGIN = 28;

/// Last frame index in an BRAM tile column.
const size_t V5_BRAM_FRAMEINDEX_END = 30;

/**
* \brief Offsets of the associated frame words for an BRAM tile column.
* \details Can also be used for tile columns of other types, on which every
*          fifth tile gets data of the configuration frame (e.g. DSP48, ...).
*/
extern const FrameOffsets V5_BRAM_TILECOLUMN[V5_FRAME_TILESPAN];


#endif
