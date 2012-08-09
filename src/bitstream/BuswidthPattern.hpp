/**
* \file BuswidthPattern.hpp
* \brief Contains declaration of BuswidthPattern class.
*/

#pragma once
#ifndef BIL_BUSWIDTHPATTERN_HPP
#define BIL_BUSWIDTHPATTERN_HPP

#include <bitstream/Packet.hpp>


namespace bil {

    /**
    * \brief A special pattern for buswidth detection.
    *
    * Some bitstreams contain a buswidth pattern somewhere at the start, in
    * order to tell the FPGA which buswidth is used for configuration. Depending
    * on the used buswidth, the configuration logic sees another part of the
    * pattern at a time, thereby determining the buswidth.
    */
    class BuswidthPattern: public Packet {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Virtual constructor for doing polymorphic copies.
        * \return Pointer to the copied instance.
        */
        virtual BuswidthPattern* clone() const;


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
