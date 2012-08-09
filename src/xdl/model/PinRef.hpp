/**
* \file PinRef.hpp
* \brief Contains declaration of PinRef class.
*/

#pragma once
#ifndef BIL_PINREF_HPP
#define BIL_PINREF_HPP

#include <cstring>
#include <vector>


namespace bil {

    /**
    * \brief References a pin on a distinct primitive site.
    *
    * In a XDL design this class is used to attach nets to the pins of primitive
    * sites. The primitive site is (implicitly) denoted by an index to an
    * Instance in the Design. The pin is denoted by an index to a Pin in the
    * corresponding PrimitiveType of a Device.
    */
    class PinRef {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PinRef instance.
        */
        PinRef();


        /**********************************************************************/
        /* INSTANCE INDEX                                                     */
        /**********************************************************************/

        /**
        * \brief Sets the Instance the pin is on.
        * \param index Index of Instance in superordinated Design.
        */
        void instanceIndex(size_t index);

        /**
        * \brief Gets the Instance the pin is on.
        * \return Index of Instance in superordinated Design.
        */
        size_t instanceIndex() const;


        /**********************************************************************/
        /* PIN INDEX                                                          */
        /**********************************************************************/

        /**
        * \brief Sets the target pin.
        * \param index Index of pin in corresponding PrimitiveType.
        */
        void pinIndex(size_t index);

        /**
        * \brief Gets the target pin.
        * \return Index of pin in corresponding PrimitiveType.
        */
        size_t pinIndex() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        size_t m_instanceIndex;
        size_t m_pinIndex;

    };


    /// An ordered list of PinRefs.
    typedef std::vector<PinRef> PinRefs;

}

#endif
