/**
* \file Instance.hpp
* \brief Contains declaration of Instance class.
*/

#pragma once
#ifndef BIL_INSTANCE_HPP
#define BIL_INSTANCE_HPP

#include <cstring>
#include <string>
#include <vector>


namespace bil {

    /**
    * \brief Defines a XDL instance.
    *
    * A XDL Instance has got an unique name, a primitive type (meaning that this
    * instance can only be placed on primitive sites of that type), and a flag
    * telling if it is already placed or not. If it is placed, two indices tell
    * on which tile and which primitive site. It has also got an attribute
    * string.
    */
    class Instance {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new Instance instance.
        */
        Instance();


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
        /* PRIMITIVE TYPE INDEX                                               */
        /**********************************************************************/

        /**
        * \brief Sets primitive type of this Instance.
        * \param index Index of a PrimitiveType in a Device.
        */
        void primitiveTypeIndex(size_t index);

        /**
        * \brief Gets primitive type of this Instance.
        * \return Index of a PrimitiveType in a Device.
        */
        size_t primitiveTypeIndex() const;


        /**********************************************************************/
        /* PLACEMENT FLAG                                                     */
        /**********************************************************************/

        /**
        * \brief Sets placement flag.
        * \param placed Flag telling if this Instance is placed or not.
        */
        void placed(bool placed);

        /**
        * \brief Gets placement flag.
        * \return Flag telling if this Instance is placed or not.
        */
        bool placed() const;


        /**********************************************************************/
        /* BONDED FLAG                                                        */
        /**********************************************************************/

        /**
        * \brief Sets bonded flag.
        * \param bonded Flag telling if this Instance is bonded out or not, when
        *               it is not placed.
        */
        void bonded(bool bonded);

        /**
        * \brief Gets bonded flag.
        * \return Flag telling if this Instance is bonded or not, when it is not
        *         placed.
        */
        bool bonded() const;


        /**********************************************************************/
        /* TILE INDEX                                                         */
        /**********************************************************************/

        /**
        * \brief Sets tile this Instance is placed on (if it is).
        * \param index Index of a Tile in a Device.
        */
        void tileIndex(size_t index);

        /**
        * \brief Gets tile this Instance is placed on (if it is).
        * \return Index of a Tile in a Device.
        */
        size_t tileIndex() const;


        /**********************************************************************/
        /* PRIMITIVE SITE INDEX                                               */
        /**********************************************************************/

        /**
        * \brief Sets primitive site this Instance is placed on (if it is).
        * \param index Index of PrimitiveSite on current Tile.
        */
        void primitiveSiteIndex(size_t index);

        /**
        * \brief Gets primitive site this Instance is placed on (if it is).
        * \return Index of PrimitiveSite on current Tile.
        */
        size_t primitiveSiteIndex() const;


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
        size_t m_tileIndex;
        size_t m_primitiveTypeIndex;
        size_t m_primitiveSiteIndex;
        bool m_placed;
        bool m_bonded;

    };


    /// An ordered list of Instance.
    typedef std::vector<Instance> Instances;

}

#endif
