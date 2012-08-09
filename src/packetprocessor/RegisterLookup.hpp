/**
* \file RegisterLookup.hpp
* \brief Contains declaration of RegisterLookup class.
*/

#pragma once
#ifndef BIL_REGISTERLOOKUP_HPP
#define BIL_REGISTERLOOKUP_HPP

#include <vector>
#include <bitstream/RegisterAddress.hpp>


namespace bil {

    class Register;


    /**
    * \brief A lookup table for registers.
    *
    * The RegisterLookup class stores references to Register instances and
    * allows quick looking up of them by their address.
    */
    class RegisterLookup {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Creates a new RegisterLookup instance.
        * \param highestAddress Highest address the lookup table should have a
        *                       slot for.
        */
        RegisterLookup(RegisterAddress::address_t highestAddress);


        /**********************************************************************/
        /* ADDING AND REMOVING OF REGISTER REFERENCES                         */
        /**********************************************************************/

        /**
        * \brief Adds a register reference into lookup table.
        * \param reg The register to add.
        * \throws .
        */
        void add(Register& reg);

        /**
        * \brief Removes register reference for given address.
        * \param registerAddress Address of slot to empty.
        * \return True, if slot was emptied; false otherwise (e.g. because slot
                  was already empty before or does not exist).
        */
        bool remove(RegisterAddress::address_t registerAddress);


        /**********************************************************************/
        /* REGISTER REFERENCE LOOKUP                                          */
        /**********************************************************************/

        /**
        * \brief Looks up a register by address.
        * \param registerAddress The address of register to get.
        * \return If found, a pointer to the register; 0 otherwise.
        */
        Register* lookup(RegisterAddress::address_t registerAddress) const;


    private:

        std::vector<Register*> m_registers;

    };

}

#endif
