/**
* \file V5FrameAddress.hpp
* \brief Contains declaration of V5FrameAddress class.
*/

#pragma once
#ifndef BIL_V5FRAMEADDRESS_HPP
#define BIL_V5FRAMEADDRESS_HPP

#include <boost/cstdint.hpp>
#include <configuration/V5AddressLayout.hpp>
#include <configuration/V5CfgBlock.hpp>
#include <configuration/V5CfgColumn.hpp>


namespace bil {

    /**
    * \brief Models an address in Virtex-5 configuration memory.
    *
    * Virtex-5 device frame addresses are made up from five integer parts that
    * count upwards as frame address increases. Between the various Virtex-5
    * models these parts count up to different limits depending on the resources
    * this model has. The V5FrameAddress instances can be configured with a
    * pointer to a V5AddressLayout instance, which provides these model
    * specific limits and the address counting scheme.
    */
    class V5FrameAddress {
    public:

        /**********************************************************************/
        /* CONSTRUCTION / DESTRUCTION                                         */
        /**********************************************************************/

        /**
        * \brief Constructs a new V5FrameAddress instance.
        */
        V5FrameAddress();

        /**
        * \brief Constructs a new V5FrameAddress instance.
        * \param layout see addressLayout().
        */
        explicit V5FrameAddress(const V5AddressLayout* layout);


        /**********************************************************************/
        /* CONFIGURATION WITH ADDRESS LAYOUT                                  */
        /**********************************************************************/

        /**
        * \brief Sets address layout used by device dependent methods.
        * \details In order to hold the V5FrameAddress instances small, they do
        *          not contain a copy of the address layout for further use.
        *          Instead, they just hold a pointer to an external address
        *          layout instance. This pointer can also be 0 for all
        *          operations that do not require an address layout; operations
        *          which require an address layout will then throw an exception.
        * \param layout Pointer to address layout.
        */
        void addressLayout(const V5AddressLayout* layout);

        /**
        * \brief Gets address layout used by device dependent methods.
        * \return Pointer to the used address layout (can be 0).
        */
        const V5AddressLayout* addressLayout() const;


        /**********************************************************************/
        /* BLOCK                                                              */
        /**********************************************************************/

        /// Maximum allowed block value
        static const unsigned BLOCK_MAX = 7;

        /**
        * \brief Sets the block subspace the address points to.
        * \param block The block.
        * \throws .
        */
        void block(V5CfgBlock::block_t block);

        /**
        * \brief Gets the block subspace the address points to.
        * \return The block.
        */
        V5CfgBlock::block_t block() const;


        /**********************************************************************/
        /* LOWER/UPPER HALF                                                   */
        /**********************************************************************/

        /**
        * \brief Sets if address points to upper or lower half of the FPGA.
        * \param lower True, if address points to lower half; false otherwise.
        */
        void lowerHalf(bool lower);

        /**
        * \brief Gets if address points to upper or lower half of the FPGA.
        * \return True, if address points to lower half; false otherwise.
        */
        bool lowerHalf() const;


        /**********************************************************************/
        /* ROW INDEX                                                          */
        /**********************************************************************/

        /// Maximum allowed row index value
        static const unsigned ROWINDEX_MAX = V5AddressLayout::ROWCOUNT_MAX - 1;

        /**
        * \brief Sets index of the row the address points to.
        * \param ri The row index.
        * \throws .
        */
        void rowIndex(unsigned char ri);

        /**
        * \brief Gets index of the row the address points to.
        * \return The row index.
        */
        unsigned char rowIndex() const;


        /**********************************************************************/
        /* COLUMN INDEX                                                       */
        /**********************************************************************/

        /// Maximum allowed column index value
        static const unsigned COLUMNINDEX_MAX = V5AddressLayout::COLUMNCOUNT_MAX - 1;

        /**
        * \brief Sets index of the column the address points to.
        * \param ci The column index.
        * \throws .
        */
        void columnIndex(unsigned char ci);

        /**
        * \brief Gets index of the column the address points to.
        * \return The column index.
        */
        unsigned char columnIndex() const;


        /**********************************************************************/
        /* FRAME INDEX                                                        */
        /**********************************************************************/

        /// Maximum allowed frame index value
        static const unsigned FRAMEINDEX_MAX = 127;

        /**
        * \brief Sets index of the frame the address points to.
        * \param fi The frame index.
        * \throws .
        */
        void frameIndex(unsigned char fi);

        /**
        * \brief Gets index of the frame the address points to.
        * \return The frame index.
        */
        unsigned char frameIndex() const;


        /**********************************************************************/
        /* ADDRESS ITERATION                                                  */
        /**********************************************************************/

        /**
        * \brief Sets first address in address space.
        * \details The first address is the same for all devices, so an address
        *          layout need not to be set for this method to work.
        */
        void first();

        /**
        * \brief Sets last address in address space.
        * \details The last address is varies between the devices, so an address
        *          layout has to be set for this method to work.
        * \throws .
        */
        void last();

        /**
        * \brief Increments the address by one.
        * \details The address has to be valid.
        * \return True, if address is still valid after increment, false
        *         otherwise (this happens when last address is incremented).
        * \throws .
        */
        bool next();


        /**********************************************************************/
        /* VALIDITY                                                           */
        /**********************************************************************/

        /**
        * \brief Tells if address is valid under current address layout.
        * \details The address is valid only if addressLayout() is not 0, and
        *          all address parts are inside their valid ranges given by the
        *          address layout.
        * \return True, if address is valid, false otherwise.
        */
        bool isValid() const;


        /**********************************************************************/
        /* ADDRESS TARGET COLUMN TYPE                                         */
        /**********************************************************************/

        /**
        * \brief Tells the column type of the resource the address points to.
        * \return The column type of the targeted resource.
        * \throws .
        */
        V5CfgColumn::column_t columnType() const;


        /**********************************************************************/
        /* RAW ADDRESS                                                        */
        /**********************************************************************/

        /**
        * \brief Sets address from the raw 32 bit address representation.
        * \param ra Raw 32 bit address.
        */
        void rawAddress(boost::uint32_t ra);

        /**
        * \brief Gets the raw 32 bit address representation.
        * \return Raw 32 bit address.
        */
        boost::uint32_t rawAddress() const;


    private:

        friend bool operator== (const V5FrameAddress& fa1, const V5FrameAddress& fa2);
        friend bool operator< (const V5FrameAddress& fa1, const V5FrameAddress& fa2);


        const V5AddressLayout* m_addressLayout;

        V5CfgBlock::block_t m_block;
        bool m_lowerHalf;
        unsigned char m_rowIndex;
        unsigned char m_columnIndex;
        unsigned char m_frameIndex;

    };


    /// Tests two V5FrameAddress instances for memberwise equality
    inline bool operator== (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        if (fa1.m_block != fa2.m_block) return false;
        if (fa1.m_lowerHalf != fa2.m_lowerHalf) return false;
        if (fa1.m_rowIndex != fa2.m_rowIndex) return false;
        if (fa1.m_columnIndex != fa2.m_columnIndex) return false;
        return fa1.m_frameIndex == fa2.m_frameIndex;
    }

    /// Tests two V5FrameAddress instances for memberwise inequality
    inline bool operator!= (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        return !(operator== (fa1, fa2));
    }


    /// Tests two V5FrameAddress instances for memberwise <
    inline bool operator< (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        if (fa1.m_block != fa2.m_block) return fa1.m_block < fa2.m_block;
        if (fa1.m_lowerHalf != fa2.m_lowerHalf) return fa2.m_lowerHalf;
        if (fa1.m_rowIndex != fa2.m_rowIndex) return fa1.m_rowIndex < fa2.m_rowIndex;
        if (fa1.m_columnIndex != fa2.m_columnIndex) return fa1.m_columnIndex < fa2.m_columnIndex;
        return fa1.m_frameIndex < fa2.m_frameIndex;
    }

    /// Tests two V5FrameAddress instances for memberwise >
    inline bool operator> (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        return (operator< (fa2, fa1));
    }

    /// Tests two V5FrameAddress instances for memberwise <=
    inline bool operator<= (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        return !(operator> (fa1, fa2));
    }

    /// Tests two V5FrameAddress instances for memberwise >=
    inline bool operator>= (const V5FrameAddress& fa1, const V5FrameAddress& fa2)
    {
        return !(operator< (fa1, fa2));
    }

}

#endif
