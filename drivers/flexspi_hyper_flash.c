/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_flexspi.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "board.h"
#include "clock_config.h"
#include "fsl_common.h"
#include "flexspi_hyper_flash.h"

/*******************************************************************************
* Prototypes
******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
flexspi_device_config_t deviceconfig = {
    .flexspiRootClk = 42000000, /* 42MHZ SPI serial clock */
    .isSck2Enabled = false,
    .flashSize = FLASH_SIZE,
    .CSIntervalUnit = kFLEXSPI_CsIntervalUnit1SckCycle,
    .CSInterval = 2,
    .CSHoldTime = 3,
    .CSSetupTime = 3,
    .dataValidTime = 1,
    .columnspace = 3,
    .enableWordAddress = true,
    .AWRSeqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA,
    .AWRSeqNumber = 1,
    .ARDSeqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA,
    .ARDSeqNumber = 1,
    .AHBWriteWaitUnit = kFLEXSPI_AhbWriteWaitUnit2AhbCycle,
    .AHBWriteWaitInterval = 20,
};

const uint32_t customLUT[CUSTOM_LUT_LENGTH] = {
		 /* Read Data */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04),

		/* Write Data */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x20, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x02),
		/* Read Status */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 2] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 3] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x70), // DATA 0x70
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 4] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 5] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_DUMMY_RWDS_DDR, kFLEXSPI_8PAD, 0x0B),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS + 6] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_READ_DDR, kFLEXSPI_8PAD, 0x04, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x0),

		/* Write Enable */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 2] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 3] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // DATA 0xAA
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 4] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 5] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 6] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x02),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE + 7] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),

		/* Erase Sector  */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 2] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 3] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x80), // DATA 0x80
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 4] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 5] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 6] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 7] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 8] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 9] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 10] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x02),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 11] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x55),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 12] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 13] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR + 14] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x30, kFLEXSPI_Command_STOP, kFLEXSPI_1PAD, 0x00),

		/* program page */
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 1] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xAA), // ADDR 0x555
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 2] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x05),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 3] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0xA0), // DATA 0xA0
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 4] =
			FLEXSPI_LUT_SEQ(kFLEXSPI_Command_DDR, kFLEXSPI_8PAD, 0x00, kFLEXSPI_Command_RADDR_DDR, kFLEXSPI_8PAD, 0x18),
		[4 * HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM + 5] = FLEXSPI_LUT_SEQ(
			kFLEXSPI_Command_CADDR_DDR, kFLEXSPI_8PAD, 0x10, kFLEXSPI_Command_WRITE_DDR, kFLEXSPI_8PAD, 0x80),
};


__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_hyperbus_read(FLEXSPI_Type *base, uint32_t addr, uint32_t *buffer, uint32_t bytes)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    flashXfer.deviceAddress = addr * 2;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Read;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA;
    flashXfer.data = buffer;
    flashXfer.dataSize = bytes;
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_hyperbus_write(FLEXSPI_Type *base, uint32_t addr, uint32_t *buffer, uint32_t bytes)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    flashXfer.deviceAddress = addr * 2;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Write;
    flashXfer.SeqNumber = 1;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA;
    flashXfer.data = buffer;
    flashXfer.dataSize = bytes;
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_write_enable(FLEXSPI_Type *base, uint32_t baseAddr)
{
    flexspi_transfer_t flashXfer;
    status_t status;

    /* Write neable */
    flashXfer.deviceAddress = baseAddr;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Command;
    flashXfer.SeqNumber = 2;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE;

    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_wait_bus_busy(FLEXSPI_Type *base)
{
    /* Wait status ready. */
    bool isBusy;
    uint32_t readValue;
    status_t status;
    flexspi_transfer_t flashXfer;

    flashXfer.deviceAddress = 0;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Read;
    flashXfer.SeqNumber = 2;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS;
    flashXfer.data = &readValue;
    flashXfer.dataSize = 2;

    do
    {
        status = FLEXSPI_TransferBlocking(base, &flashXfer);

        if (status != kStatus_Success)
        {
            return status;
        }
        if (readValue & 0x8000)
        {
            isBusy = false;
        }
        else
        {
            isBusy = true;
        }

        if (readValue & 0x3200)
        {
            status = kStatus_Fail;
            break;
        }

    } while (isBusy);

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address)
{
	status_t status;
	flexspi_transfer_t flashXfer;

    status = flexspi_nor_write_enable(base, address);

    if (status != kStatus_Success)
    {
        return status;
    }

    flashXfer.deviceAddress = address;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Command;
    flashXfer.SeqNumber = 4;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR;
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t address, const uint32_t *src)
{
    status_t status;
    flexspi_transfer_t flashXfer;

    /* Write neable */
    status = flexspi_nor_write_enable(base, address);

    if (status != kStatus_Success)
    {
        return status;
    }

    /* Prepare page program command */
    flashXfer.deviceAddress = address;
    flashXfer.port = kFLEXSPI_PortA1;
    flashXfer.cmdType = kFLEXSPI_Write;
    flashXfer.SeqNumber = 2;
    flashXfer.seqIndex = HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM;
    flashXfer.data = (uint32_t *)src;
    flashXfer.dataSize = FLASH_PAGE_SIZE;
    status = FLEXSPI_TransferBlocking(base, &flashXfer);

    if (status != kStatus_Success)
    {
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    return status;
}

__attribute__((section(".data.$SRAM_DTC")))
static void print_cfi_info(uint32_t *cfibuffer)
{
	int i;
	for(i=0; i<0x20; i++)
	{
		PRINTF("CFI[0x%02X]: %08X\n", i*4, cfibuffer[i]);
	}

}
__attribute__((section(".data.$SRAM_DTC")))
status_t flexspi_nor_hyperflash_cfi(FLEXSPI_Type *base)
{
    /*
     * Read ID-CFI Parameters
     */
    // CFI Entry
    status_t status;
    uint32_t buffer[2];
    uint32_t cfibuffer[32];
    uint32_t data = 0x9800;
    int i;
    status = flexspi_nor_hyperbus_write(base, 0x555, &data, 2);
    if (status != kStatus_Success)
    {
        return status;
    }

    //PRINTF("Entering the ASO mode\r\n");
    // ID-CFI Read
    // Read Query Unique ASCII String

    status = flexspi_nor_hyperbus_read(base, 0x10, &buffer[0], sizeof(buffer));
	if (status != kStatus_Success)
	{
		return status;
	}

    buffer[1] &= 0xFFFF;
    // Check that the data read out is  unicode "QRY" in big-endian order
    if ((buffer[0] != 0x52005100) || (buffer[1] != 0x5900))
    {
        status = kStatus_Fail;
        //PRINTF("Can not found the HyperFlash!\r\n");
        return status;
    }

    for(i=0;i<0x20;i++)
    {
    	status = flexspi_nor_hyperbus_read(base, i*2, &cfibuffer[i], 4);
    	if (status != kStatus_Success)
    	{
    		return status;
    	}
    }

    // ASO Exit
    data = 0xF000;
    status = flexspi_nor_hyperbus_write(base, 0x0, &data, 2);
    if (status != kStatus_Success)
    {
        //PRINTF("Can not exit the ASO\r\n");
        return status;
    }

    status = flexspi_nor_wait_bus_busy(base);

    PRINTF("Found the HyperFlash by CFI\r\n");
    print_cfi_info(cfibuffer);

    return status;
}
