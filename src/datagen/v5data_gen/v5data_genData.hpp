/**
* \file v5data_genData.hpp
* \brief Contains definition of Virtex-5 device names, IDs, and address layouts.
*/

#pragma once
#ifndef V5DATA_GENDATA_HPP
#define V5DATA_GENDATA_HPP

#include <cstring>
#include <boost/cstdint.hpp>
#include <configuration/V5AddressLayout.hpp>


/// number of devices in Virtex-5 family
const size_t V5_DEVICE_COUNT = 26;


/// Virtex-5 device names
extern const char* const V5_DEVICE_NAMES[V5_DEVICE_COUNT];

/// Virtex-5 device IDs
extern const boost::uint32_t V5_DEVICE_IDS[V5_DEVICE_COUNT];

/// Virtex-5 address layouts
extern const bil::V5AddressLayout V5_ADDRESS_LAYOUTS[V5_DEVICE_COUNT];


#endif
