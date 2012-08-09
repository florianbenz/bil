/**
* \file V5Configuration.hpp
* \brief Contains declaration of V5Configuration class.
*/

#pragma once
#ifndef BIL_V5CONFIGURATION_HPP
#define BIL_V5CONFIGURATION_HPP

#include <map>
#include <utility>
#include <vector>
#include <configuration/V5AddressLayout.hpp>
#include <configuration/V5CfgFrame.hpp>
#include <configuration/V5FrameAddress.hpp>


namespace bil {

    /**
    * \brief Configuration of a Virtex-5 device.
    *
    * Holds the configuration memory contents (complete or only a part) of a
    * Virtex-5 device by storing pairs consisting of a frame address and its
    * associated frame. Theses pairs are sorted by their frame address, and can
    * be quickly looked up by them.
    */
    class V5Configuration {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5Configuration instance.
        */
        V5Configuration();

        /**
        * \brief Constructs a new V5Configuration instance.
        * \param layout See addressLayout().
        */
        explicit V5Configuration(const V5AddressLayout& layout);

        /**
        * \brief Copy constructs a new V5Configuration instance.
        * \param src Reference to V5Configuration instance from which to copy.
        */
        V5Configuration(const V5Configuration& src);


        /**********************************************************************/
        /* ASSIGNMENT                                                         */
        /**********************************************************************/

        /**
        * \brief Assigns a V5Configuration instance to another.
        * \param src Reference to V5Configuration instance from which to copy.
        * \returns Reference to instance that has been assigned to.
        */
        V5Configuration& operator=(const V5Configuration& src);


        /**********************************************************************/
        /* ADDRESS LAYOUT CONFIGURATION                                       */
        /**********************************************************************/

        /**
        * \brief Sets address layout used for the frame addresses.
        * \details The given layout is copied and all subsequently inserted
        *          addresses will be linked to it. If the container is not
        *          empty, it will be cleared. Setting an equivalent layout (in
        *          terms of operator==) will do nothing.
        * \param layout New address layout.
        */
        void addressLayout(const V5AddressLayout& layout);

        /**
        * \brief Gets address layout used for the frame addresses.
        * \return A reference to currently used address layout.
        */
        const V5AddressLayout& addressLayout() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Inserts a frame address/frame pair. If there is already another
        *        frame address/frame pair with same address, it gets replaced by
        *        the new pair.
        * \details Before address gets inserted, it is copied and linked to the
        *          current address layout, under that it must be valid.
        * \param address Frame address to insert at.
        * \param frame V5CfgFrame instance that will be copied.
        * \return True, if given address was not occupied, false otherwise.
        * \throws .
        */
        bool insert(const V5FrameAddress& address, const V5CfgFrame& frame);

        /**
        * \brief Erases a frame address/frame pair.
        * \param address Frame address of pair to erase.
        * \return True, if designated frame address/frame pair existed; false
        *         otherwise.
        */
        bool erase(const V5FrameAddress& address);

        /**
        * \brief Erases all frame address/frame pairs.
        */
        void clear();


        /**********************************************************************/
        /* CONTENT ITERATION                                                  */
        /**********************************************************************/

        /**
        * \brief Gets count of contained frame address/frame pairs.
        * \return Number of contained pairs.
        */
        size_t size() const;

        /// type for contained frame address/frame pairs
        typedef std::pair<const V5FrameAddress, V5CfgFrame> pair_t;

        /// type for pointers to frame address/frame pairs
        typedef std::vector<pair_t*> pairptrs_t;

        /// type for const pointers to frame address/frame pairs
        typedef std::vector<const pair_t*> pairconstptrs_t;

        /**
        * \brief Gets references to all frame address/frame pairs.
        * \return Vector filled with references to pairs. Each reference is
        *         valid until referenced instance is not erased.
        * \throws .
        */
        pairptrs_t contents();

        /**
        * \brief Gets references to all frame address/frame pairs read only.
        * \return Vector filled with read only references to pairs. Each
        *         reference is valid until referenced instance is not erased.
        * \throws .
        */
        pairconstptrs_t contents() const;


        /**********************************************************************/
        /* FRAME LOOKUP                                                       */
        /**********************************************************************/

        /**
        * \brief Looks up a frame by address.
        * \param address Address of frame to query.
        * \return Pointer to the queried frame if found, 0 otherwise. Valid
        *         until that frame is erased or replaced.
        */
        V5CfgFrame* lookup(const V5FrameAddress& address);

        /**
        * \brief Looks up a read only frame by address.
        * \param address Address of frame to query.
        * \return Pointer to the queried frame if found, 0 otherwise. Valid
        *         until that frame is erased or replaced.
        */
        const V5CfgFrame* lookup(const V5FrameAddress& address) const;


    private:

        V5AddressLayout m_addressLayout;

        typedef std::map<V5FrameAddress, V5CfgFrame> container_t;
        container_t m_configuration;

    };

}

#endif
