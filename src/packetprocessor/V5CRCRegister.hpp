/**
* \file V5CRCRegister.hpp
* \brief Contains declaration of V5CRCRegister class.
*/

#pragma once
#ifndef BIL_V5CRCREGISTER_HPP
#define BIL_V5CRCREGISTER_HPP

#include <packetprocessor/Register.hpp>


namespace bil {

    /**
    * \brief A register for doing cyclic redundancy checks.
    *
    * The CRC register is an one word write- and readable register. Writes will
    * trigger a check of its register value. Reads will return the current CRC
    * value. The actual updating of the CRC values must be done from outside per
    * update().
    */
    class V5CRCRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5CRCRegister instance.
        */
        V5CRCRegister();


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief When writing a word, a CRC check will be issued (by calling
        *        check()).
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief When reading a word, the current CRC value will be returned.
        * \param words Pointer to data buffer.
        * \param wordCount Number of data words to read.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


        /**********************************************************************/
        /* CRC INTERFACE                                                      */
        /**********************************************************************/

        /**
        * \brief Gets the current CRC value.
        * \return The CRC value.
        */
        boost::uint32_t crcValue() const;

        /**
        * \brief Resets the CRC register value to 0.
        */
        void reset();

        /**
        * \brief Updates the CRC value based on given data and register address.
        * \param words Pointer to data words.
        * \param wordCount Number of data words.
        * \param registerAddress Target register of data words.
        */
        void update(const boost::uint32_t* words, size_t wordCount, RegisterAddress::address_t registerAddress);

        /**
        * \brief Checks if CRC was successful, i.e. CRC value is 0 again.
        * \throws .
        */
        void check() const;


    private:

        V5CRCRegister(const V5CRCRegister&);
        V5CRCRegister& operator=(const V5CRCRegister&);

        boost::uint32_t m_crcValue;

    };

}

#endif
