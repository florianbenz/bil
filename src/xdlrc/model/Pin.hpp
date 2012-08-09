/**
* \file Pin.hpp
* \brief Contains declaration of Pin class.
*/

#pragma once
#ifndef BIL_PIN_HPP
#define BIL_PIN_HPP

#include <string>
#include <vector>
#include <serialization/PinBS.hpp>


namespace bil {

    /**
    * \brief A pin of a primitive.
    *
    * The interface of a primitive is made up by pins connecting the primitive
    * to the outside. Each pin has got an unique name inside its primitive, and
    * is input or output only.
    */
    class Pin {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Pin instance.
        */
        Pin();


        /**********************************************************************/
        /* NAME                                                               */
        /**********************************************************************/

        /**
        * \brief Gets external name.
        * \return The name.
        */
        std::string& externalName();

        /**
        * \brief Gets external name read only.
        * \return The name.
        */
        const std::string& externalName() const;


        /**********************************************************************/
        /* INPUT/OUTPUT FLAG                                                  */
        /**********************************************************************/

        /**
        * \brief Sets input/output flag.
        * \param flag Flag denoting if this is an input pin.
        */
        void isInput(bool flag);

        /**
        * \brief Gets pin input/output flag.
        * \return Flag denoting if this is an input pin.
        */
        bool isInput() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const Pin& data, std::ostream& outputStream);
        friend void readBinary(Pin& data, std::istream& inputStream);

        std::string m_externalName;
        bool m_isInput;

    };

    /// An ordered list of pins.
    typedef std::vector<Pin> Pins;

}

#endif
