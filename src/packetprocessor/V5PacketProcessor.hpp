/**
* \file V5PacketProcessor.hpp
* \brief Contains declaration of V5PacketProcessor class.
*/

#pragma once
#ifndef BIL_V5PACKETPROCESSOR_HPP
#define BIL_V5PACKETPROCESSOR_HPP

#include <bitstream/V5BitstreamSyntaxChecker.hpp>
#include <configuration/V5Configuration.hpp>
#include <packetprocessor/RegisterLookup.hpp>
#include <packetprocessor/WordRegister.hpp>
#include <packetprocessor/V5CMDRegister.hpp>
#include <packetprocessor/V5CRCRegister.hpp>
#include <packetprocessor/V5FARRegister.hpp>
#include <packetprocessor/V5FDRIRegister.hpp>
#include <packetprocessor/V5IDCODERegister.hpp>
#include <packetprocessor/V5MFWRRegister.hpp>


namespace bil {

    class V5AddressLayoutRegistry;


    /**
    * \brief Executes bitstreams in order to get their configuration data.
    *
    * The packet processor is essentially a register machine, that is capable of
    * executing the bitstream packets containing opcode, register address, and
    * data. The outcome of this execution is the raw configuration data, which
    * describe the configuration memory contents.
    */
    class V5PacketProcessor: public V5BitstreamSyntaxChecker {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a V5PacketProcessor instance.
        * \param registry V5AddressLayoutRegistry instance reference to be used
        *                 for looking up the device specific address layout.
        */
        explicit V5PacketProcessor(const V5AddressLayoutRegistry& registry);


        /**********************************************************************/
        /* PACKET VISITOR INTERFACE                                           */
        /**********************************************************************/

        /**
        * \brief Visits a DummyWord packet.
        * \param dummyWord DummyWord instance to be visited.
        * \throws .
        */
        virtual void visit(const DummyWord& dummyWord);

        /**
        * \brief Visits a Type1Packet packet.
        * \param type1Packet Type1Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type1Packet& type1Packet);

        /**
        * \brief Visits a Type2Packet packet.
        * \param type2Packet Type2Packet instance to be visited.
        * \throws .
        */
        virtual void visit(const Type2Packet& type2Packet);


        /**
        * \brief Resets the packet processor.
        * \details Resets packet processor's internal bitstream syntax checker,
        *          so that is then ready for a new bitstream. Also clears the
        *          current configuration.
        */
        virtual void reset();


        /**********************************************************************/
        /* LINKED ADDRESS LAYOUT REGISTRY                                     */
        /**********************************************************************/

        /**
        * \brief Gets the linked address layout registry.
        * \return Read only reference to V5AddressLayoutRegistry instance used
        *         by the packet processor for getting the configuration memory
        *         layout of the target device.
        */
        const V5AddressLayoutRegistry& addressLayoutRegistry() const;


        /**********************************************************************/
        /* CONFIGURATION MEMORY INTERFACE                                     */
        /**********************************************************************/

        /**
        * \brief Gets the configuration.
        * \return Reference to packet processor's V5Configuration instance.
        */
        V5Configuration& configuration();

        /**
        * \brief Gets the configuration read only.
        * \return Read only reference to packet processor's V5Configuration
        *         instance.
        */
        const V5Configuration& configuration() const;


    protected:

        /**
        * \brief Visits a data packet.
        * \param type2Packet Reference to data packet to be processed.
        * \throws .
        */
        void visitDataPacket(const Type2Packet& type2Packet);

        /**
        * \brief Writes data to a register.
        * \param regAddr Target register address.
        * \param words Pointer to data words to write.
        * \param wordCount Number of data words to write.
        * \throws .
        */
        void registerWrite(RegisterAddress::address_t regAddr, const boost::uint32_t* words, size_t wordCount);


    private:

        V5PacketProcessor(const V5PacketProcessor&);
        V5PacketProcessor& operator=(const V5PacketProcessor&);


        const V5AddressLayoutRegistry& m_addressLayoutRegistry;

        RegisterLookup m_registerLookup;

        V5CRCRegister m_crcReg;
        V5FARRegister m_farReg;
        V5CMDRegister m_cmdReg;
        V5FDRIRegister m_fdriReg;
        V5MFWRRegister m_mfwrReg;
        V5IDCODERegister m_idcodeReg;

        WordRegister m_fdroReg;
        WordRegister m_ctl0Reg;
        WordRegister m_maskReg;
        WordRegister m_statReg;
        WordRegister m_loutReg;
        WordRegister m_cor0Reg;
        WordRegister m_cbcReg;
        WordRegister m_axssReg;
        WordRegister m_cor1Reg;
        WordRegister m_csobReg;
        WordRegister m_wbstarReg;
        WordRegister m_timerReg;
        WordRegister m_reg19Reg;
        WordRegister m_bootstsReg;
        WordRegister m_ctl1Reg;

    };

}

#endif
