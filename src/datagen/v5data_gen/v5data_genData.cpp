/**
* \file v5data_genData.cpp
* \brief Contains definition of Virtex-5 device names, IDs, and address layouts.
*/

#include <boost/assign/list_of.hpp>
#include <datagen/v5data_gen/v5data_genData.hpp>

using namespace bil;
using namespace bil::V5CfgColumn;


const char* const V5_DEVICE_NAMES[V5_DEVICE_COUNT] =
{
    "xc5vlx30",
    "xc5vlx50",
    "xc5vlx85",
    "xc5vlx110",
    "xc5vlx155",
    "xc5vlx220",
    "xc5vlx330",

    "xc5vlx20t",
    "xc5vlx30t",
    "xc5vlx50t",
    "xc5vlx85t",
    "xc5vlx110t",
    "xc5vlx155t",
    "xc5vlx220t",
    "xc5vlx330t",

    "xc5vsx35t",
    "xc5vsx50t",
    "xc5vsx95t",
    "xc5vsx240t",

    "xc5vfx30t",
    "xc5vfx70t",
    "xc5vfx100t",
    "xc5vfx130t",
    "xc5vfx200t",

    "xc5vtx150t",
    "xc5vtx240t"
};


const boost::uint32_t V5_DEVICE_IDS[V5_DEVICE_COUNT] =
{
    0x286e093,
    0x2896093,
    0x28ae093,
    0x28d6093,
    0x28ec093,
    0x290c093,
    0x295c093,

    0x2a56093,
    0x2a6e093,
    0x2a96093,
    0x2aae093,
    0x2ad6093,
    0x2aec093,
    0x2b0c093,
    0x2b5c093,

    0x2e72093,
    0x2e9a093,
    0x2ece093,
    0x2f3e093,

    0x3276093,
    0x32c6093,
    0x32d8093,
    0x3300093,
    0x3334093,

    0x4502093,
    0x453e093
};


const V5AddressLayout V5_ADDRESS_LAYOUTS[V5_DEVICE_COUNT] =
{
    V5AddressLayout(2, 2, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)
        (CLB)(CLB)(CLB)),

    V5AddressLayout(3, 3, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)
        (CLB)(CLB)(CLB)),

    V5AddressLayout(3, 3, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)
        (CLB)(CLB)),

    V5AddressLayout(6, 6, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)
        (CLB)(CLB)),


    V5AddressLayout(1, 2, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (SERIAL)),

    V5AddressLayout(2, 2, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)
        (CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(3, 3, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)
        (CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(3, 3, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(6, 6, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(SERIAL)),


    V5AddressLayout(2, 2, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(3, 3, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)
        (CLB)(IOB)(CLK)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)
        (IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(6, 6, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(DSP)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)
        (DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (SERIAL)),


    V5AddressLayout(2, 2, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)
        (CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL)),

    V5AddressLayout(4, 4, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)
        (CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)
        (CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(5, 5, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)
        (CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)
        (CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(6, 6, boost::assign::list_of(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)
        (CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)
        (CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(DSP)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(SERIAL)),


    V5AddressLayout(5, 5, boost::assign::list_of(SERIAL)(CLB)(CLB)(CLB)(CLB)
        (IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(IOB)(CLK)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)
        (CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(SERIAL)),

    V5AddressLayout(6, 6, boost::assign::list_of(SERIAL)(CLB)(CLB)(CLB)(CLB)
        (IOB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(DSP)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(IOB)
        (CLK)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(CLB)
        (CLB)(CLB)(CLB)(CLB)(CLB)(BRAM)(CLB)(CLB)(CLB)(CLB)(IOB)(CLB)(CLB)(CLB)
        (CLB)(BRAM)(SERIAL))
};