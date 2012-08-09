/**
* \file Net.hpp
* \brief Contains declaration of Net class.
*/

#pragma once
#ifndef BIL_NET_HPP
#define BIL_NET_HPP

#include <string>
#include <xdl/model/NetType.hpp>
#include <xdl/model/PinRef.hpp>
#include <xdl/model/PIPRef.hpp>


namespace bil {

    /**
    * \brief Defines a XDL net.
    *
    * A net has got a name, a type, and lists of used pins and PIPs.
    */
    class Net {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Net instance.
        */
        Net();


        /**********************************************************************/
        /* NAME                                                               */
        /**********************************************************************/

        /**
        * \brief Gets name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* NET TYPE                                                           */
        /**********************************************************************/

        /**
        * \brief Sets type.
        * \param type The new type.
        */
        void type(NetType::net_t type);

        /**
        * \brief Gets type.
        * \return The type.
        */
        NetType::net_t type() const;


        /**********************************************************************/
        /* ATTATCHED PINS                                                     */
        /**********************************************************************/

        /**
        * \brief Gets pins the net is attached to.
        * \return The pin references.
        */
        PinRefs& pinRefs();

        /**
        * \brief Gets pins the net is attached to read only.
        * \return The pin references.
        */
        const PinRefs& pinRefs() const;


        /**********************************************************************/
        /* PIPS IN THE NET                                                    */
        /**********************************************************************/

        /**
        * \brief Gets PIPs the net crosses.
        * \return The PIP references.
        */
        PIPRefs& pipRefs();

        /**
        * \brief Gets PIPs the net crosses read only.
        * \return The PIP references.
        */
        const PIPRefs& pipRefs() const;


        /**********************************************************************/
        /* ATTRIBUTE STRING                                                   */
        /**********************************************************************/

        /**
        * \brief Gets attribute string.
        * \return The attribute string.
        */
        std::string& attributes();

        /**
        * \brief Gets attribute string read only.
        * \return The attribute string.
        */
        const std::string& attributes() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        std::string m_name;
        std::string m_attributes;
        PinRefs m_pinRefs;
        PIPRefs m_pipRefs;
        NetType::net_t m_type;

    };


    /// An ordered list of Nets.
    typedef std::vector<Net> Nets;

}

#endif
