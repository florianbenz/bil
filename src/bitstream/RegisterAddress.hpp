/**
* \file RegisterAddress.hpp
* \brief Contains packet register address type.
*/

#pragma once
#ifndef BIL_REGISTERADDRESS_HPP
#define BIL_REGISTERADDRESS_HPP


namespace bil {

    /**
    * \brief Namespace for register address type.
    *
    * Some packets in the bitstream contain a register address, which tells
    * configuration logic (i.e. the packet processor) where to put the packet's
    * data.
    */
    namespace RegisterAddress {

        /// Packet register address type.
        typedef unsigned char address_t;

    }

}

#endif
