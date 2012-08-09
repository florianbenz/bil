/**
* \file v5cfgmap_genAlgo.hpp
* \brief Function for filling a V5CfgTileMap with data.
*/

#pragma once
#ifndef V5CFGMAP_GENALGO_HPP
#define V5CFGMAP_GENALGO_HPP

#include <configuration/V5AddressLayout.hpp>
#include <correlation/cfgextraction/V5CfgTileMap.hpp>
#include <xdlrc/model/Device.hpp>


/**
* \brief Fills a V5CfgTileMap instance with data.
* \param map The instance to fill.
* \param device Target device description.
* \param addressLayout Configuration address layout of target device.
* \throws .
*/
void generateCfgTileMap(bil::V5CfgTileMap& map, const bil::Device& device,
                        const bil::V5AddressLayout& addressLayout);


#endif
