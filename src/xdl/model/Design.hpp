/**
* \file Design.hpp
* \brief Contains declaration of Design class.
*/

#pragma once
#ifndef BIL_DESIGN_HPP
#define BIL_DESIGN_HPP

#include <xdl/model/Instance.hpp>
#include <xdl/model/Net.hpp>


namespace bil {

    /**
    * \brief Models a XDL design.
    *
    * A XDL design consists basically of its instances and its nets. Instances
    * represent used primitive sites, and are connected by nets. Nets are
    * denoted by their constituting PIPs and are attached to the primitive
    * sites/instances by pins.
    */
    class Design {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Design instance.
        */
        Design();


        /**********************************************************************/
        /* DESIGN NAME                                                        */
        /**********************************************************************/

        /**
        * \brief Gets design name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets design name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* TARGET DEVICE NAME                                                 */
        /**********************************************************************/

        /**
        * \brief Gets device name.
        * \return The name.
        */
        std::string& deviceName();

        /**
        * \brief Gets device name read only.
        * \return The name.
        */
        const std::string& deviceName() const;


        /**********************************************************************/
        /* NCD VERSION STRING                                                 */
        /**********************************************************************/

        /**
        * \brief Gets NCD version string.
        * \return The string.
        */
        std::string& ncdVersion();

        /**
        * \brief Gets NCD version string read only.
        * \return The string.
        */
        const std::string& ncdVersion() const;


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
        /* INSTANCES                                                          */
        /**********************************************************************/

        /**
        * \brief Gets instances.
        * \return The instances.
        */
        Instances& instances();

        /**
        * \brief Gets instances read only.
        * \return The instances.
        */
        const Instances& instances() const;


        /**********************************************************************/
        /* NETS                                                               */
        /**********************************************************************/

        /**
        * \brief Gets the nets.
        * \return The nets.
        */
        Nets& nets();

        /**
        * \brief Gets the nets read only.
        * \return The nets.
        */
        const Nets& nets() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        std::string m_name;
        std::string m_deviceName;
        std::string m_ncdVersion;
        std::string m_attributes;
        Instances m_instances;
        Nets m_nets;

    };

}

#endif
