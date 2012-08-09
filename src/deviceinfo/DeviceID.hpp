/**
* \file DeviceID.hpp
* \brief Contains declaration of device ID type.
*/

#pragma once
#ifndef BIL_DEVICEID_HPP
#define BIL_DEVICEID_HPP

#include <boost/cstdint.hpp>


namespace bil {

    /**
    * \brief Namespace for device ID type.
    *
    * Every Virtex device is identified by a unique number.
    */
    namespace DeviceID {

        /// Device id type.
        typedef boost::uint32_t ID_t;

    }

}

#endif
