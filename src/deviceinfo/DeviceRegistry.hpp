/**
* \file DeviceRegistry.hpp
* \brief Contains declaration of DeviceRegistry class.
*/

#pragma once
#ifndef BIL_DEVICEREGISTRY_HPP
#define BIL_DEVICEREGISTRY_HPP

#include <cstring>
#include <map>
#include <string>
#include <utility>
#include <deviceinfo/DeviceID.hpp>
#include <serialization/DeviceRegistryBS.hpp>


namespace bil {

    /**
    * \brief A registry associating device IDs with their names and vice versa.
    *
    * Every device has got a device ID and a name. This registry holds pairs of
    * them and allows for lookup by ID and by name.
    */
    class DeviceRegistry {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new DeviceRegistry instance.
        */
        DeviceRegistry();


        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Copies a ID/name pair into registry.
        * \param deviceID ID of the device.
        * \param deviceName Name of the device.
        * \throws .
        */
        void insert(DeviceID::ID_t deviceID, const std::string& deviceName);

        /**
        * \brief Erases a ID/name pair from registry.
        * \param deviceID ID of the ID/name pair to erase.
        * \return True, if designated pair was found, false otherwise.
        */
        bool erase(DeviceID::ID_t deviceID);

        /**
        * \brief Erases a ID/name pair from registry.
        * \param deviceName Name of the ID/name pair to erase.
        * \return True, if designated pair was found, false otherwise.
        */
        bool erase(const std::string& deviceName);

        /**
        * \brief Erases all ID/name pairs.
        */
        void clear();


        /**********************************************************************/
        /* CONTENT ITERATION                                                  */
        /**********************************************************************/

        /**
        * \brief Gets the number of contained ID/name pairs.
        * \return The count.
        */
        size_t size() const;

        /// type for contained device ID/name pairs
        typedef std::pair<const DeviceID::ID_t, std::string> pair_t;

        /**
        * \brief Gets a device ID/name pair by index read only.
        * \param index Index of the pair to query.
        * \return Reference to pair at given index. Valid until it is erased.
        * \throws .
        */
        const pair_t& at(size_t index) const;


        /**********************************************************************/
        /* NAME & ID LOOKUP                                                   */
        /**********************************************************************/

        /**
        * \brief Looks up a device name by ID.
        * \param deviceID ID to query.
        * \return If found, copy of device name associated with given ID; an
        *         empty string otherwise.
        */
        std::string lookup(DeviceID::ID_t deviceID) const;

        /**
        * \brief Looks up a device ID by name.
        * \param deviceName Name to query.
        * \return If found, copy of device ID associated with given name; 0
        *         otherwise.
        */
        DeviceID::ID_t lookup(const std::string& deviceName) const;


    private:

        friend void writeBinary(const DeviceRegistry& data, std::ostream& outputStream);
        friend void readBinary(DeviceRegistry& data, std::istream& inputStream);


        typedef std::map<DeviceID::ID_t, std::string> IDMap_t;
        IDMap_t m_idMap;

        typedef std::map<std::string, DeviceID::ID_t> NameMap_t;
        NameMap_t m_nameMap;

    };

}

#endif
