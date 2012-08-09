/**
* \file V5BitstreamDeviceDetector.hpp
* \brief Contains declaration of V5BitstreamDeviceDetector class.
*/

#pragma once
#ifndef BIL_V5BITSTREAMDEVICEDETECTOR_HPP
#define BIL_V5BITSTREAMDEVICEDETECTOR_HPP

#include <deviceinfo/DeviceID.hpp>
#include <bitstream/V5BitstreamSyntaxChecker.hpp>


namespace bil {

    class Bitstream;


    /**
    * \brief Visitor for determining target device type of a Virtex-5 bitstream.
    *
    * This visitor is derived from V5BitstreamSyntaxChecker, because when
    * visiting a bitstream and trying to detect its target device type this
    * bitstream has to be at least syntactical correct. The detection itself
    * relies on the presence of a write into the IDCODE register, which tells
    * the ID of the device the bitstream is for. If multiple IDCODE writes are
    * present, thats no problem, unless they all write the same device ID;
    * otherwise an exception will be thrown.
    */
    class V5BitstreamDeviceDetector: public V5BitstreamSyntaxChecker {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        V5BitstreamDeviceDetector();


        /**********************************************************************/
        /* DETECTION STATE                                                    */
        /**********************************************************************/

        /**
        * \brief Gets the detected device ID.
        * \details This method will return 0, if reset() was called directly
        *          before; or if no IDCODE command was found in the visited
        *          bitstream.
        * \return The device ID.
        */
        DeviceID::ID_t deviceID() const;

        /**
        * \brief Resets the syntax checker and the device ID.
        */
        virtual void reset();


        /**********************************************************************/
        /* VISITING METHODS                                                   */
        /**********************************************************************/

        /**
        * \brief Checks a Type1Packet packet for device ID data.
        * \param type1Packet Type1Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type1Packet& type1Packet);

        /**
        * \brief Checks a Type2Packet packet for device ID data.
        * \param type2Packet Type2Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type2Packet& type2Packet);


    protected:

        /**
        * \brief Tests if packet contains a device ID. If so, the ID is tested
        *        against previous written IDs (if there are previous writes,
        *        all IDs must be equal) and stored.
        * \details If the packet is a one word write to the IDCODE register,
        *          this word is the device ID.
        * \param type2Packet The packet.
        * \throws .
        */
        void checkDeviceID(const Type2Packet& type2Packet);


    private:

        DeviceID::ID_t m_id;

    };

    /**
    * \brief Detects target device type of a Virtex-5 bitstream.
    * \details Convenience functions for using V5BitstreamDeviceDetector.
    * \throws .
    */
    DeviceID::ID_t detectV5DeviceType(Bitstream& bitstream);

}

#endif
