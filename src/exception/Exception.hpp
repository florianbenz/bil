/**
* \file Exception.hpp
* \brief Contains declaration of Exception class.
*/

#pragma once
#ifndef BIL_EXCEPTION_HPP
#define BIL_EXCEPTION_HPP

#include <stdexcept>
#include <string>


namespace bil {

    /**
    * \brief Base exception class.
    *
    * Base exception class used in bil.
    */
    class Exception: public std::runtime_error {
    public:

        /**
        * \brief Creates a new Exception instance.
        */
        Exception() throw();

        /**
        * \brief Creates a new Exception instance.
        * \param what_arg Description string.
        */
        explicit Exception(const std::string& what_arg) throw();

    };

}

#endif
