/**
* \file V5AddressLayoutRegistry.hpp
* \brief Contains declaration of V5AddressLayoutRegistry class.
*/

#pragma once
#ifndef BIL_V5ADDRESSLAYOUTREGISTRY_HPP
#define BIL_V5ADDRESSLAYOUTREGISTRY_HPP

#include <cstring>
#include <map>
#include <utility>
#include <configuration/V5AddressLayout.hpp>
#include <deviceinfo/DeviceID.hpp>


namespace bil {

    /**
    * \brief A registry to hold and lookup V5AddressLayout instances.
    *
    * This registry holds V5AddressLayout instances. Each address layout is
    * associated with the ID of the corresponding device and can be looked up
    * by it.
    */
    class V5AddressLayoutRegistry {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5AddressLayoutRegistry instance.
        */
        V5AddressLayoutRegistry();


        /**********************************************************************/
        /* MODIFIERS                                                          */
        /**********************************************************************/

        /**
        * \brief Inserts a device ID/address layout pair into registry.
        * \param deviceID Device ID given layout will be associated with.
        * \param layout V5AddressLayout instance that will be copied.
        * \throws .
        */
        void insert(DeviceID::ID_t deviceID, const V5AddressLayout& layout);

        /**
        * \brief Erases a device ID/address layout pair from registry.
        * \param deviceID Device ID of pair to erase.
        * \return True, if designated pair was found, false otherwise.
        */
        bool erase(DeviceID::ID_t deviceID);

        /**
        * \brief Erases all device ID/address layout pairs.
        */
        void clear();


        /**********************************************************************/
        /* CONTENT ITERATION                                                  */
        /**********************************************************************/

        /**
        * \brief Gets the number of contained device ID/address layout pairs.
        * \return Number of contained pairs.
        */
        size_t size() const;

        /// type for contained device ID/address layout pairs
        typedef std::pair<const DeviceID::ID_t, V5AddressLayout> pair_t;

        /**
        * \brief Gets a device ID/address layout pair by index.
        * \param index Index of the pair to query.
        * \return Reference to pair at given index. Valid until it is erased.
        * \throws .
        */
        pair_t& at(size_t index);

        /**
        * \brief Gets a device ID/address layout pair by index read only.
        * \param index Index of the pair to query.
        * \return Reference to pair at given index. Valid until it is erased.
        * \throws .
        */
        const pair_t& at(size_t index) const;


        /**********************************************************************/
        /* ADDRESS LAYOUT LOOKUP                                              */
        /**********************************************************************/

        /**
        * \brief Looks up an address layout by ID.
        * \param deviceID Device ID associated with the layout to get.
        * \return Pointer to queried V5AddressLayout instance if found, 0
        *         otherwise. Valid until that instance is erased.
        */
        V5AddressLayout* lookup(DeviceID::ID_t deviceID);

        /**
        * \brief Looks up an address layout by ID read only.
        * \param deviceID Device ID associated with the layout to get.
        * \return Pointer to queried V5AddressLayout instance if found, 0
        *         otherwise. Valid until that instance is erased.
        */
        const V5AddressLayout* lookup(DeviceID::ID_t deviceID) const;


    private:

        typedef std::map<DeviceID::ID_t, V5AddressLayout> IDMap_t;
        IDMap_t m_idMap;

    };

}

#endif
