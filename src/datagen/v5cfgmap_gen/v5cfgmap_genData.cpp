/**
* \file v5cfgmap_genData.cpp
* \brief Contains Virtex-5 tile columns.
*/

#include <datagen/v5cfgmap_gen/v5cfgmap_genData.hpp>


const FrameOffsets V5_NULL_TILECOLUMN[V5_FRAME_TILESPAN] = {
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0},
    {1, 0}, {1, 0}, {1, 0}
};

const FrameOffsets V5_INT_TILECOLUMN[V5_FRAME_TILESPAN] = {
    {39, 40}, {37, 38}, {35, 36}, {33, 34}, {31, 32},
    {29, 30}, {27, 28}, {25, 26}, {23, 24}, {21, 22},
    {20, 20},
    {18, 19}, {16, 17}, {14, 15}, {12, 13}, {10, 11},
    {8, 9}, {6, 7}, {4, 5}, {2, 3}, {0, 1}
};

const FrameOffsets V5_INT_INTERFACE_TILECOLUMN[V5_FRAME_TILESPAN] = {
    {31, 40}, {31, 40}, {31, 40}, {31, 40}, {31, 40},
    {21, 30}, {21, 30}, {21, 30}, {21, 30}, {21, 30},
    {20, 20},
    {10, 19}, {10, 19}, {10, 19}, {10, 19}, {10, 19},
    {0, 9}, {0, 9}, {0, 9}, {0, 9}, {0, 9}
};

const FrameOffsets V5_BRAM_TILECOLUMN[V5_FRAME_TILESPAN] = {
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {31, 40},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {21, 30},
    {20, 20},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {10, 19},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {0, 9}
};