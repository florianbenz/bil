/**
* \file TileTypeCfgDb.hpp
* \brief Contains declaration of TileTypeCfgDb class.
*/

#pragma once
#ifndef BIL_TILETYPECFGDB_HPP
#define BIL_TILETYPECFGDB_HPP

#include <cstring>
#include <mappingdb/PIPControlSet.hpp>
#include <serialization/TileTypeCfgDbBS.hpp>


namespace bil {

    /**
    * \brief Holds configuration bit mapping of a tile type.
    *
    * Todo: At the moment there are only control sets for the PIPs. Control
	* sets for the primitive sites should be added.
    */
    class TileTypeCfgDb {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new TileTypeCfgDb instance.
        */
        TileTypeCfgDb();


        /**********************************************************************/
        /* TILE TYPE INDEX                                                    */
        /**********************************************************************/

        /**
        * \brief Sets tile type index.
        * \param index Index of TileType in corresponding Device.
        */
        void typeIndex(size_t index);

        /**
        * \brief Gets tile type index.
        * \return Index of TileType in corresponding Device.
        */
        size_t typeIndex() const;


        /**********************************************************************/
        /* PIP CONTROL SETS                                                   */
        /**********************************************************************/

        /**
        * \brief Gets PIP control sets.
        * \return The PIP control sets.
        */
        PIPControlSets& pipControlSets();

        /**
        * \brief Gets PIP control sets read only.
        * \return The PIP control sets.
        */
        const PIPControlSets& pipControlSets() const;


        /**********************************************************************/
        /* MODIFICATORS                                                       */
        /**********************************************************************/

        /**
        * \brief Resets all properties to default values.
        */
        void clear();


    private:

        friend void writeBinary(const TileTypeCfgDb& data, std::ostream& outputStream);
        friend void readBinary(TileTypeCfgDb& data, std::istream& inputStream);

        PIPControlSets m_pipControlSets;
        size_t m_tileTypeIndex;

    };


    /// A list of TileTypeCfgDb instances
    typedef std::vector<TileTypeCfgDb> TileTypeCfgDbs;

}

#endif
