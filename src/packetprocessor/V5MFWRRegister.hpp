/**
* \file V5MFWRRegister.hpp
* \brief Contains declaration of V5MFWRRegister class.
*/

#pragma once
#ifndef BIL_V5MFWRREGISTER_HPP
#define BIL_V5MFWRREGISTER_HPP

#include <packetprocessor/Register.hpp>


namespace bil {

    class V5CMDRegister;
    class V5FDRIRegister;


    /**
    * \brief %Register for use with bitstream compression.
    *
    * The MFWR register is a write-only register. Writes of at least two dummy
    * words to it cause the FDRI register to write the previous written frame
    * again to the current frame address in FAR.
    */
    class V5MFWRRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5FDRIRegister instance.
        * \param cmdReg V5CMDRegister instance reference that should be linked
        *               to this register (e.g. for querying state).
        * \param fdriReg V5FDRIRegister instance reference that should be linked
        *                to this register (e.g. for triggering frame writes).
        */
        V5MFWRRegister(const V5CMDRegister& cmdReg, V5FDRIRegister& fdriReg);


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief Writes cause the FDRI register to write the previous written
        *        frame again to the current frame address in FAR.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);


        /**********************************************************************/
        /* LINK TO OTHER REGISTERS                                            */
        /**********************************************************************/

        /**
        * \brief Gets linked V5CMDRegister register instance.
        * \return Reference to the V5CMDRegister instance.
        */
        const V5CMDRegister& cmdRegister() const;

        /**
        * \brief Gets linked V5FDRIRegister register instance.
        * \return Reference to the V5FDRIRegister instance.
        */
        V5FDRIRegister& fdriRegister() const;


    private:

        V5MFWRRegister(const V5MFWRRegister&);
        V5MFWRRegister& operator=(const V5MFWRRegister&);

        const V5CMDRegister& m_cmdReg;
        V5FDRIRegister& m_fdriReg;

    };

}

#endif
