/**
* \file PrimitiveTypeBS.hpp
* \brief Contains binary serialization functions for PrimitiveType class.
*/

#pragma once
#ifndef BIL_PRIMITIVETYPEBS_HPP
#define BIL_PRIMITIVETYPEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PrimitiveType;


    /**
    * \brief Writes data from a PrimitiveType into a binary stream.
    * \param data The PrimitiveType to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PrimitiveType& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PrimitiveType from a binary stream.
    * \param data The PrimitiveType to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PrimitiveType& data, std::istream& inputStream);

}

#endif
