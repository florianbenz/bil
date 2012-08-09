/**
* \file Element.hpp
* \brief Contains declaration of Element class.
*/

#pragma once
#ifndef BIL_ELEMENT_HPP
#define BIL_ELEMENT_HPP

#include <string>
#include <vector>
#include <serialization/ElementBS.hpp>


namespace bil {

    /// An ordered list of configuration options.
    typedef std::vector<std::string> ConfigurationOptions;


    /**
    * \brief An element of a primitive.
    *
    * Elements are configurable subunits of primitives. Each element has got an
    * unique name inside its primitive and a list of configuration options. Each
    * single option denotes a distinct configuration of the whole element.
    */
    class Element {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Element instance.
        */
        Element();


        /**********************************************************************/
        /* ELEMENT NAME                                                       */
        /**********************************************************************/

        /**
        * \brief Gets element name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets element name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* CONFIGURATION OPTIONS                                              */
        /**********************************************************************/

        /**
        * \brief Gets configuration options.
        * \return The configuration options.
        */
        ConfigurationOptions& options();

        /**
        * \brief Gets configuration options read only.
        * \return The configuration options.
        */
        const ConfigurationOptions& options() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const Element& data, std::ostream& outputStream);
        friend void readBinary(Element& data, std::istream& inputStream);

        std::string m_name;
        ConfigurationOptions m_options;

    };

    /// An ordered list of elements.
    typedef std::vector<Element> Elements;

}

#endif
