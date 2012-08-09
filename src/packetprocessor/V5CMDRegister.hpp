/**
* \file V5CMDRegister.hpp
* \brief Contains declaration of V5CMDRegister class.
*/

#pragma once
#ifndef BIL_V5CMDREGISTER_HPP
#define BIL_V5CMDREGISTER_HPP

#include <packetprocessor/Register.hpp>
#include <packetprocessor/V5CommandCode.hpp>


namespace bil {

    class V5CRCRegister;


    /**
    * \brief A register for executing commands.
    *
    * The command register is an one word write- and readable register. Writes
    * will set a command code and execute it. Reads will return the current
    * command code.
    */
    class V5CMDRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5CMDRegister instance.
        * \param crcReg V5CRCRegister instance reference that should be linked
        *               to this register (e.g. for being controlled).
        */
        explicit V5CMDRegister(V5CRCRegister& crcReg);


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief When writing a word, it will be set as current command code and
        *        executed immediately (by calling commandCode() and execute()).
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief When reading a word, the current command code will be returned.
        * \param words Pointer to data buffer.
        * \param wordCount Number of data words to read.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


        /**********************************************************************/
        /* COMMAND CODE INTERFACE                                             */
        /**********************************************************************/

        /**
        * \brief Sets command code.
        * \param code The new command code.
        * \throws .
        */
        void commandCode(V5CommandCode::command_t code);

        /**
        * \brief Gets current command code.
        * \return The command code.
        */
        V5CommandCode::command_t commandCode() const;

        /**
        * \brief Executes current command code.
        */
        void execute() const;


        /**********************************************************************/
        /* LINK TO OTHER REGISTERS                                            */
        /**********************************************************************/

        /**
        * \brief Gets linked V5CRCRegister register instance.
        * \return Reference to the V5CRCRegister instance.
        */
        V5CRCRegister& crcRegister() const;


    private:

        V5CMDRegister(const V5CMDRegister&);
        V5CMDRegister& operator=(const V5CMDRegister&);

        V5CommandCode::command_t m_command;
        V5CRCRegister& m_crcReg;

    };

}

#endif
