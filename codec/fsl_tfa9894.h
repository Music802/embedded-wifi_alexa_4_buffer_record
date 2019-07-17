/*
 * fsl_tfa9894.h
 *
 *  Created on: Apr 25, 2018
 *      Author: krg00719
 */

#ifndef FSL_TFA9894_H_
#define FSL_TFA9894_H_

#include "fsl_common.h"
#include "fsl_lpi2c.h"
#include "fsl_codec_common.h"

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_codec_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define TFA98XX_PRINT_DEBUG

#ifdef TFA98XX_PRINT_DEBUG
//#define TFA98xx_Printf DbgConsole_Printf
#define TFA98xx_Printf printf
#else
#define TFA98xx_Printf(format, args...) ((void)0)
#endif
//#define FACTORY_CALIBRATION_ONLY /* Set Calibrate Once in the factory */
#define TFA98XX_BROWNOUT_DETECT_SUPPORT
#define TFA_MAX_VSTEP_MSG_MARKER 100
#define SB_PARAM_SET_ALGO_PARAMS        0x00
#define SB_PARAM_SET_LAGW               0x01
#define SB_PARAM_SET_ALGO_PARAMS_WITHOUT_RESET	0x02
#define SB_PARAM_SET_LSMODEL            0x06
#define SB_PARAM_SET_MBDRC              0x07
#define SB_PARAM_SET_MBDRC_WITHOUT_RESET	0x08
#define SB_PARAM_SET_DRC                0x0F
#define FAM_TFA98XX_CF_MEM      (TFA9894_BF_MEMA>>8)
#define FAM_TFA98XX_CF_CONTROLS (TFA9894_BF_RST >> 8)

#define TFA2_FW_ReZ_SCALE   65536
#define TFA2_BF_ACK   		0x9387
#define TFA98XX_WAITRESULT_NTRIES  40
#define TFA98XX_I2C_MAX_SIZE 254
#define MAX_I2C_LENGTH		TFA98XX_I2C_MAX_SIZE
#define ROUND_DOWN(a,n) (((a)/(n))*(n))
#define TFA98XX_API_WAITRESULT_NTRIES        3000
/* RPC Status results */
#define STATUS_OK                  0
#define STATUS_INVALID_MODULE_ID   2
#define STATUS_INVALID_PARAM_ID    3
#define STATUS_INVALID_INFO_ID     4
/* module Ids */
#define FW_PAR_ID_SET_SENSES_DELAY      0x04
#define MODULE_FRAMEWORK        0
#define MODULE_SPEAKERBOOST     1
#define MODULE_BIQUADFILTERBANK 2
#define SB_PARAM_GET_STATE        0xC0
#define FW_PARAM_GET_STATE        0x84
/* RPC commands */
#define SB_PARAM_GET_RE0          0x85
#define SB_PARAM_SET_LSMODEL      0x06  /* Load a full model into SpeakerBoost. */
#define SB_PARAM_SET_EQ			  0x0A  /* 2 Equaliser Filters. */
#define SB_PARAM_SET_CONFIG		  0x0E  /* Load a config */
#define SB_PARAM_SET_AGCINS       0x10
#define PARAM_GET_LSMODEL         0x86  /* Gets current LoudSpeaker impedance Model.*/
#define PARAM_GET_LSMODELW        0xC1  /* Gets current LoudSpeaker xcursion Model.*/

#define FW_STATE_SIZE 9
#define FW_STATE_MAX_SIZE FW_STATE_SIZE
#define SPKRBST_HEADROOM			7					  /* Headroom applied to the main input signal */
#define SPKRBST_AGCGAIN_EXP			SPKRBST_HEADROOM	  /* Exponent used for AGC Gain related variables */
#define SPKRBST_TEMPERATURE_EXP     9
#define SPKRBST_LIMGAIN_EXP			4			          /* Exponent used for Gain Corection related variables */
#define SPKRBST_TIMECTE_EXP         1
#ifndef MIN
#define MIN(A,B)(A<B?A:B)
#endif

/* Data structure */
typedef struct _tfa98xx_registers 
{
	uint16_t reg;
    uint16_t val;
} tfa98xx_Registers_t;

#define OPTIMIZED_RPC
typedef int int24;
typedef struct uint24M 
{
  uint8_t b[3];
}uint24M_t;

enum _tfa98xx_error 
{
	kStatus_TFA98XX_Ok = MAKE_STATUS(kStatusGroup_Generic, 0),
	kStatus_TFA98XX_DSP_not_running = MAKE_STATUS(
		kStatusGroup_Generic, 1),  /* communication with the DSP failed, presumably because DSP not running */
	kStatus_TFA98XX_Bad_Parameter = MAKE_STATUS(kStatusGroup_Generic, 2),
	kStatus_TFA98XX_NotOpen = MAKE_STATUS(kStatusGroup_Generic, 3),  		/* the given handle is not open */
	kStatus_TFA98XX_OutOfHandles = MAKE_STATUS(kStatusGroup_Generic, 4),     /* too many handles */
	kStatus_TFA98XX_StateTimedOut = 
		MAKE_STATUS(kStatusGroup_Generic, 5),	/* the expected response did not occur within the expected time */

	kStatus_TFA98XX_RpcBase = MAKE_STATUS(kStatusGroup_Generic, 100),
	kStatus_TFA98XX_RpcBusy = MAKE_STATUS(kStatusGroup_Generic, 101),
	kStatus_TFA98XX_RpcModId = MAKE_STATUS(kStatusGroup_Generic, 102),
	kStatus_TFA98XX_RpcParamId = MAKE_STATUS(kStatusGroup_Generic, 103),
	kStatus_TFA98XX_RpcInfoId = MAKE_STATUS(kStatusGroup_Generic, 104),
	kStatus_TFA98XX_RpcNotAllowedSpeaker = MAKE_STATUS(kStatusGroup_Generic, 105),

	kStatus_TFA98XX_Not_Implemented = MAKE_STATUS(kStatusGroup_Generic, 106),
	kStatus_TFA98XX_Not_Supported = MAKE_STATUS(kStatusGroup_Generic, 107),
	kStatus_TFA98XX_I2C_Fatal = MAKE_STATUS(kStatusGroup_Generic, 108),        /* Fatal I2C error occurred */
    kStatus_TFA98XX_I2C_NonFatal =
        MAKE_STATUS(kStatusGroup_Generic, 109), /* Nonfatal I2C error, and retry count reached */
	kStatus_TFA98XX_Other = MAKE_STATUS(kStatusGroup_Generic, 1000)
} ;

typedef enum _tfa98xx_DMEM
{
	DMEM_PMEM=0,
	DMEM_XMEM=1,
	DMEM_YMEM=2,
	DMEM_IOMEM=3,
} tfa98xx_DMEM_t;

typedef enum _tfa9891_mute
{
	Mute_Off,
	Mute_Digital,
	Mute_Amplifier
} tfa9891_mute_t;

#pragma pack(push, 1)
/*!
 * @brief VSTEP header
 */
typedef struct _tfa98xx_tfaheader
{
	uint16_t id;
    char version[2];     /* "V_" : V=version, vv=subversion */
    char subversion[2];  /* "vv" : vv=subversion */
    uint16_t size;       /* data size in bytes following CRC */
    uint32_t CRC;        /* 32-bits CRC for following data */
    char customer[8];    /* "name of customer" */
    char application[8]; /* "application name" */
    char type[8];		 /* "application type name" */
} tfa98xx_tfaheader_t;

/*!
 * @brief Bitfield in container file
 */
typedef struct _tfa98xx_BfEnum
{
	uint32_t  len:4;		/* this is the actual length-1 */
	uint32_t  pos:4;
	uint32_t  address:8;
} tfa98xx_BfEnum_t;

/*!
 * @brief volumestepMax2 file
 */
typedef struct _tfa98xx_volumeStepMax2File
{
	tfa98xx_tfaheader_t hdr;
	uint8_t version[3];
	uint8_t NrOfVsteps;
	uint8_t vstepsBin[];
} tfa98xx_volumeStepMax2File_t;

/*!
 * @brief volumestepMax2 file for bin2hdr conversion
 * This volumestep should ONLY be used for the use of bin2hdr
 * This can only be used to find the messagetype of the vstep (without header)
 */
typedef struct _tfa98xx_volumeStepMax2_1File
{
	uint8_t version[3];
	uint8_t NrOfVsteps;
	uint8_t vstepsBin[];
} tfa98xx_volumeStepMax2_1File_t;

/*!
 * @brief Register settings in container file
 */
struct _tfa98xx_volumeStepRegisterInfo
{
	uint8_t NrOfRegisters;
	uint16_t registerInfo[];
};

/*!
 * @brief Messages in container file
 */
struct _tfa98xx_volumeStepMessageInfo
{
	uint8_t NrOfMessages;
	uint8_t MessageType;
	uint24M_t MessageLength;
	uint8_t CmdId[3];
	uint8_t ParameterData[];
};

/*!
 * @brief Bitfield in container file
 */
typedef struct _tfa98xx_Bitfield
{
	uint16_t  value;
	uint16_t  field; /* ==datasheet defined, 16 bits */
} tfa98xx_Bitfield_t;
#pragma pack(pop)

/*! @brief Channels in stereo. TFA_LEFT only in mono */
enum _tfa98xx_Channel
{
	TFA_LEFT = 0,
	TFA_RIGHT = 1
};

/*! @brief Power up and down */
enum _tfa98xx_PowerUpDown
{
	TFA_POWERUP = 0,
	TFA_POWERDOWN = 1
};

/*! @brief Number of TFA devices requires for channel. */
enum _tfa98xx_Devices
{
	TFA_MONO = 1,
	TFA_STEREO = 2
};

/*! @brief Device manager status. */
enum _tfa98xx_ManState
{
	TFA_STATUS_POWER_DOWN = 0,
	TFA_STATUS_WAIT_FOR_SOURCE_SETTING = 1,
	TFA_STATUS_ENABLE_PLL = 4,
	TFA_STATUS_ENABLE_CGU = 5,
	TFA_STATUS_INIT_COOLFLUX = 6,
	TFA_STATUS_ENABLE_AMPLIFIER = 7,
	TFA_STATUS_ALARM = 8,
	TFA_STATUS_OPERATING = 9,
	TFA_STATUS_MUTE_AUDIO = 10,
	TFA_STATUS_DISABLE_CGU_PLL = 11
};

/*! @brief TFA9894 configure definition. */
typedef struct _tfa98xx_handle tfa98xx_handle_t;

/*! @brief TFA9894 codec operations. */
typedef struct _tfa98xx_operation
{
    status_t (*Init)(tfa98xx_handle_t *handle, codec_config_t *config); /* AMP init operation */
    status_t (*SetFormat)(tfa98xx_handle_t *handle,
                          uint32_t mclk,
                          uint32_t sampleRate,
                          uint32_t bitWidth); /*!< AMP format setting */
    status_t (*SetVolume)(tfa98xx_handle_t *handle, uint8_t volume_level); /* AMP volume setting */
    status_t (*Deinit)(tfa98xx_handle_t *handle);
} tfa98xx_operation_t;

/*! @brief TFA9894 codec handle. */
struct _tfa98xx_handle
{
#if defined(FSL_FEATURE_SOC_LPI2C_COUNT) && (FSL_FEATURE_SOC_LPI2C_COUNT)
    LPI2C_Type *base;
#else
    /* I2C relevant definition. */
    I2C_Type *base;                 /*!< I2C instance. */
#endif
    /* Pointer to the user-defined I2C Send Data function. */
    codec_i2c_send_func_t I2C_SendFunc;
    /* Pointer to the user-defined I2C Receive Data function. */
    codec_i2c_receive_func_t I2C_ReceiveFunc;
    /* The I2C slave address . */
    uint8_t slaveAddress;
    tfa98xx_operation_t op;
};


/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Set I2S format.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_SetFormat(tfa98xx_handle_t *handle, uint32_t mclk, uint32_t sampleRate, uint32_t bitWidth);

/*!
 * @brief Set amplifier volume.
 * Example volume table
 * Volume level index and corresponding VOL value(dec) from TFA9894 register 0x51
 * Vol_lvl	0	1	2	3	4	5	6	7	8	9	10	11	12	13	14 (Maximum attenuation)
 * Vol_val	0	1	2	4	6	10	16	24	30	40	50	60	80	100	255 (Soft mute)
 *
 * @param handle TFA98xx codec handle.
 * @param volume_atten Amplifier volume attenuation index 0..255 volume_atten*-0.5dB. 255 is soft mute and 0 is max volume.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_SetVolume(tfa98xx_handle_t *handle, uint8_t volume_level);

/*!
 * @brief Initialize TFA9894.
 *
 * @param handle TFA98xx codec handle.
 * @param config Codec configuration.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_Init(tfa98xx_handle_t *handle, codec_config_t *config);

/*!
 * @brief DeInitilize TFA9894.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_DeInit(tfa98xx_handle_t *handle);

/*!
 * @brief Read TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param value value read from I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ReadRegister(tfa98xx_handle_t *handle, uint8_t subaddress,uint16_t * value);

/*!
 * @brief Get Bitfield of TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @return Bitfield value read from I2C register.
 */
uint16_t TFA98XX_ReadBitf(tfa98xx_handle_t *handle, const uint16_t bf);

/*!
 * @brief Read Bitfield from value. No I2C transaction triggered by function call.
 *
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param reg_value Register value already read from I2C register
 * @return Bitfield value.
 */
uint16_t TFA98XX_ReadBitfValue(const uint16_t bf, const uint16_t reg_value);

/*!
 * @brief Read chunck of data from I2C register address.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param num_bytes number of bytes to read
 * @param data data array to store data chunk after read
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ReadData(tfa98xx_handle_t *handle, uint8_t subaddress, int num_bytes, uint8_t data[]);

/*!
 * @brief Write value to TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteRegister(tfa98xx_handle_t *handle, uint8_t subaddress, uint16_t value);

/*!
 * @brief Write bitfield to TFA98XX I2C register. No I2C transaction if old value is the same with new value.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteBitf(tfa98xx_handle_t *handle, const uint16_t bf, const uint16_t value);

/*!
 * @brief Write bitfield to TFA98XX I2C register.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteBitfVolitale(tfa98xx_handle_t *handle, const uint16_t bf, const uint16_t value);

/*!
 * @brief Set Bitfield from value. No I2C transaction triggered by function call.
 *
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param reg_value Register value already read from I2C register
 * @return Bitfield value.
 */
void TFA98XX_WriteBitfValue(const uint16_t bf, const uint16_t bf_value, uint16_t *p_reg_value);

/*!
 * @brief Write chunck of data from I2C register address.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param num_bytes number of bytes to write
 * @param data data array to load data chunk for writing
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteData(tfa98xx_handle_t *handle, uint8_t subaddress, int num_bytes, const uint8_t data[]);

/*!
 * @brief Load TFA98xx firmware patch file.
 *
 * @param handle TFA98xx codec handle.
 * @param length length of firmware file without common header.
 * @param bytes byte array containing firmware binary
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ProcessPatchFile(tfa98xx_handle_t *handle, int length, const uint8_t *bytes);

/*!
 * @brief Check IC ROM version.
 *
 * This function checks IC ROM version to verify exact firmware version to be loaded
 *
 * @param handle TFA98xx codec handle.
 * @param patchheader header pointer of patch file
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_CheckICRomVersion(tfa98xx_handle_t *handle, const uint8_t patchheader[]);

/*!
 * @brief Check DSP stability.
 *
 * This function checks DSP is ready for initilization by checking I2S BCLK is stable or not.
 *
 * @param handle TFA98xx codec handle.
 * @param ready Status of DSP - Reference voltage, I2S clock, and MTP is not busy
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspCheckStability(tfa98xx_handle_t *handle, uint32_t *ready);

/*!
 * @brief Mute/Unmute
 *
 * This function mute/unmute audio.
 *
 * @param handle TFA98xx codec handle.
 * @param mute mute/unmute
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_Mute(tfa98xx_handle_t *handle,tfa9891_mute_t mute);

/*!
 * @brief Power down/up DSP.
 *
 * This function power down and up DSP. Power down doesn't require DSP re-initialization.
 *
 * @param handle TFA98xx codec handle.
 * @param powerdown 1 = Power Down, 0 = Power Up
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_Powerdown(tfa98xx_handle_t *handle, uint16_t powerdown);

/*!
 * @brief Read message to DSP
 *
 * This function read command message to DSP.
 *
 * @param handle TFA98xx codec handle.
 * @param length message length
 * @param buf data array store message body
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspReadMsg(tfa98xx_handle_t *handle, int length, uint8_t *bytes);

/*!
 * @brief Write message to DSP
 *
 * This function write command message to DSP.
 *
 * @param handle TFA98xx codec handle.
 * @param length message length
 * @param buf data array contains message body
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspWriteMsg(tfa98xx_handle_t *handle,int length, const char *buf);

/*!
 * @brief Read calibrated speaker impedance value from DSP
 * @param handle TFA98xx codec handle.
 * @param pRe25 Impedance value read from DSP
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspGetCalibrationImpedance(tfa98xx_handle_t *handle,float *pRe25);

/*!
 * @brief Wait until calibration done
 * @param calibrateDone 1 if calibratione successfully done, otherwise calibration fail
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WaitCalibrateDone(tfa98xx_handle_t *handle, int *calibrateDone);

/*!
 * @brief Write word to DSP memory
 *
 * This function write word size data to DSP SRAM.
 *
 * @param handle TFA98xx codec handle.
 * @param address DSP SRAM memory address
 * @param value word data
 * @param memtype DSP SRAM memory area
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspWriteMemWord(tfa98xx_handle_t *handle, uint16_t address, int value, int memtype);

/*!
 * @brief Parse container file and write Vstep to DSP
 *
 * This function parse container and write vstep tuning file to DSP.
 *
 * @param handle TFA98xx codec handle.
 * @param vp Pointer to vstep data
 * @param vstep_idx vstep index - obsolite
 * @param vste_msg_idx End point of msg in container
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ContWriteVstepMax2(tfa98xx_handle_t *handle,
                                    tfa98xx_volumeStepMax2File_t *vp,
                                    int vstep_idx,
                                    int vstep_msg_idx);

/*!
 * @brief Clear Calibrate Once
 *
 * This function unset Calibrate Once and set Calibrate Always by manually clearing MTPEX and MTPOTC.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ClearCalibrateOnce(tfa98xx_handle_t *handle);

#ifdef FACTORY_CALIBRATION_ONLY
/*!
 * @brief Set Calibrate Once
 *
 * This function set Calibrate Once by manually set MTPOTC and trigger calibration.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_SetCalibrateOnce(tfa98xx_handle_t *handle);
#endif

/*!
 * @brief Printe Calibrated impedance
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_PrintCalibration(tfa98xx_handle_t *handle);
#endif /* FSL_TFA9894_H_ */
