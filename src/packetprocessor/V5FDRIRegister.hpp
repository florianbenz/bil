/**
* \file V5FDRIRegister.hpp
* \brief Contains declaration of V5FDRIRegister class.
*/

#pragma once
#ifndef BIL_V5FDRIREGISTER_HPP
#define BIL_V5FDRIREGISTER_HPP

#include <packetprocessor/Register.hpp>
#include <configuration/V5Configuration.hpp>
#include <configuration/V5CfgFrame.hpp>


namespace bil {

    class V5CMDRegister;
    class V5FARRegister;


    /**
    * \brief A register for storing configuration data.
    *
    * The FDRI register is the input for configuration data. Because of this it
    * is a write-only register and writes to it must be a multiple of the frame
    * size. Every frame-sized data chunk will be packed into a frame and stored
    * in configuration memory at the frame address denoted by the FAR register.
    * After a frame is written, the FAR register is auto-incremented.
    */
    class V5FDRIRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5FDRIRegister instance.
        * \param cmdReg V5CMDRegister instance reference that should be linked
        *               to this register (e.g. for querying state).
        * \param farReg V5FARRegister instance reference that should be linked
        *               to this register (e.g. for querying frame address). The
        *               FAR register's frame address layout pointer will also be
        *               set V5Configuration member's address layout.
        */
        V5FDRIRegister(const V5CMDRegister& cmdReg, V5FARRegister& farReg);


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief Every frame-sized data chunk will be packed into a frame and
        *        stored in configuration memory at the frame address denoted by
        *        the FAR register. After a frame is written, the FAR register is
        *        auto-incremented.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);


        /**********************************************************************/
        /* MULTI-FRAME-WRITE INTERFACE                                        */
        /**********************************************************************/

        /**
        * \brief Writes the previous written frame again, but to the current
        *        FAR register's frame address.
        * \details This feature is used by the MFWRRegister for writing the same
        *          frame data to many different locations.
		* \throws .
        */
        void writePreviousFrame();


        /**********************************************************************/
        /* LINK TO OTHER REGISTERS                                            */
        /**********************************************************************/

        /**
        * \brief Gets linked V5CMDRegister register instance.
        * \return Reference to the V5CMDRegister instance.
        */
        const V5CMDRegister& cmdRegister() const;

        /**
        * \brief Gets linked V5FARRegister register instance.
        * \return Reference to the V5FARRegister instance.
        */
        V5FARRegister& farRegister() const;


        /**********************************************************************/
        /* CONFIGURATION INTERFACE                                            */
        /**********************************************************************/

        /**
        * \brief Gets configuration.
        * \return Reference to V5Configuration instance.
        */
        V5Configuration& configuration();

        /**
        * \brief Gets read only configuration.
        * \return Reference to V5Configuration instance.
        */
        const V5Configuration& configuration() const;


    private:

        V5FDRIRegister(const V5FDRIRegister&);
        V5FDRIRegister& operator=(const V5FDRIRegister&);

        V5Configuration m_configuration;
        const V5CMDRegister& m_cmdReg;
        V5FARRegister& m_farReg;
        V5CfgFrame m_previousFrame;

    };

}

#endif
