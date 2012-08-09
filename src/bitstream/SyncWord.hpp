/**
* \file SyncWord.hpp
* \brief Contains declaration of SyncWord class.
*/

#pragma once
#ifndef BIL_SYNCWORD_HPP
#define BIL_SYNCWORD_HPP

#include <bitstream/Packet.hpp>


namespace bil {

    /**
    * \brief A special synchronization word.
    *
    * Bitstreams normally contain a synchronization word in order to mark the
    * beginning of the packet stream.
    */
    class SyncWord: public Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual SyncWord* clone() const;


        /**********************************************************************/
        /* VISITOR INTERFACE                                                  */
        /**********************************************************************/

        /**
        * \brief Accepts a visitor for dynamic type dependent stuff.
        * \param visitor Visitor, which matching method will be called.
        */
        virtual void accept(PacketVisitor& visitor) const;

    };

}

#endif
