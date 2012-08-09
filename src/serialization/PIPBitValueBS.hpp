/**
* \file PIPBitValueBS.hpp
* \brief Contains binary serialization functions for PIPBitValue class.
*/

#pragma once
#ifndef BIL_PIPBITVALUEBS_HPP
#define BIL_PIPBITVALUEBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class PIPBitValue;


    /**
    * \brief Writes data from a PIPBitValue into a binary stream.
    * \param data The PIPBitValue to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const PIPBitValue& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a PIPBitValue from a binary stream.
    * \param data The PIPBitValue to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(PIPBitValue& data, std::istream& inputStream);

}

#endif
