/**
* \file PrimitiveSite.hpp
* \brief Contains declaration of PrimitiveSite class.
*/

#pragma once
#ifndef BIL_PRIMITIVESITE_HPP
#define BIL_PRIMITIVESITE_HPP

#include <string>
#include <vector>
#include <serialization/PrimitiveSiteBS.hpp>


namespace bil {

    /**
    * \brief A primitive site.
    *
    * The primitive site entity in XDLRC is broken up into two classes:
    * PrimitiveSite and PrimitiveSiteType. The PrimitiveSite stores data of a
    * distinct primitive site on a tile: its name and its bonded flag.
    */
    class PrimitiveSite {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new PrimitiveSite instance.
        */
        PrimitiveSite();


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
        /* BONDED/UNBONDED FLAG                                               */
        /**********************************************************************/

        /**
        * \brief Sets bonded/unbonded flag.
        * \param flag Flag denoting if this site connects out of the FPGA.
        */
        void isBonded(bool flag);

        /**
        * \brief Gets pin bonded/unbonded flag.
        * \return Flag denoting if this site connects out of the FPGA.
        */
        bool isBonded() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const PrimitiveSite& data, std::ostream& outputStream);
        friend void readBinary(PrimitiveSite& data, std::istream& inputStream);

        std::string m_name;
        bool m_bonded;

    };

    /// An ordered list of primitive sites.
    typedef std::vector<PrimitiveSite> PrimitiveSites;

}

#endif
