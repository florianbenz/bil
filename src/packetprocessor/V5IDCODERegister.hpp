/**
* \file V5IDCODERegister.hpp
* \brief Contains declaration of V5IDCODERegister class.
*/

#pragma once
#ifndef BIL_V5IDCODEREGISTER_HPP
#define BIL_V5IDCODEREGISTER_HPP

#include <deviceinfo/DeviceID.hpp>
#include <packetprocessor/Register.hpp>


namespace bil {

    class V5FDRIRegister;
    class V5AddressLayoutRegistry;


    /**
    * \brief A register for setting/checking the target device type.
    *
    * The IDCODE register is an one word write- and readable register. It
    * contains the device ID code of the device to be configured. Writes will
    * set this ID code (and prepare the FDRI register for that device); reads
    * will return the current ID code.
    */
    class V5IDCODERegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5IDCODERegister instance.
        * \param fdriReg Reference to a V5FDRIRegister instance that should be
        *                linked to this register (e.g. for doing target device
        *                related setup of FDRI).
        * \param registry Reference to a V5AddressLayoutRegistry instance that
        *                 should be linked to this register (e.g. for looking up
        *                 address layouts based on the device ID).
        */
        V5IDCODERegister(V5FDRIRegister& fdriReg, const V5AddressLayoutRegistry& registry);


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief When writing a word, it will be set as current ID code by
        *        calling deviceID().
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief When reading a word, the current ID code will be returned.
        * \param words Pointer to data buffer.
        * \param wordCount Number of data words to read.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


        /**********************************************************************/
        /* ID CODE INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Sets device ID code, looks up the corresponding address layout
        *        in the address layout registry, and copies it to FDRI register.
        * \param id The new ID code.
        * \throws .
        */
        void idCode(DeviceID::ID_t id);

        /**
        * \brief Gets current device ID code.
        * \return The ID code.
        */
        DeviceID::ID_t idCode() const;


        /**********************************************************************/
        /* LINK TO OTHER REGISTERS                                            */
        /**********************************************************************/

        /**
        * \brief Gets linked V5FDRIRegister instance.
        * \return Reference to the V5FDRIRegister instance.
        */
        V5FDRIRegister& fdriRegister() const;


        /**********************************************************************/
        /* LINK TO ADDRESS LAYOUT REGISTRY                                    */
        /**********************************************************************/

        /**
        * \brief Gets linked V5AddressLayoutRegistry instance.
        * \return Reference to the V5AddressLayoutRegistry instance.
        */
        const V5AddressLayoutRegistry& layoutRegistry() const;


    private:

        V5IDCODERegister(const V5IDCODERegister&);
        V5IDCODERegister& operator=(const V5IDCODERegister&);

        DeviceID::ID_t m_idCode;
        V5FDRIRegister& m_fdriRegister;
        const V5AddressLayoutRegistry& m_addressLayoutRegistry;

    };

}

#endif
