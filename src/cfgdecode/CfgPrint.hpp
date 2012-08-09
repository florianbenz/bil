/**
* \file CfgPrint.hpp
* \brief Contains functions for printing PIPs and primitive site configurations.
*/

#pragma once
#ifndef BIL_CFGPRINT_HPP
#define BIL_CFGPRINT_HPP

#include <ostream>
#include <xdl/model/PIPRef.hpp>
#include <xdlrc/model/Device.hpp>


namespace bil {

    /**
    * \brief Prints out the given PIPs as a text list.
    * \param pipRefs The PIPs to print out.
    * \param device The device the PIPs are on.
    * \param outputStream Stream to print on.
    * \throws .
    */
    void printPIPs(const PIPRefs& pipRefs, const Device& device, std::ostream& outputStream);

    /**
    * \todo Function for printing primitive site configurations.
    */

}

#endif
