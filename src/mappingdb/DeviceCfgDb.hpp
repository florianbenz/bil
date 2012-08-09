/**
* \file DeviceCfgDb.hpp
* \brief Contains declaration of DeviceCfgDb class.
*/

#pragma once
#ifndef BIL_DEVICECFGDB_HPP
#define BIL_DEVICECFGDB_HPP

#include <mappingdb/TileTypeCfgDb.hpp>
#include <mappingdb/DeviceCfgDb.hpp>


namespace bil {

    /**
    * \brief Holds a device's configuration bit mapping.
    *
    * This database contains one entry for every TileType of the corresponding
    * Device, holding its mapping information.
    */
    class DeviceCfgDb {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new DeviceCfgDb instance.
        */
        DeviceCfgDb();


        /**********************************************************************/
        /* TILE TYPE DATA BASES                                               */
        /**********************************************************************/

        /**
        * \brief Gets tile type databases.
        * \return The tile type databases.
        */
        TileTypeCfgDbs& tileTypeDbs();

        /**
        * \brief Gets tile type databases read only.
        * \return The tile type databases.
        */
        const TileTypeCfgDbs& tileTypeDbs() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const DeviceCfgDb& data, std::ostream& outputStream);
        friend void readBinary(DeviceCfgDb& data, std::istream& inputStream);

        TileTypeCfgDbs m_tileTypeDbs;

    };

}

#endif
