/**
* \file xdlcmpAlgo.hpp
* \brief Contains declaration of xdlcmp compare functions.
*/

#pragma once
#ifndef XDLCMPALGO_HPP
#define XDLCMPALGO_HPP

#include <ostream>
#include <xdl/model/Design.hpp>
#include <xdlrc/model/Device.hpp>


/**
* \brief Gets all PIPs of a design.
* \param design The design to get PIPs from.
* \param pipRefs The PIP list to fill.
*/
void getPIPs(const bil::Design& design, bil::PIPRefs& pipRefs);

/**
* \brief Compares two PIP lists and prints the results.
* \param refPIPRefs Reference list of PIPs.
* \param testPIPRefs Test list of PIPs.
* \param device Device the PIPs belong to.
* \param outputStream Stream to write to comparison results.
* \throws .
*/
void comparePIPs(const bil::PIPRefs& refPIPRefs, const bil::PIPRefs& testPIPRefs,
                 const bil::Device& device, std::ostream& outputStream);


#endif
