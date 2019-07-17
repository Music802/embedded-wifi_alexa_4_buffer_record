/*******************************************************************************
* Definitions
******************************************************************************/
#define EXAMPLE_FLEXSPI FLEXSPI
//#define FLASH_SIZE 0x4000000
#define FLASH_SIZE 0x2000000
#define EXAMPLE_FLEXSPI_AMBA_BASE FlexSPI_AMBA_BASE
#define FLASH_PAGE_SIZE 512
#define EXAMPLE_SECTOR 2
#define SECTOR_SIZE 0x40000
#define EXAMPLE_FLEXSPI_CLOCK kCLOCK_FlexSpi
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READDATA 0
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEDATA 1
#define HYPERFLASH_CMD_LUT_SEQ_IDX_READSTATUS 2
#define HYPERFLASH_CMD_LUT_SEQ_IDX_WRITEENABLE 4
#define HYPERFLASH_CMD_LUT_SEQ_IDX_ERASESECTOR 6
#define HYPERFLASH_CMD_LUT_SEQ_IDX_PAGEPROGRAM 10
#define CUSTOM_LUT_LENGTH 60

extern const uint32_t customLUT[CUSTOM_LUT_LENGTH];
