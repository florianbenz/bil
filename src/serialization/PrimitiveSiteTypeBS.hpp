/**
* \file PrimitiveSiteTypeBS.hpp
* \brief Contains binary serialization functions for PrimitiveSiteType class.
*/

#pragma once
#ifndef BIL_PRIMITIVESITETYPEBS_HPP
#define BIL_PRIMITIVESITETYPEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PrimitiveSiteType;


    /**
    * \brief Writes data from a PrimitiveSiteType into a binary stream.
    * \param data The PrimitiveSiteType to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PrimitiveSiteType& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PrimitiveSiteType from a binary stream.
    * \param data The PrimitiveSiteType to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PrimitiveSiteType& data, std::istream& inputStream);

}

#endif
