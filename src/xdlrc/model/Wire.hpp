/**
* \file Wire.hpp
* \brief Contains declaration of Wire class.
*/

#pragma once
#ifndef BIL_WIRE_HPP
#define BIL_WIRE_HPP

#include <string>
#include <serialization/WireBS.hpp>
#include <xdlrc/model/WireConnection.hpp>


namespace bil {

    /**
    * \brief Describes a wire.
    *
    * A wire is located on a tile. It has got a name, and a list of connections
    * (to other wires on the same or on other tiles).
    */
    class Wire {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Wire instance.
        */
        Wire();


        /**********************************************************************/
        /* WIRE NAME                                                          */
        /**********************************************************************/

        /**
        * \brief Gets wire name.
        * \return The name.
        */
        std::string& name();

        /**
        * \brief Gets wire name read only.
        * \return The name.
        */
        const std::string& name() const;


        /**********************************************************************/
        /* WIRE CONNECTIONS                                                   */
        /**********************************************************************/

        /**
        * \brief Gets connections to other wires.
        * \return The connections.
        */
        WireConnections& connections();

        /**
        * \brief Gets connections to other wires read only.
        * \return The connections.
        */
        const WireConnections& connections() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const Wire& data, std::ostream& outputStream);
        friend void readBinary(Wire& data, std::istream& inputStream);

        std::string m_name;
        WireConnections m_connections;

    };

    /// An ordered list of wires.
    typedef std::vector<Wire> Wires;

}

#endif
