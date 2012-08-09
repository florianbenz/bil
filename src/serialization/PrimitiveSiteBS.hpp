/**
* \file PrimitiveSiteBS.hpp
* \brief Contains binary serialization functions for PrimitiveSite class.
*/

#pragma once
#ifndef BIL_PRIMITIVESITEBS_HPP
#define BIL_PRIMITIVESITEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PrimitiveSite;


    /**
    * \brief Writes data from a PrimitiveSite into a binary stream.
    * \param data The PrimitiveSite to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PrimitiveSite& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PrimitiveSite from a binary stream.
    * \param data The PrimitiveSite to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PrimitiveSite& data, std::istream& inputStream);

}

#endif
