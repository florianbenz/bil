/**
* \file WordRegister.hpp
* \brief Contains declaration of WordRegister class.
*/

#pragma once
#ifndef BIL_WORDREGISTER_HPP
#define BIL_WORDREGISTER_HPP

#include <packetprocessor/Register.hpp>


namespace bil {

    /**
    * \brief A standard register containing a 32 bit word.
    *
    * This class models a 32 bit word register. One word can be written or read
    * at a time.
    */
    class WordRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a WordRegister instance.
        * \details See Register().
        */
        WordRegister(RegisterAddress::address_t address, const std::string& name, bool writable = true, bool readable = true);


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief Writes a data word into the register.
        * \param words Pointer to data words to write.
        * \param wordCount Must be 1.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief Reads a data word from the register.
        * \param words Pointer to data buffer.
        * \param wordCount Must be 1.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


        /**********************************************************************/
        /* REGISTER VALUE                                                     */
        /**********************************************************************/

        /**
        * \brief Sets the register's current value.
        * \param val The 32 bit word value.
        */
        void value(boost::uint32_t val);

        /**
        * \brief Gets the register's current value.
        * \return The 32 bit word value.
        */
        boost::uint32_t value() const;


    private:

        WordRegister(const Register&);
        WordRegister& operator=(const Register&);

        boost::uint32_t m_value;

    };

}

#endif
