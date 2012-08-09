/**
* \file NameSplit.hpp
* \brief Splitting of XDL(RC) names into parts.
*/

#pragma once
#ifndef BIL_NAMESPLIT_HPP
#define BIL_NAMESPLIT_HPP


namespace bil {

    /**
    * \brief Extracts the X and Y coordinate from a XDL(RC) name.
    * \details Some XDL(RC) entities have got names like T_X#Y# (where T stands
    *          for a typename and # for a positive integer number).
    * \param name Name to extract from.
    * \param x Resulting X coordinate.
    * \param y Resulting Y coordinate.
    * \return True, if coordinates were successfully extracted; false otherwise.
    */
    bool extractPosition(const char* name, unsigned& x, unsigned& y);

}

#endif
