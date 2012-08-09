/**
* \file ElementBS.hpp
* \brief Contains binary serialization functions for Element class.
*/

#pragma once
#ifndef BIL_ELEMENTBS_HPP
#define BIL_ELEMENTBS_HPP

#include <istream>
#include <ostream>


namespace bil {

    class Element;


    /**
    * \brief Writes data from a Element into a binary stream.
    * \param data The Element to write.
    * \param outputStream The stream to write into.
    * \throws .
    */
    void writeBinary(const Element& data, std::ostream& outputStream);

    /**
    * \brief Reads data into a Element from a binary stream.
    * \param data The Element to read into.
    * \param inputStream The stream to read from.
    * \throws .
    */
    void readBinary(Element& data, std::istream& inputStream);

}

#endif
