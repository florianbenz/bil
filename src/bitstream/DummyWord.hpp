/**
* \file DummyWord.hpp
* \brief Contains declaration of DummyWord class.
*/

#pragma once
#ifndef BIL_DUMMYWORD_HPP
#define BIL_DUMMYWORD_HPP

#include <boost/cstdint.hpp>
#include <bitstream/Packet.hpp>


namespace bil {

    /**
    * \brief A word of dummy data.
    *
    * Sometimes it is necessary to insert dummy data into a bitstream; for
    * this purpose serves the DummyWord class. It contains one 32 bit word for
    * holding its dummy value.
    */
    class DummyWord: public Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Default constructor.
        */
        DummyWord();

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual DummyWord* clone() const;


        /**********************************************************************/
        /* VISITOR INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Accepts a visitor for dynamic type dependent stuff.
        * \param visitor Visitor, which matching method will be called.
        */
        virtual void accept(PacketVisitor& visitor) const;


        /**********************************************************************/
        /* PACKET CONTENT                                                     */
        /**********************************************************************/

        /// a frequent dummy data value
        static const boost::uint32_t NULL_WORD = 0x00000000;

        /// a frequent dummy data value
        static const boost::uint32_t FULL_WORD = 0xffffffff;

        /**
        * \brief Sets the dummy value.
        * \param dummyValue The 32 bit word dummy value.
        */
        void value(boost::uint32_t dummyValue);

        /**
        * \brief Gets the dummy value.
        * \return The 32 bit dummy value.
        */
        boost::uint32_t value() const;


    private:

        boost::uint32_t m_value;

    };

}

#endif
