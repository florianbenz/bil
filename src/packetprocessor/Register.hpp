/**
* \file Register.hpp
* \brief Contains declaration of Register class.
*/

#pragma once
#ifndef BIL_REGISTER_HPP
#define BIL_REGISTER_HPP

#include <cstring>
#include <string>
#include <boost/cstdint.hpp>
#include <bitstream/RegisterAddress.hpp>


namespace bil {

    /**
    * \brief Abstract base class for packet processor's registers.
    *
    * Each register has an address, a name, and could be written and/or read.
    * Derived specialized registers perform some register specific actions on
    * reads/writes, and accept only specific data.
    */
    class Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a Register instance.
        * \details Once created, name, address, writable, and readable can not
        *          be changed.
        * \param address Address of the register.
        * \param name Name of the register (gets copied).
        * \param writable Writable flag.
        * \param readable Readable flag.
        */
        Register(RegisterAddress::address_t address, const std::string& name, bool writable = true, bool readable = true);

        /**
        * \brief Destructs a Register instance.
        */
        virtual ~Register() = 0;


        /**********************************************************************/
        /* REGISTER PROPERTIES                                                */
        /**********************************************************************/

        /**
        * \brief Gets register address.
        * \return The register address.
        */
        RegisterAddress::address_t address() const;

        /**
        * \brief Gets register name.
        * \return A const reference to the register name.
        */
        const std::string& name() const;

        /**
        * \brief Tells if register is writable.
        * \return True if register is writable, false otherwise.
        */
        bool writable() const;

        /**
        * \brief Tells if register is readable.
        * \return True if register is readable, false otherwise.
        */
        bool readable() const;


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief Writes data words into the register.
        * \details Note that different Register subclasses may accept different
        *          data (e.g. only a specific number of words or some special
        *          values), and even the same register instance may accept
        *          different data over the time dependent on its internal state.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief Reads data words from the register.
        * \details Note that different Register subclasses may accept different
        *          read sizes, and even the same register instance may accept
        *          different read sizes over the time dependent on its internal
        *          state.
        * \param words Pointer to data buffer.
        * \param wordCount Number of data words to read into buffer.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


    private:

        Register(const Register&);
        Register& operator=(const Register&);

        const std::string m_name;
        const RegisterAddress::address_t m_address;
        const bool m_writable;
        const bool m_readable;

    };

}

#endif
