/**
* \file V5FARRegister.hpp
* \brief Contains declaration of V5FARRegister class.
*/

#pragma once
#ifndef BIL_V5FARREGISTER_HPP
#define BIL_V5FARREGISTER_HPP

#include <packetprocessor/Register.hpp>
#include <configuration/V5FrameAddress.hpp>


namespace bil {

    /**
    * \brief A register holding a frame address.
    *
    * The FAR register is an one word write- and readable register containing a
    * frame address. Writes will alter its frame address to point to a new
    * target. Reads will return the current frame address.
    */
    class V5FARRegister: public Register {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5FARRegister instance.
        */
        V5FARRegister();


        /**********************************************************************/
        /* REGISTER I/O                                                       */
        /**********************************************************************/

        /**
        * \brief When writing a word, it sets the current frame address.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        virtual void write(const boost::uint32_t* words, size_t wordCount);

        /**
        * \brief When reading a word, the current frame address is returned.
        * \param words Pointer to data buffer.
        * \param wordCount Number of data words to read.
        * \throws .
        */
        virtual void read(boost::uint32_t* words, size_t wordCount) const;


        /**********************************************************************/
        /* FRAME ADDRESS INTERFACE                                            */
        /**********************************************************************/

        /**
        * \brief Gets frame address.
        * \return Reference to FARRegister's V5FrameAddress instance.
        */
        V5FrameAddress& frameAddress();

        /**
        * \brief Gets read only frame address.
        * \return Reference to FARRegister's V5FrameAddress instance.
        */
        const V5FrameAddress& frameAddress() const;


    private:

        V5FARRegister(const V5FARRegister&);
        V5FARRegister& operator=(const V5FARRegister&);

        V5FrameAddress m_frameAddress;

    };

}

#endif
