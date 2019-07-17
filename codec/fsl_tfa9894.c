/*
 * Copyright 2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fsl_lpi2c.h"
#include "fsl_common.h"
#include "fsl_codec_common.h"
#include "fsl_debug_console.h"
#include "fsl_tfa9894.h"
#include "tfa9894_tfafieldnames.h"

/* Select tuning parameter for specific speaker
 * - SELTECH_SPEAKER / CUI_SPEAKER / PUI_AS01808AO_SPEAKER */
#define PUI_AS01808AO_SPEAKER

#if defined(SELTECH_SPEAKER)
#include "TFA9894_Seltech_Demo.h"
#elif defined(CUI_SPEAKER)
#include "TFA9894_CUI_Demo.h"
#elif defined(PUI_AS01808AO_SPEAKER)
#include "TFA9894_PUI_AS01808AO.h"
#else
#error "No SPEAKER defined"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define DEMO_VERBOSE

#define TFA98XX_PATCH_EXTRA	6U
#define TFA98XX_INIT_BYPASS 0 /* 0 for DSP mode 1 for Bypass mode */
#define TFA9894_ENABLE_AEC_REFERENCE	/* Enable AEC reference signal back to host */
#define TFA_MONO_DOWNMIX 	/* Mono downmix = (L+R)/2 */

uint8_t g_NumDevice = TFA_MONO;

tfa98xx_operation_t g_TFA9894_operation = {
		TFA9894_Init, 		/* Init function */
		TFA9894_SetFormat,	/* Set I2S format */
		TFA9894_SetVolume,	/* Set AMP volume */
		TFA9894_DeInit		/* DeInit */
};

uint32_t g_SampleRate = 0;
uint16_t g_BitWidth = 0;

/*! @brief Unlock low level control of TFA9894N1 */
const tfa98xx_Registers_t g_TFA9894N1_Dev_prof0Reg[] = {
	{0x000f, 0xa245U}, {0x020f, 0x5288U}, {0x520f, 0xbe17U}, {0x560f, 0x05c3U}, {0x570f, 0x0344U},
	{0x610f, 0x0032U}, {0x710f, 0x00cfU}, {0x720f, 0x34a9U}, {0x730f, 0x3808U}, {0x760f, 0x0067U},
	{0x800f, 0x0000U}, {0x810f, 0x5715U}, {0x820f, 0x0104U}, {0xffff, 0}};

/*! @brief Unlock low level control of TFA9894N2 */
const tfa98xx_Registers_t g_TFA9894N2_Dev_prof0Reg[] = {
	{0x010f, 0x15daU}, {0x020f, 0x51e8U}, {0x040f, 0x0200U}, {0x520f, 0xbe17U}, {0x530f, 0x0dbeU},
	{0x570f, 0x0344U}, {0x610f, 0x0032U}, {0x710f, 0x6ecfU}, {0x720f, 0xb4a9U}, {0x730f, 0x38c8U},
	{0x760f, 0x0067U}, {0x800f, 0x0000U}, {0x810f, 0x5799U}, {0x820f, 0x0104U}, {0xffff, 0}};

#if (TFA98XX_INIT_BYPASS == 0)
const tfa98xx_Registers_t g_TFA9894N1_INI_prof0Reg[] = {
	{TFA9894_BF_TDMNBCK,0U},	/* 0 = 32FS, 2 = 64FS */
	{TFA9894_BF_TDMSLLN,15U},	/* 15 = 32FS, 31 = 64FS */
	{TFA9894_BF_TDMSSIZE,15U},	/* 15 = 32FS, 31 = 64FS */
	{TFA9894_BF_TDMSPKE,1U},
	{TFA9894_BF_TDMDCE,1U},
	{TFA9894_BF_TDMCSE,0},
	{TFA9894_BF_TDMVSE,0},
	{TFA9894_BF_TDMSPKS,0},
	{TFA9894_BF_TDMDCS,1U},
	{TFA9894_BF_TDMCSS,0},
	{TFA9894_BF_TDMVSS,1U},
	{TFA9894_BF_TDMCLINV,0},
#ifdef TFA9894_ENABLE_AEC_REFERENCE
	{TFA9894_BF_TDMCF2E,1U}, 	/* AEC output: Enable TDM slot 3 */
	{TFA9894_BF_TDMCF2SEL,1U},	/* AEC output: DSP AEC output without pilot tone */
	{TFA9894_BF_TDMCF2S, 0},	/* AEC output */
#endif /* TFA9894_ENABLE_AEC_REFERENCE */
	{TFA9894_BF_FRACTDEL,20U},
	{TFA9894_BF_DCTRACK,1U},
	{TFA9894_BF_AMPGAIN,190U},
	{TFA9894_BF_DCHOLD,8U},
	{TFA9894_BF_DCCV,3U},
	{TFA9894_BF_LVLCLPPWM,1U},
	{TFA9894_BF_DELCURCOMP,2U},
	{TFA9894_BF_HPFBYP,0},
	{TFA9894_BF_TDMSPKG,4U},
	{TFA9894_BF_TDMDCG,4U},
	{TFA9894_BF_DCTRIP,9U},
	{TFA9894_BF_DCTRIP2,15U},
	{TFA9894_BF_DCTRIPT,13U},
	{TFA9894_BF_DCVOF,30U},
	{TFA9894_BF_DCVOS,63U},
	{TFA9894_BF_AMPE,1U},
#ifdef FACTORY_CALIBRATION_ONLY
	{TFA9894_BF_DCA,0},
	{TFA9894_BF_AMPE,1U},
	{TFA9894_BF_TROS,1U},
	{TFA9894_BF_LPM1MODE,1U},
	{TFA9894_BF_LNMODE,1U},
	{TFA9894_BF_TROS,1U},
	{TFA9894_BF_EXTTS,25U},
#endif /*FACTORY_CALIBRATION_ONLY */
	{TFA9894_BF_CFE,1U},
    {TFA9894_BF_AMPC,1U},
	{TFA9894_BF_AMPINSEL,2U},
	{TFA9894_BF_DCINSEL,2U},
	{TFA9894_BF_EXTTS,25U},
#ifdef BROWNOUT_DETECT_SUPPORT
	{TFA9894_BF_BODE,1U},
	{TFA9894_BF_BODTHLVL,2U},
	{TFA9894_BF_MANROBOD,1U},
#endif/*BROWNOUT_DETECT_SUPPORT */
    {0xffff, 0}};
#endif /* TFA98XX_INIT_BYPASS == 0 */


#if (TFA98XX_INIT_BYPASS == 1)
/* No AEC feedback in bypass mode */
const tfa98xx_Registers_t g_TFA9894N1_INI_bypassReg[] = {{TFA9894_BF_TDMNBCK,0},
	{TFA9894_BF_TDMSLLN,15U},
	{TFA9894_BF_TDMSSIZE,15U},
	{TFA9894_BF_TDMSPKE,1U},
	{TFA9894_BF_TDMDCE,1U},
	{TFA9894_BF_TDMCSE,0},
	{TFA9894_BF_TDMVSE,0},
	{TFA9894_BF_TDMSPKS,0},
	{TFA9894_BF_TDMDCS,1U},
	{TFA9894_BF_TDMCSS,0},
	{TFA9894_BF_TDMVSS,1U},
	{TFA9894_BF_TDMCLINV,0},
	{TFA9894_BF_FRACTDEL,20U},
	{TFA9894_BF_DCTRACK,1U},
	{TFA9894_BF_AMPGAIN,190U},
	{TFA9894_BF_DCHOLD,8U},
	{TFA9894_BF_DCCV,3U},
	{TFA9894_BF_LVLCLPPWM,1U},
	{TFA9894_BF_DELCURCOMP,2U},
	{TFA9894_BF_HPFBYP,0},
	{TFA9894_BF_TDMSPKG,4U},
	{TFA9894_BF_TDMDCG,4U},
	{TFA9894_BF_DCTRIP,9U},
	{TFA9894_BF_DCTRIP2,15U},
	{TFA9894_BF_DCTRIPT,13U},
	{TFA9894_BF_DCVOF,30U},
	{TFA9894_BF_DCVOS,63U},
	{TFA9894_BF_AMPE,1U},
	{TFA9894_BF_DCA,1U},
	{TFA9894_BF_AMPINSEL,0},
	{TFA9894_BF_DCINSEL,0},
	{TFA9894_BF_HPFBYP,1U},
	{TFA9894_BF_CFE,0},
	{TFA9894_BF_AMPC,0},
	{0xffff, 0}};
#endif /* TFA98XX_INIT_BYPASS == 1 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static status_t tfa98xx_dsp_read_mem(tfa98xx_handle_t *handle, unsigned int start_offset, int num_words, int *pValues);
static void tfa98xx_convert_data2bytes(int num_data, const int data[], uint8_t bytes[]);
static void tfa98xx_convert_bytes2data(int num_bytes, const uint8_t bytes[], int data[]);
static status_t tfa98xx_dsp_msg_id(tfa98xx_handle_t *handle, int length, const char *buf, uint8_t cmdid[3]);
static status_t tfa98xx_dsp_msg_write_id(tfa98xx_handle_t *handle, int length, const char *buffer, uint8_t cmdid[3]);
static status_t tfa98xx_wait_result(tfa98xx_handle_t *handle, int wait_retry_count);
static status_t tfa98xx_check_rpc_status(tfa98xx_handle_t *handle, int *pRpcStatus);
static status_t tfa98xx_dsp_msg_status(tfa98xx_handle_t *handle, int *pRpcStatus);
static status_t tfa98xx_dsp_cmd_id_write_read(
    tfa98xx_handle_t *handle, uint8_t module_id, uint8_t param_id, int num_bytes, uint8_t data[]);
static status_t  tfaRunWriteBitfieldTfa98xx(tfa98xx_handle_t *handle,  tfa98xx_Bitfield_t bf);
static void tfa2_manual_mtp_cpy(tfa98xx_handle_t *handle,
                                uint16_t reg_row_to_keep,
                                uint16_t reg_row_to_set,
                                uint8_t row);

/*!
 * @brief Set I2S format.
 * Since TFA9894 is not a codec but amplifier, dynamic audio format change is not supported.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_SetFormat(tfa98xx_handle_t *handle,
		uint32_t mclk,
        uint32_t sampleRate,
        uint32_t bitWidth) /*!< Codec format setting */
{
	if(!handle)
		return kStatus_TFA98XX_Bad_Parameter;
	/* Function not supported */
	TFA98xx_Printf("Function %s not supported\n", __FUNCTION__);
	return kStatus_TFA98XX_Ok;
}

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
status_t TFA9894_SetVolume(tfa98xx_handle_t *handle, uint8_t volume_atten)
{
	uint16_t mstate = 0;

	if(!handle)
		return kStatus_TFA98XX_Bad_Parameter;
	if(volume_atten > 255)
		return kStatus_TFA98XX_Bad_Parameter;

	return TFA98XX_WriteBitf(handle, TFA9894_BF_VOL, volume_atten);
}

/*!
 * @brief Initialize TFA9894.
 *
 * @param handle TFA98xx codec handle.
 * @param config Codec configuration.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_Init(tfa98xx_handle_t *handle, codec_config_t *config)
{
	status_t error = kStatus_TFA98XX_Ok;
	uint8_t trial = 10U;
	uint16_t regRead = 0;
	uint16_t xor = 0;
	uint32_t status;
	int calibrateDone = 0;
	float re25;
	int i;
	tfa98xx_Registers_t *pRegs = NULL;
	uint8_t *pFirmware = NULL;
	uint32_t Firmware_len = 0;
	uint8_t *pSpeaker = NULL;
	uint32_t Speaker_len = 0;
	uint8_t *pVSteps = NULL;
	uint8_t *pExfilter_msg = NULL;
	uint32_t Exfilter_msg_len = 0;

	if(!handle)
		return kStatus_TFA98XX_Bad_Parameter;
	if(config)
		memcpy(&handle->op, &config->op, sizeof(tfa98xx_operation_t));

	/* Read Device ID TFA9894 == 0x1a94 */
	regRead = TFA98XX_ReadBitf(handle, TFA9894_BF_REV);
	if(regRead == 0x1a94U) 
	{
		/* Not support TFA9894N1A1 */
		error = kStatus_TFA98XX_I2C_Fatal;
	}
	else if((regRead == 0x2a94U) || regRead == 0x3a94) 
	{
		/* TFA9894 N2 */
		pRegs = (tfa98xx_Registers_t *)g_TFA9894N2_Dev_prof0Reg;
		pFirmware = (uint8_t *)Firmware_N2A1_patch;
		Firmware_len = Firmware_N2A1_patch_len;
	}
	else
		error = kStatus_TFA98XX_I2C_Fatal;
	assert(error == kStatus_TFA98XX_Ok);

#ifdef SELTECH_SPEAKER
	pSpeaker = (uint8_t *)Seltech_speaker;
	Speaker_len = Seltech_speaker_len;
	pVSteps = (uint8_t *)music_P_48000_vstep;
	pExfilter_msg = (uint8_t *)seltech_music_P_48000_excursion_filter_msg;
	Exfilter_msg_len = seltech_music_P_48000_excursion_filter_msg_len;
#elif defined(CUI_SPEAKER)
	pSpeaker = (uint8_t *)CMS_181325_078SP_speaker;
	Speaker_len = CMS_181325_078SP_speaker_len;
	pVSteps = (uint8_t *)RT_Voice_music_P_48000_vstep;
	pExfilter_msg = (uint8_t *)Left_excursion_filter_msg;
	Exfilter_msg_len = Left_excursion_filter_msg_len;
#elif defined(PUI_AS01808AO_SPEAKER)
	pSpeaker = (uint8_t *)PUI_AS01808AO_speaker;
	Speaker_len = PUI_AS01808AO_speaker_len;
	pVSteps = (uint8_t *)music_P_48000_vstep;
	pExfilter_msg = (uint8_t *)PUI_AS01808AO_music_P_48000_excursion_filter_msg;
	Exfilter_msg_len = PUI_AS01808AO_music_P_48000_excursion_filter_msg_len;
#endif
	/*************************/
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_I2CR, 1U);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_MANSCONF,0);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_MANCOLD,1U);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_RST,1U);
	assert(error == kStatus_TFA98XX_Ok);

	/* Unlock keys to write settings */
	error = TFA98XX_WriteRegister(handle, 0x0F, (uint16_t)0x5A6BU);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_ReadRegister(handle, 0xFB, &regRead);
	assert(error == kStatus_TFA98XX_Ok);
	xor = regRead ^ 0x005AU;
	error = TFA98XX_WriteRegister(handle, 0xA0, xor);
	assert(error == kStatus_TFA98XX_Ok);
	/* Write Device specific registers */
	while(pRegs->reg != 0xffff) 
	{
		error = TFA98XX_WriteBitfVolitale(handle, pRegs->reg, pRegs->val);
		assert(error == kStatus_TFA98XX_Ok);
		pRegs += 1;
	}
	/* Write profile specific registers */
#if TFA98XX_INIT_BYPASS == 1
	pRegs = (tfa98xx_Registers_t *)g_TFA9894N1_INI_bypassReg;
#else
	pRegs = (tfa98xx_Registers_t *)g_TFA9894N1_INI_prof0Reg;
#endif /* TFA98XX_INIT_BYPASS == 1 */
	while(pRegs->reg != 0xffff) 
	{
		error = TFA98XX_WriteBitfVolitale(handle, pRegs->reg, pRegs->val);
		assert(error == kStatus_TFA98XX_Ok);
		pRegs += 1;
	}
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_MANSCONF,1U);
	error = TFA98XX_Powerdown(handle, TFA_POWERUP);
	assert(error == kStatus_TFA98XX_Ok);

	/* Stop here in bypass mode */
#if TFA98XX_INIT_BYPASS == 1
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_MANSCONF,1U);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_SBSL,1U);
	assert(error == kStatus_TFA98XX_Ok);
	goto SUCCESS_END;
#endif /* TFA98XX_INIT_BYPASS == 1 */
	/* Check the PLL is powered up from status register 10h*/
	TFA98XX_ReadRegister(handle, 0x10,&regRead);
	while ( (regRead & 0x2000) == 0)
	{
		TFA98XX_ReadRegister(handle, 0x10, &regRead);
	}

	/* Force Coldstart */
	while (TFA98XX_ReadBitf(handle, TFA9894_BF_ACS)!= 1) 
	{
		error = TFA98XX_DspWriteMemWord(handle, 0x8100, 1, DMEM_IOMEM);
		if (trial-- == 0) 
		{
			return 1;
		}
	}
	assert(error == kStatus_TFA98XX_Ok);
	for ( trial=1; trial < 10; trial++ ) 
	{
		error = TFA98XX_DspCheckStability(handle, &status);
		if ( status )
			break;
		else
			for(i=0;i<0xfff;i++)
				; /* Busy waiting instead of Sleep(10) */
	}
	if (trial >=10)
	{
		TFA98xx_Printf("Timed out , exit, exit\r\n");
		return 1;
	}
	else
		TFA98xx_Printf(" OK (trial=%d)\r\n", trial);

#ifdef FACTORY_CALIBRATION_ONLY
	TFA98XX_ClearCalibrateOnce(handle);
	TFA98XX_SetCalibrateOnce(handle);
#else
	TFA98XX_ClearCalibrateOnce(handle);
#endif /* FACTORY_CALIBRATION_ONLY */
	error = TFA98XX_CheckICRomVersion(handle, pFirmware);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("SC:%x PATCH loading Start--length to be  loaded:%d\r\n",handle->slaveAddress, 
					Firmware_len - TFA98XX_PATCH_EXTRA );
	error = TFA98XX_ProcessPatchFile(handle, Firmware_len-6, pFirmware + TFA98XX_PATCH_EXTRA);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("FRACTDEL_after211 :%d",TFA98XX_ReadBitf(handle, TFA9894_BF_FRACTDEL));
	TFA98xx_Printf(" PATCH OK \r\n");
	error = TFA98XX_DspWriteMemWord(handle, 512U, 0, DMEM_XMEM);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_RST,0);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("FRACTDEL_after222 :%d\n",TFA98XX_ReadBitf(handle, TFA9894_BF_FRACTDEL));
	error = TFA98XX_Mute(handle,Mute_Digital);
	assert(error == kStatus_TFA98XX_Ok);
    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetInputSelector_msg_len);
#ifdef TFA_MONO_DOWNMIX
	error = TFA98XX_DspWriteMsg(handle, SetInputSelector_msg_len, (const char *)Mix_SetInputSelector_msg);
#else
	error = TFA98XX_DspWriteMsg(handle, SetInputSelector_msg_len, (const char *)Left_SetInputSelector_msg);
#endif /* TFA_MONO_DOWNMIX */
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk1\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetOutputSelector_msg_len);
	error = TFA98XX_DspWriteMsg(handle, SetOutputSelector_msg_len, (const char *)SetOutputSelector_msg);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk2\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetProgramConfig_msg_len);
	error = TFA98XX_DspWriteMsg(handle, SetProgramConfig_msg_len, (const char *)SetProgramConfig_msg);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk3\r\n");

	TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n",handle->slaveAddress,SetLagW_msg_len );
	error = TFA98XX_DspWriteMsg(handle, SetLagW_msg_len, (const char *)SetLagW_msg );
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk4\r\n");
	/*****************/
    TFA98xx_Printf("SC:%x Speaker loading Start--length to be  loaded:%d\r\n", handle->slaveAddress, Speaker_len);
	error = TFA98XX_DspWriteMsg(handle, Speaker_len, (const char *)pSpeaker);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("SpeakerOk\r\n");
	/*********************/
#ifdef FACTORY_CALIBRATION_ONLY  
    error = TFA98XX_ContWriteVstepMax2(handle, (tfa98xx_volumeStepMax2File_t *)Calibration_vstep, 0,
                                       TFA_MAX_VSTEP_MSG_MARKER);
#else
	error = TFA98XX_ContWriteVstepMax2(handle,(tfa98xx_volumeStepMax2File_t *)pVSteps,0, TFA_MAX_VSTEP_MSG_MARKER);
#endif /* FACTORY_CALIBRATION_ONLY */
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("VSTEPOk\r\n");

	TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n",handle->slaveAddress,SetGains_msg_len );
	error = TFA98XX_DspWriteMsg(handle, SetGains_msg_len, (const char *)SetGains_msg);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk9\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetSensesDelay_msg_len);
	error = TFA98XX_DspWriteMsg(handle, SetSensesDelay_msg_len, (const char *)SetSensesDelay_msg);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk10\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetSensesCal_msg_len);
	error = TFA98XX_DspWriteMsg(handle, SetSensesCal_msg_len, (const char *)SetSensesCal_msg );
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk11\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   SetvBatFactors_msg_len);
	error = TFA98XX_DspWriteMsg(handle, SetvBatFactors_msg_len, (const char *)SetvBatFactors_msg);
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk12\r\n");

    TFA98xx_Printf("SC:%x Message loading Start--length to be  loaded:%d\r\n", handle->slaveAddress,
                   Exfilter_msg_len);
	error = TFA98XX_DspWriteMsg(handle, Exfilter_msg_len, (const char *)pExfilter_msg );
	assert(error == kStatus_TFA98XX_Ok);
	TFA98xx_Printf("MessageOk15\r\n");

	error = TFA98XX_Powerdown(handle,TFA_POWERUP);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_MANSCONF,1);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_SBSL,1);
	assert(error == kStatus_TFA98XX_Ok);
	error = TFA98XX_Mute(handle,Mute_Off);

#ifdef DEMO_VERBOSE
	TFA98XX_ReadRegister(handle, 0x10, &regRead);
	TFA98xx_Printf("Status reg 0x10 = 0x%04x\r\r\n", regRead);
	TFA98XX_ReadRegister(handle, 0x11, &regRead);
	TFA98xx_Printf("Status reg 0x11 = 0x%04x\r\r\n", regRead);
	TFA98XX_ReadRegister(handle, 0x12, &regRead);
	TFA98xx_Printf("Status reg 0x12 = 0x%04x\r\r\n", regRead);
	TFA98XX_ReadRegister(handle, 0x13, &regRead);
	TFA98xx_Printf("Status reg 0x13 = 0x%04x\r\r\n", regRead);
	assert(error == kStatus_TFA98XX_Ok);
#endif /* DEMO_VERBOSE */
	error = TFA98XX_WaitCalibrateDone(handle, &calibrateDone);
	if(error != kStatus_TFA98XX_Ok) 
	{
		TFA98xx_Printf("Calibration Fail [%x]\r\r\n", error);
		return 0;
	}
	assert(error == kStatus_TFA98XX_Ok);

	if (calibrateDone)
	{
		error = TFA98XX_DspGetCalibrationImpedance(handle, &re25);
		assert(error == kStatus_TFA98XX_Ok);
	}
	else
	{
        re25 = 0.0;
	}
	TFA98xx_Printf("TFA9894 0x%02X Calibration value is %2.2f mohm\r\n", handle->slaveAddress, re25);
	error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_OPENMTP,0);
    TFA98xx_Printf("MTPOTC=%d MTPEX=%d TFA9894_BF_OPENMTP=%d\r\n", TFA98XX_ReadBitf(handle, TFA9894_BF_MTPOTC),
                   TFA98XX_ReadBitf(handle, TFA9894_BF_MTPEX), TFA98XX_ReadBitf(handle, TFA9894_BF_OPENMTP));

#if TFA98XX_INIT_BYPASS == 1
SUCCESS_END:
#endif
	return (int)error;
}

/*!
 * @brief DeInitilize TFA9894.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA9894_DeInit(tfa98xx_handle_t *handle)
{
	TFA98xx_Printf("%s: Device 0x%02x deinit", __FUNCTION__, handle->slaveAddress);
	TFA98XX_Powerdown(handle, TFA_POWERDOWN);
	return kStatus_TFA98XX_Ok;
}

/*!
 * @brief Read TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param value value read from I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ReadRegister(tfa98xx_handle_t *handle, uint8_t subaddress, uint16_t * value)
{
	status_t err = kStatus_TFA98XX_Ok;
	lpi2c_master_transfer_t transfer;
    uint8_t retval = 0;
    static uint8_t data[2] = {0};

    if(!value) 
	{
        err = kStatus_TFA98XX_Bad_Parameter;
        goto error_return;
    }

	transfer.flags = 0;
	transfer.slaveAddress = handle->slaveAddress;
	transfer.direction = kLPI2C_Read;
	transfer.subaddress = subaddress;
	transfer.subaddressSize = 1;
	transfer.data = data;
	transfer.dataSize = sizeof(short);

	retval = LPI2C_MasterTransferBlocking(handle->base, &transfer);
    if (retval != kStatus_Success)
    {
        err = kStatus_TFA98XX_I2C_Fatal;
        goto error_return;
    }

	if(transfer.dataSize == 2) 
	{
	    memcpy(value, transfer.data, 2U);
		*value = (*value <<8) | ((*value >> 8) & 0x00ff);
	}
	else
		err = kStatus_TFA98XX_I2C_Fatal;
#if defined(DEMO_VERBOSE)
    TFA98xx_Printf("R(0x%02x):", subaddress);
   	TFA98xx_Printf("[0x%04x]", *value);
    TFA98xx_Printf("\r\n");
#endif
error_return:
	return err;
}

/*!
 * @brief Get Bitfield of TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @return Bitfield value read from I2C register.
 */
uint16_t TFA98XX_ReadBitf(tfa98xx_handle_t *handle, const uint16_t bf)
{
	uint16_t regvalue = 0;
	uint16_t msk = 0;
	uint16_t value;
	uint8_t len = bf & 0x0f;
	uint8_t pos = (bf >> 4) & 0x0f;
	uint8_t address = (bf >> 8) & 0xff;

	TFA98XX_ReadRegister(handle, address,&regvalue);
	msk = ((1<<(len+1))-1)<<pos;
	regvalue &= msk;
	value = regvalue>>pos;
	return value;
}

/*!
 * @brief Read Bitfield from value. No I2C transaction triggered by function call.
 *
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param reg_value Register value already read from I2C register
 * @return Bitfield value.
 */
uint16_t TFA98XX_ReadBitfValue(const uint16_t bf, const uint16_t reg_value)
{
	uint16_t msk, value;

	/*
	 * bitfield enum:
	 * - 0..3  : len
	 * - 4..7  : pos
	 * - 8..15 : address
	 */
	uint8_t len = bf & 0x0f;
	uint8_t pos = (bf >> 4) & 0x0f;

	msk = ((1<<(len+1))-1)<<pos;
	value = (reg_value & msk) >> pos;

	return value;
}

/*!
 * @brief Read chunck of data from I2C register address.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param num_bytes number of bytes to read
 * @param data data array to store data chunk after read
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ReadData(tfa98xx_handle_t *handle, uint8_t subaddress, int num_bytes, uint8_t data[])
{
	lpi2c_master_transfer_t transfer;
	status_t err = kStatus_TFA98XX_Ok;
    uint8_t retval = 0;
#if defined(DEMO_VERBOSE)
    int i;
#endif

	transfer.flags = 0;
	transfer.slaveAddress = handle->slaveAddress;
	transfer.direction = kLPI2C_Read;
	transfer.subaddress = subaddress;
	transfer.subaddressSize = 1U;
	transfer.data = data;
	transfer.dataSize = num_bytes;

	retval = LPI2C_MasterTransferBlocking(handle->base, &transfer);
    if (retval != kStatus_Success)
    {
        err = kStatus_TFA98XX_I2C_Fatal;
    }

#if defined(DEMO_VERBOSE)
    TFA98xx_Printf("R(0x%02x):", subaddress);
    for(i=0; i<transfer.dataSize;i++) 
	{
    	TFA98xx_Printf("[0x%02x]", (uint8_t)data[i]);
    }
    TFA98xx_Printf("\r\n");
#endif
	return err;
}

/*!
 * @brief Write value to TFA98XX I2C register
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteRegister(tfa98xx_handle_t *handle, uint8_t subaddress, uint16_t value)
{
	lpi2c_master_transfer_t transfer;
	status_t err = kStatus_TFA98XX_Ok;
    uint8_t retval = 0;
    static uint8_t data[2] = {0};

#if defined(DEMO_VERBOSE)
    TFA98xx_Printf("W(0x%02x):", subaddress);
    TFA98xx_Printf("[0x%02x]", value);
    TFA98xx_Printf("\r\n");
#endif
	transfer.flags = 0;
	transfer.slaveAddress = handle->slaveAddress;
	transfer.direction = kLPI2C_Write;
	transfer.subaddress = subaddress;
	transfer.subaddressSize = 1;
	transfer.dataSize = sizeof(short);
    data[0] = (value >> 8);
    data[1] = value;
    transfer.data = (void *)data;

	retval = LPI2C_MasterTransferBlocking(handle->base, &transfer);
    if (retval != kStatus_Success)
    {
        err = kStatus_TFA98XX_I2C_Fatal;
    }

	return err;
}

/*!
 * @brief Write bitfield to TFA98XX I2C register. No I2C transaction if old value is the same with new value.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteBitf(tfa98xx_handle_t *handle, const uint16_t bf, const uint16_t value)
{
	status_t err = kStatus_TFA98XX_Ok;
	uint16_t regvalue = 0;
	uint16_t msk, oldvalue;
	uint8_t len = (bf & 0x0f);
	uint8_t pos = (bf >> 4) & 0x0f;
	uint8_t address = (bf >> 8) & 0xff;

	err = TFA98XX_ReadRegister(handle, address,&regvalue);
	oldvalue = regvalue;
	msk = ((1<<(len+1))-1)<<pos;
	regvalue &= ~msk;
	regvalue |= value<<pos;

	if(oldvalue != regvalue)
		err = TFA98XX_WriteRegister(handle, (bf >> 8) & 0xff, regvalue);

	return err;
}

/*!
 * @brief Write bitfield to TFA98XX I2C register.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param value value write to I2C register
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteBitfVolitale(tfa98xx_handle_t *handle, const uint16_t bf, const uint16_t value)
{
	status_t err = kStatus_TFA98XX_Ok;
	uint16_t regvalue = 0;
	uint16_t msk;
	uint8_t len = (bf & 0x0f);
	uint8_t pos = (bf >> 4) & 0x0f;
	uint8_t address = (bf >> 8) & 0xff;

	err = TFA98XX_ReadRegister(handle, address,&regvalue);
	if(err != kStatus_TFA98XX_Ok)
		return err;

	msk = ((1<<(len+1))-1)<<pos;
	regvalue &= ~msk;
	regvalue |= value<<pos;

	return TFA98XX_WriteRegister(handle, (bf >> 8) & 0xff, regvalue);
}

/*!
 * @brief Set Bitfield from value. No I2C transaction triggered by function call.
 *
 * @param bf bitfield macro constant - I2C register address[15..8] bitfield position[7..4] length[3..0].
 * @param reg_value Register value already read from I2C register
 * @return Bitfield value.
 */
void TFA98XX_WriteBitfValue(const uint16_t bf, const uint16_t bf_value, uint16_t *p_reg_value)
{
	uint16_t regvalue, msk;

	/*
	 * bitfield enum:
	 * - 0..3  : len
	 * - 4..7  : pos
	 * - 8..15 : address
	 */
	uint8_t len = bf & 0x0f;
	uint8_t pos = (bf >> 4) & 0x0f;

	assert(p_reg_value != NULL);

	regvalue = *p_reg_value;
	msk = ((1<<(len+1))-1)<<pos;
	regvalue &= ~msk;
	regvalue |= bf_value<<pos;
	*p_reg_value = regvalue;

	return;
}

/*!
 * @brief Write chunck of data from I2C register address.
 *
 * @param handle TFA98xx codec handle.
 * @param subaddress I2C register address.
 * @param num_bytes number of bytes to write
 * @param data data array to load data chunk for writing
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WriteData(tfa98xx_handle_t *handle, uint8_t subaddress, int num_bytes, const uint8_t data[])
{
	lpi2c_master_transfer_t transfer;
	status_t err = kStatus_TFA98XX_Ok;
    uint8_t retval = 0;
#if defined(DEMO_VERBOSE)
    int i;

    TFA98xx_Printf("W(0x%02x):", subaddress);
    for(i=0; i<num_bytes;i++)
    	TFA98xx_Printf("[0x%02x]", data[i]);
    TFA98xx_Printf("\r\n");
#endif
	transfer.flags = 0;
	transfer.slaveAddress = handle->slaveAddress;
	transfer.direction = kLPI2C_Write;
	transfer.subaddress = subaddress;
	transfer.subaddressSize = 1U;
	transfer.data = (void *)data;
	transfer.dataSize = num_bytes;

	retval = LPI2C_MasterTransferBlocking(handle->base, &transfer);
    if (retval != kStatus_Success)
    {
        err = kStatus_TFA98XX_I2C_Fatal;
    }

	return err;
}

/*!
 * @brief Load TFA98xx firmware patch file.
 *
 * @param handle TFA98xx codec handle.
 * @param length length of firmware file without common header.
 * @param bytes byte array containing firmware binary
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ProcessPatchFile(tfa98xx_handle_t *handle, int length, const uint8_t *bytes)
{
	uint16_t size;
	int index;

	lpi2c_master_transfer_t transfer;
	status_t err = kStatus_TFA98XX_Ok;
    uint8_t retval = 0;
#if defined(DEMO_VERBOSE)
    int i;
#endif

	/* expect following format in patchBytes:
	* 2 bytes length of I2C transaction in little endian, then the bytes, excluding the slave address which is added from the handle
	* This repeats for the whole file
	*/
	index = 0;

	transfer.flags = 0;
	transfer.slaveAddress = handle->slaveAddress;
	transfer.direction = kLPI2C_Write;
	transfer.subaddress = 0;
	transfer.subaddressSize = 0;

	while (index < length) 
	{
		/* extract little endian length */
		size = bytes[index] + bytes[index + 1] * 256;
		index += 2;
		if ((index + size) > length) 
		{
			/* too big, outside the buffer, error in the input data */
			return kStatus_TFA98XX_Bad_Parameter;
		}
		if ((size + 1) > MAX_I2C_LENGTH) 
		{
			/* too big, must fit buffer */
			return kStatus_TFA98XX_Bad_Parameter;
		}

		transfer.data = (void *)(bytes + index);
		transfer.dataSize = size;

        TFA98xx_Printf("Bytes to be written_patch:%d (index = %d bytes[index] = %d bytes[index+1] = %d\r\n", size,
                       index, bytes[index], bytes[index + 1]);
		retval = LPI2C_MasterTransferBlocking(handle->base, &transfer);
		if (retval != kStatus_Success)
		{
			TFA98xx_Printf("I2C write error at \r\n",size);
			err = kStatus_TFA98XX_I2C_Fatal;
			break;
		}
#if defined(DEMO_VERBOSE)
		for(i=0; i<transfer.dataSize;i++)
			TFA98xx_Printf("[%02x]", ((uint8_t *)transfer.data) + i);
		TFA98xx_Printf("\r\n");
#endif
		index += size;
	}
	return err;
}

/*!
 * @brief Check IC ROM version.
 *
 * This function checks IC ROM version to verify exact firmware version to be loaded
 *
 * @param handle TFA98xx codec handle.
 * @param patchheader header pointer of patch file
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_CheckICRomVersion(tfa98xx_handle_t *handle, const uint8_t patchheader[])
{
	status_t error = kStatus_TFA98XX_Ok;
	uint16_t checkrev;
	uint16_t checkaddress;
	int checkvalue;
	int value = 0;
	uint16_t status;
	checkrev = patchheader[0];
	if ((checkrev != 0xFF) && (checkrev != 0x94)) 
	{
		return kStatus_TFA98XX_Not_Supported;
	}
	checkaddress = (patchheader[1] << 8) + patchheader[2];
	checkvalue = (patchheader[3] << 16) + (patchheader[4] << 8) + patchheader[5];
	if (checkaddress != 0xFFFF) 
	{
		/* before reading XMEM, check if we can access the DSP */
		error = TFA98XX_ReadRegister(handle, 0x00, &status);
		if (error == kStatus_TFA98XX_Ok) 
		{
			if ((status & 0x8000) != 0x8000) 
			{
				/* one of Vddd, PLL and clocks not ok */
				error = kStatus_TFA98XX_DSP_not_running;
			}
		}
		/* read some address register that allows checking the correct ROM version */
		if (error == kStatus_TFA98XX_Ok) 
		{
			error =	tfa98xx_dsp_read_mem(handle, checkaddress, 1, &value);
		}
		if (error == kStatus_TFA98XX_Ok) 
		{
			if (value != checkvalue) 
			{
					error = kStatus_TFA98XX_Not_Supported;
			}
		}
	}
	return error;
}

/*!
 * @brief Check DSP stability.
 *
 * This function checks DSP is ready for initilization by checking I2S BCLK is stable or not.
 *
 * @param handle TFA98xx codec handle.
 * @param ready Status of DSP - Reference voltage, I2S clock, and MTP is not busy
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspCheckStability(tfa98xx_handle_t *handle, uint32_t *ready)
{
	status_t  error = kStatus_TFA98XX_Ok;
	uint16_t status;
	uint16_t value;

	/* check the contents of the STATUS register */
	error = TFA98XX_ReadRegister(handle, 0x10, &value);
	if (error != kStatus_TFA98XX_Ok) 
	{
		*ready = 0;
		TFA98xx_Printf("%s[%d]: Fatal Error\r\n", __FUNCTION__, __LINE__);
		return error;
	}
	status = (uint16_t)value;

	/* check AREFS and CLKS: not ready if either is clear */
    *ready = !((TFA98XX_ReadBitfValue(TFA9894_BF_AREFS, status) == 0) ||
               (TFA98XX_ReadBitfValue(TFA9894_BF_CLKS, status) == 0) ||
               (TFA98XX_ReadBitfValue(TFA9894_BF_MTPB, status) == 1));

	return error;
}

/*!
 * @brief Power down/up DSP.
 *
 * This function power down and up DSP. Power down doesn't require DSP re-initialization.
 *
 * @param handle TFA98xx codec handle.
 * @param powerdown 1 = Power Down, 0 = Power Up
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_Powerdown(tfa98xx_handle_t *handle, uint16_t powerdown)
{
	status_t error = kStatus_TFA98XX_Ok;

	/* if powerdown = 1, power down DSP, if powerdown = 0, power up DSP */
	error = TFA98XX_WriteBitfVolitale(handle, TFA9894_BF_PWDN, (uint16_t)powerdown);
	return error;
}

/*!
 * @brief Mute/Unmute
 *
 * This function mute/unmute audio.
 *
 * @param handle TFA98xx codec handle.
 * @param mute mute/unmute
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t  TFA98XX_Mute(tfa98xx_handle_t *handle, tfa9891_mute_t mute)
{
	status_t error;

	switch (mute) 
	{
	case Mute_Off:
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_CFSM,(uint16_t)0);
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_AMPE,(uint16_t)1);
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_DCA,(uint16_t)1);
		break;
	case Mute_Digital:
		/* expect the amplifier to run */
		/* set the cf_mute bit */
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_CFSM,(uint16_t)1);
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_AMPE,(uint16_t)1);
		error = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_DCA,(uint16_t)0);
		break;
	default:
		error = kStatus_TFA98XX_Bad_Parameter;
	}

	return error;
}

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
status_t TFA98XX_DspWriteMemWord(tfa98xx_handle_t *handle, uint16_t address, int value, int memtype)
{
	status_t error = kStatus_TFA98XX_Ok;
	uint8_t bytes[3];

	TFA98XX_WriteBitfVolitale(handle, TFA9894_BF_DMEM, (uint16_t)memtype);
	error = - TFA98XX_WriteBitf(handle, TFA9894_BF_MADD,address);
	if (error != kStatus_TFA98XX_Ok)
		return error;
    tfa98xx_convert_data2bytes(1, &value, bytes);
	error = TFA98XX_WriteData(handle, 0x920f>>8, 3, bytes);

	return error;
}

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
status_t TFA98XX_DspWriteMsg(tfa98xx_handle_t *handle, int length, const char *buf)
{
	status_t error;
	int tries, rpc_status = kStatus_Success;

	/* write the message and notify the DSP */
	error = tfa98xx_dsp_msg_write_id(handle, length, buf,NULL);
	if( error != kStatus_TFA98XX_Ok)
		return error;
	else
		TFA98xx_Printf("tfa_dsp_msg_write_id_tfa98xx error :%d\r\n",error);

	/* get the result from the DSP (polling) */
	for(tries=TFA98XX_WAITRESULT_NTRIES; tries>0;tries--) 
	{
#ifdef TFA98XX_PRINT_DEBUG
		TFA98xx_Printf("tries:%d\r\n",tries);
#endif /* TFA98XX_PRINT_DEBUG */
		error = tfa98xx_dsp_msg_status(handle, &rpc_status);
		if (error == kStatus_TFA98XX_Ok && rpc_status == kStatus_Success)
			break;
		else
			TFA98xx_Printf("Error_status:%d--rpc_status:%d\r\n",error,rpc_status);

	/* If the rpc status is a specific error we want to know it.
	* If it is busy or not running it should retry
	*/
		if(rpc_status != kStatus_LPI2C_Busy && rpc_status != -1)
		{
			TFA98xx_Printf("%s[%d]: Error\r\n", __FUNCTION__, __LINE__);
			break;
		}
	}

	if (rpc_status != kStatus_Success) 
	{
		TFA98xx_Printf("%s[%d]: Error\r\n", __FUNCTION__, __LINE__);
		/* DSP RPC call returned an error */
		error = (status_t) (rpc_status + kStatus_TFA98XX_RpcBase);
	}

	return error;
}

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
status_t TFA98XX_DspReadMsg(tfa98xx_handle_t *handle, int length, uint8_t *bytes)
{
	status_t error = kStatus_TFA98XX_Ok;
	int burst_size;		/* number of words per burst size */
	int num_bytes;
	int offset = 0;
	uint16_t start_offset=2; /* msg starts @xmem[2] ,[1]=cmd */

	TFA98XX_WriteBitfVolitale(handle, TFA9894_BF_DMEM, (uint16_t)DMEM_XMEM);
	error = -TFA98XX_WriteBitf(handle, TFA9894_BF_MADD, start_offset);
	if (error != kStatus_TFA98XX_Ok)
		return error;

	num_bytes = length; /* input param */
	while (num_bytes > 0) 
	{
		burst_size = ROUND_DOWN(TFA98XX_I2C_MAX_SIZE, 3);
		if (num_bytes < burst_size)
			burst_size = num_bytes;
		error = TFA98XX_ReadData(handle, FAM_TFA98XX_CF_MEM, burst_size, bytes + offset);
		if (error != kStatus_TFA98XX_Ok)
			return error;

		num_bytes -= burst_size;
		offset += burst_size;
	}

	return error;
}

#ifdef DEMO_VERBOSE
void printArray(char *ptr, size_t size)
{
    char *const end = ptr + size;
    while( ptr < end ) 
	{
        TFA98xx_Printf("[%x]-", *ptr++);
    }
}
#endif /* DEMO_VERBOSE */

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
                                    int vstep_msg_idx)
{
	status_t err = kStatus_TFA98XX_Ok;
	struct _tfa98xx_volumeStepRegisterInfo *regInfo = { 0 };
	struct _tfa98xx_volumeStepMessageInfo *msgInfo = { 0 };
	tfa98xx_Bitfield_t bitF;
	int msgLength = 0, i, j, size = 0, nrMessages, modified = 0;
	uint8_t cmdid_changed[3];

#ifdef DEMO_VERBOSE
	printArray((char *) vp, 50);
#endif
	if (vstep_idx >= vp->NrOfVsteps) 
	{
		TFA98xx_Printf("Volumestep %d is not available \r\n", vstep_idx);
		return kStatus_TFA98XX_Bad_Parameter;
	}
#ifdef DEMO_VERBOSE
	else
        TFA98xx_Printf("vp->NrOfVsteps:%d---vstep_idx %d--sizeof(TfaHeaderTfa98xx_t):%d\r\n", vp->NrOfVsteps, vstep_idx,
                       sizeof(tfa98xx_tfaheader_t));
#endif /* DEMO_VERBOSE */
	for (i = 0; i <= vstep_idx; i++) 
	{
		regInfo = (struct _tfa98xx_volumeStepRegisterInfo*) (vp->vstepsBin + size);
        msgInfo = (struct _tfa98xx_volumeStepMessageInfo *)(vp->vstepsBin + (regInfo->NrOfRegisters * sizeof(uint32_t) +
                                                                             sizeof(regInfo->NrOfRegisters) + size));

		nrMessages = msgInfo->NrOfMessages;
		TFA98xx_Printf("nrMessages:%d\r\n", nrMessages);
		for (j = 0; j < nrMessages; j++) 
		{
			/* location of message j, from vstep i */
			msgInfo =
					(struct _tfa98xx_volumeStepMessageInfo*) (vp->vstepsBin + (regInfo->NrOfRegisters * sizeof(uint32_t) +
									 sizeof(regInfo->NrOfRegisters) + size));
			/* message length */
			msgLength = ((msgInfo->MessageLength.b[0] << 16) + (msgInfo->MessageLength.b[1] << 8) + 
						msgInfo->MessageLength.b[2]);
			TFA98xx_Printf("nrMessages:%d--msgLength:%d--MessageType:%d\r\n", j, msgLength, msgInfo->MessageType);
			if (i == vstep_idx) 
			{
				/* If no vstepMsgIndex is passed on, all message needs to be send */
				if ((vstep_msg_idx >= TFA_MAX_VSTEP_MSG_MARKER) || (vstep_msg_idx == j)) 
				{
                    /*
                     * The algoparams and mbdrc msg id will be changed to the reset type when SBSL=0
                     * if SBSL=1 the msg will remain unchanged. It's up to the tuning engineer to choose the
                     * 'without_reset'
                     * types inside the vstep. In other words: the reset msg is applied during SBSL==0 else it remains
                     * unchanged.
                     */
					if (TFA98XX_ReadBitf(handle, TFA9894_BF_SBSL) == 0) 
					{
						if (msgInfo->MessageType == 0) 
						{ /* If the messagetype(0) is AlgoParams */
							TFA98xx_Printf("SBSL NULL MessageType NULL\r\n");
							/* Only do this when not set already */
							if (msgInfo->CmdId[2] != SB_PARAM_SET_ALGO_PARAMS) 
							{
								TFA98xx_Printf("CmdId[2] != SB_PARAM_SET_ALGO_PARAMS\r\n");
								cmdid_changed[0] = msgInfo->CmdId[0];
								cmdid_changed[1] = msgInfo->CmdId[1];
								cmdid_changed[2] = SB_PARAM_SET_ALGO_PARAMS;
								modified = 1;
							}
							else
								TFA98xx_Printf("CmdId[2] == SB_PARAM_SET_ALGO_PARAMS\r\n");
						} 
						else if (msgInfo->MessageType == 2) 
						{ 
							/* If the messagetype(2) is MBDrc */
							/* Only do this when not set already */
							TFA98xx_Printf("SBSL NULL MessageType 2-2-2\r\n");
							if (msgInfo->CmdId[2] != SB_PARAM_SET_MBDRC) 
							{
								TFA98xx_Printf("msgInfo->CmdId[2] != SB_PARAM_SET_MBDRC\r\n");
								cmdid_changed[0] = msgInfo->CmdId[0];
								cmdid_changed[1] = msgInfo->CmdId[1];
								cmdid_changed[2] = SB_PARAM_SET_MBDRC;
								modified = 1;
							}
							else
								TFA98xx_Printf("msgInfo->CmdId[2] == SB_PARAM_SET_MBDRC\r\n");
						}
					}
					else
						TFA98xx_Printf("SBSL TRUE--TRUE\r\n");
					/* Messagetype(3) is Smartstudio Info! Dont send this! */
					if (msgInfo->MessageType != 3) 
					{
						if (modified == 1) 
						{
							if (cmdid_changed[2] == SB_PARAM_SET_ALGO_PARAMS)
								TFA98xx_Printf("P-ID for SetAlgoParams modified!: ");
							else
								TFA98xx_Printf("P-ID for SetMBDrc modified!: ");

							TFA98xx_Printf("Command-ID used: 0x%02x%02x%02x \r\n", cmdid_changed[0], cmdid_changed[1],
									cmdid_changed[2]);
							/* Send payload to dsp (Remove 1 from the length for cmdid) */
							TFA98xx_Printf("Send Payload DSP :tfa_dsp_msg_id:((msgLength-1) * 3) %d:\r\n",
									(msgLength - 1) * 3);
							err = tfa98xx_dsp_msg_id(handle, (msgLength - 1) * 3, (const char *) msgInfo->ParameterData,
									cmdid_changed);
							if (err != kStatus_TFA98XX_Ok)
								return err;
						} 
						else 
						{
							/* Send cmdId + payload to dsp */
							TFA98xx_Printf("Send cmdId + payload to dsp :tfa_dsp_msg_id:(msgLength * 3) %d:\r\n",
									msgLength * 3);
							err = TFA98XX_DspWriteMsg(handle, msgLength * 3, (const char *) msgInfo->CmdId);
							/* dsp_msg(devs[0], msgLength * 3,(const char *)msgInfo->CmdId); */
							if (err != kStatus_TFA98XX_Ok)
								return err;
						}

						/* Set back to zero every time */
						modified = 0;
					}
				}
			}

			if (msgInfo->MessageType == 3) 
			{
				/* MessageLength is in bytes */
				size += sizeof(msgInfo->MessageType) + sizeof(msgInfo->MessageLength) + msgLength;
			} 
			else 
			{
				/* MessageLength is in words (3 bytes) */
				size += sizeof(msgInfo->MessageType) + sizeof(msgInfo->MessageLength) + sizeof(msgInfo->CmdId) + 
						((msgLength - 1) * 3);
			}
		}
		size += sizeof(regInfo->NrOfRegisters) + (regInfo->NrOfRegisters * sizeof(uint32_t)) + 
				sizeof(msgInfo->NrOfMessages);
	}

	if (regInfo->NrOfRegisters == 0) 
	{
		TFA98xx_Printf("No registers in selected vstep (%d)!\r\n", vstep_idx);
		return kStatus_TFA98XX_Bad_Parameter;
	}

	for (i = 0; i < regInfo->NrOfRegisters * 2; i++) 
	{
		/* Byte swap the datasheetname */
		bitF.field = (uint16_t) (regInfo->registerInfo[i] >> 8) | (regInfo->registerInfo[i] << 8);
		i++;
		bitF.value = (uint16_t) regInfo->registerInfo[i] >> 8;
		TFA98xx_Printf("bitF.field:%x--bitF.value:%x\r\n", bitF.field, bitF.value);
		err = tfaRunWriteBitfieldTfa98xx(handle, bitF);
		if (err != kStatus_TFA98XX_Ok)
			return err;
	}
	return err;
}

/*!
 * @brief Read calibrated speaker impedance value from DSP
 * @param handle TFA98xx codec handle.
 * @param pRe25 Impedance value read from DSP
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_DspGetCalibrationImpedance(tfa98xx_handle_t *handle, float *pRe25)
{
	status_t error = kStatus_TFA98XX_Ok;
	int spkr_count = 1, nr_bytes, i;
	uint8_t bytes[6] = { 0 };
	int data[2];

	nr_bytes = spkr_count * 3;
	if (TFA98XX_ReadBitf(handle, TFA9894_BF_MTPOTC))
	{
		*pRe25 = (TFA98XX_ReadBitf(handle, TFA9894_BF_R25C) * 1000) / 1024;
	} 
	else 
	{
		error = tfa98xx_dsp_cmd_id_write_read(handle, MODULE_SPEAKERBOOST, SB_PARAM_GET_RE0, nr_bytes, bytes);
		if (error == kStatus_TFA98XX_Ok) 
		{
			tfa98xx_convert_bytes2data(nr_bytes, bytes, data);
			for (i = 0; i < spkr_count; i++) 
			{
				*pRe25 = (data[i] * 1024) / TFA2_FW_ReZ_SCALE;
			}
		}
		else 
		{
			for (i = 0; i < spkr_count; i++)
				*pRe25 = -1;
		}
	}

	return error;
}

/*!
 * @brief Wait until calibration done
 * @param calibrateDone 1 if calibratione successfully done, otherwise calibration fail
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_WaitCalibrateDone(tfa98xx_handle_t *handle, int *calibrateDone)
{
	status_t err = kStatus_TFA98XX_Ok;
	int tries = 0, mtp_busy = 1, tries_mtp_busy = 0;
	int i;

	*calibrateDone = 0;

	/* in case of calibrate once wait for MTPEX */
	if (TFA98XX_ReadBitf(handle, TFA9894_BF_MTPOTC)) 
	{
		/* Check if MTP_busy is clear */
		while (tries_mtp_busy < 50) 
		{
			mtp_busy = TFA98XX_ReadBitf(handle, TFA9894_BF_MTPB);
			if (mtp_busy == 1)
				for (i = 0; i < 0xfff; i++)
					; /*msleep_interruptible(10);  wait 10ms to avoid busload */
			else
				break;
			tries_mtp_busy++;
		}

		if (tries_mtp_busy < 50) 
		{
			/* Because of the msleep TFA98XX_API_WAITRESULT_NTRIES is way to long!
			 * Setting this to 25 will take it atleast 25*50ms = 1.25 sec
			 */
			while ((*calibrateDone == 0) && (tries < 50)) 
			{
				*calibrateDone = TFA98XX_ReadBitf(handle, TFA9894_BF_MTPEX);
				if (*calibrateDone == 1)
					break;
				for (i = 0; i < 0xfff; i++)
					; /* msleep_interruptible(50); wait 50ms to avoid busload */
				tries++;
			}

			if (tries >= 50) 
			{
				tries = 3000;
			}
		}
		else 
		{
			TFA98xx_Printf("MTP bussy after %d tries\r\n", 50);
		}
	}

	/* poll xmem for calibrate always
	 * calibrateDone = 0 means "calibrating",
	 * calibrateDone = -1 (or 0xFFFFFF) means "fails"
	 * calibrateDone = 1 means calibration done
	 */
	while ((*calibrateDone != 1) && (tries < 3000)) 
	{
		err = tfa98xx_dsp_read_mem(handle, 516, 1, calibrateDone);
		tries++;
	}

	if (*calibrateDone != 1) 
	{
		TFA98xx_Printf("Calibration failed! \r\n");
		err = kStatus_TFA98XX_Bad_Parameter;
	} 
	else if (tries == 3000) 
	{
		TFA98xx_Printf("Calibration has timedout! \r\n");
		err = kStatus_TFA98XX_StateTimedOut;
	} 
	else if (tries_mtp_busy == 1000) 
	{
		TFA98xx_Printf("Calibrate Failed: MTP_busy stays high! \r\n");
		err = kStatus_TFA98XX_StateTimedOut;
	}
	return err;
}

/*!
 * @brief Clear Calibrate Once
 *
 * This function unset Calibrate Once and set Calibrate Always by manually clearing MTPEX and MTPOTC.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_ClearCalibrateOnce(tfa98xx_handle_t *handle)
{
	status_t err = kStatus_TFA98XX_Ok;
	uint16_t mtp;
	int tries=0, mtpBusy=0;

	/* Unlock MTP register by writing 0x005A to register 0x0B */
	err = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_OPENMTP,1);
	assert(err == kStatus_TFA98XX_Ok);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0x5A6B);
	TFA98XX_WriteRegister(handle, 0xA1,(uint16_t)0x005A);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0);

	/* Read MTP register */
	TFA98XX_ReadRegister(handle, 0xF0, &mtp);

	/* Set MTPEX=0 and MTPOTC=0 to clear current calibration status */
	mtp &= ~(0x03);
	err = TFA98XX_WriteRegister(handle, 0xF0, mtp);
	assert(err == kStatus_TFA98XX_Ok);
	tfa2_manual_mtp_cpy(handle, 0xF1, mtp, 0);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0x5A6B);
	TFA98XX_WriteRegister(handle, 0xA1,(uint16_t)0);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0);
	assert(err == kStatus_TFA98XX_Ok);
	do
	{
		tries++;
		mtpBusy = TFA98XX_ReadBitf(handle, TFA9894_BF_MTPB);
	} while ((mtpBusy == 0x01) && (tries < TFA98XX_API_WAITRESULT_NTRIES));

	if (tries==TFA98XX_API_WAITRESULT_NTRIES)
	{
		TFA98xx_Printf("MTP Busy timedout\r\n");
		err = kStatus_TFA98XX_StateTimedOut;
	}
	return err;
}

#ifdef FACTORY_CALIBRATION_ONLY
/*!
 * @brief Set Calibrate Once
 *
 * This function set Calibrate Once by manually set MTPOTC and trigger calibration.
 *
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_SetCalibrateOnce(tfa98xx_handle_t *handle)
{
	status_t err = kStatus_TFA98XX_Ok;

	uint16_t mtp;
	int tries=0, mtpBusy=0;

	err = TFA98XX_WriteBitfVolitale(handle,TFA9894_BF_OPENMTP,1);
	assert(err == kStatus_TFA98XX_Ok);
	/* Unlock MTP register by writing 0x005A to register 0x0B */
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0x5A6B);
	TFA98XX_WriteRegister(handle, 0xA1,(uint16_t)0x005A);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0);
	TFA98XX_ReadRegister(handle, 0xF0, &mtp);
	/* Clear MTPEX */
	mtp |=0x01;
	err = TFA98XX_WriteRegister(handle, 0xF0, mtp);
	assert(err == kStatus_TFA98XX_Ok);
	tfa2_manual_mtp_cpy(handle, 0xF1, mtp, 0);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0x5A6B);
	TFA98XX_WriteRegister(handle, 0xA1,(uint16_t)0);
	TFA98XX_WriteRegister(handle, 0x0F,(uint16_t)0);
	tries = 0;
	do
	{
		tries++;
		mtpBusy = TFA98XX_ReadBitf(handle, TFA9894_BF_MTPB);
	} while ((mtpBusy == 0x01) && (tries < TFA98XX_API_WAITRESULT_NTRIES));

	if (tries==TFA98XX_API_WAITRESULT_NTRIES)
	{
		TFA98xx_Printf("MTP Busy timedout\r\n");
		err = kStatus_TFA98XX_StateTimedOut;
	}
	return err;
}
#endif /* FACTORY_CALIBRATION_ONLY */

/*!
 * @brief Printe Calibrated impedance
 * @param handle TFA98xx codec handle.
 * @return Returns @ref kStatus_TFA98XX_Ok if success, otherwise returns error code.
 */
status_t TFA98XX_PrintCalibration(tfa98xx_handle_t *handle)
{
	status_t error = kStatus_TFA98XX_Ok;
	uint8_t bytes[6] = {0};
	int24 data[2];
	float mohm = 0.0;

	error = tfa98xx_dsp_cmd_id_write_read(handle, MODULE_SPEAKERBOOST, SB_PARAM_GET_RE0, 3, bytes);
	assert(error == kStatus_TFA98XX_Ok);

	if (error == kStatus_TFA98XX_Ok) 
	{
		tfa98xx_convert_bytes2data(3, bytes, data);
		mohm = ((float)data[0]*1024)/TFA2_FW_ReZ_SCALE;
	}
	TFA98xx_Printf("Calibrated value :%1.2f mOhms :\r\n",mohm);

	return error;
}

/*******************************************************************************
 * Static functions
 ******************************************************************************/
static status_t tfa98xx_dsp_read_mem(tfa98xx_handle_t *handle, unsigned int start_offset, int num_words, int *pValues)
{
	status_t  error = kStatus_TFA98XX_Ok;
	uint8_t *bytes;
	int burst_size;		/* number of words per burst size */
	const int bytes_per_word = 3;
	int dmem;
	int num_bytes;
	int *p;

	bytes = (uint8_t *)malloc(num_words*bytes_per_word);
	if (bytes == NULL)
		return kStatus_TFA98XX_Other;

	/* If no offset is given, assume XMEM! */
	if(((start_offset>>16) & 0xf) > 0 )
		dmem = (start_offset>>16) & 0xf;
	else
		dmem = DMEM_XMEM;

	/* Remove offset from adress */
	start_offset = start_offset & 0xffff;
	num_bytes = num_words * bytes_per_word;
	p = pValues;

	TFA98XX_WriteBitfVolitale(handle, TFA9894_BF_DMEM, (uint16_t)dmem);
	error = -TFA98XX_WriteBitf(handle, TFA9894_BF_MADD, (uint16_t)start_offset);
	if (error != kStatus_TFA98XX_Ok)
		goto tfa98xx_dsp_read_mem_exit;
	for (; num_bytes > 0;) 
	{
		burst_size = ROUND_DOWN(TFA98XX_I2C_MAX_SIZE, bytes_per_word);
		if (num_bytes < burst_size)
			burst_size = num_bytes;
		assert(burst_size <= sizeof(bytes));
		error = TFA98XX_ReadData(handle, FAM_TFA98XX_CF_MEM, burst_size, bytes);
		if (error != kStatus_TFA98XX_Ok)
			goto tfa98xx_dsp_read_mem_exit;

		tfa98xx_convert_bytes2data(burst_size, bytes, p);

		num_bytes -= burst_size;
		p += burst_size / bytes_per_word;
	}

tfa98xx_dsp_read_mem_exit:
	free(bytes);
	return error;
}

static void tfa98xx_convert_data2bytes(int num_data, const int data[], uint8_t bytes[])
{
    int i;            /* index for data */
    int k;            /* index for bytes */
    int d;
    /* note: cannot just take the lowest 3 bytes from the 32 bit
     * integer, because also need to take care of clipping any
     * value > 2&23 */
    for (i = 0, k = 0; i < num_data; ++i, k += 3) 
	{
        if (data[i] >= 0)
            d = MIN(data[i], (1 << 23) - 1);
        else 
		{
            /* 2's complement */
            d = (1 << 24) - MIN(-data[i], 1 << 23);
        }
        bytes[k] = (d >> 16) & 0xFF;    /* MSB */
        bytes[k + 1] = (d >> 8) & 0xFF;
        bytes[k + 2] = (d) & 0xFF;    /* LSB */
    }
}

/**
 convert memory bytes to signed 24 bit integers
   input:  bytes contains "num_bytes" byte elements
   output: data contains "num_bytes/3" int24 elements
*/
static void tfa98xx_convert_bytes2data(int num_bytes, const uint8_t bytes[], int data[])
{
    int i;            /* index for data */
    int k;            /* index for bytes */
    int d;
    int num_data = num_bytes / 3;
    assert((num_bytes % 3) == 0);
    for (i = 0, k = 0; i < num_data; ++i, k += 3) 
	{
        d = (bytes[k] << 16) | (bytes[k + 1] << 8) | (bytes[k + 2]);
        assert(d >= 0);
        assert(d < (1 << 24));    /* max 24 bits in use */
        if (bytes[k] & 0x80)    /* sign bit was set */
            d = -((1 << 24) - d);

        data[i] = d;
    }
}

static status_t  tfa98xx_dsp_msg_id(tfa98xx_handle_t *handle, int length, const char *buf, uint8_t cmdid[3])
{
	status_t error;
	int tries, rpc_status = kStatus_Success;

	/* write the message and notify the DSP */
	error = tfa98xx_dsp_msg_write_id(handle, length, buf, cmdid);
	if( error != kStatus_TFA98XX_Ok)
	{
		TFA98xx_Printf("Return error-----error\r\n");
		return error;
	}
	/* get the result from the DSP (polling) */
	for(tries=40; tries>0;tries--) 
	{
		error = tfa98xx_dsp_msg_status(handle, &rpc_status);
                if (error == kStatus_TFA98XX_Ok && rpc_status == kStatus_Success)
			break;
	}
	if (rpc_status != kStatus_Success) 
	{
		/* DSP RPC call returned an error */
		error = (status_t) (rpc_status + kStatus_TFA98XX_RpcBase);
	}

	return error;
}

static status_t  tfa98xx_dsp_msg_write_id(tfa98xx_handle_t *handle, int length, const char *buffer, uint8_t cmdid[3])
{
	int offset = 0;
	int chunk_size = ROUND_DOWN(TFA98XX_I2C_MAX_SIZE, 3 /* XMEM word size */ );

	int remaining_bytes = length;
	status_t error = kStatus_TFA98XX_Ok;
	uint16_t cfctl;

	error = TFA98XX_ReadRegister(handle, (TFA9894_BF_DMEM >> 8), &cfctl);
	if (error != kStatus_TFA98XX_Ok) {
		return error;
	}
	/* assume no I2C errors from here */
	TFA98XX_WriteBitfValue(TFA9894_BF_DMEM, (uint16_t)DMEM_XMEM, &cfctl); /* set cf ctl to DMEM  */
	TFA98XX_WriteBitfValue(TFA9894_BF_AIF, 0, &cfctl ); /* set to autoincrement */
	TFA98XX_WriteRegister(handle, (TFA9894_BF_DMEM >> 8), cfctl);
	/* xmem[1] is start of message
	*  direct write to register to save cycles avoiding read-modify-write
	*/
	TFA98XX_WriteRegister(handle, (TFA9894_BF_MADD >> 8), 1);
	/* write cmd-id */
	if(cmdid != NULL)
	error = TFA98XX_WriteData(handle, FAM_TFA98XX_CF_MEM, 3, (const uint8_t *)cmdid);

	/* due to autoincrement in cf_ctrl, next write will happen at
	* the next address */
	while ((error == kStatus_TFA98XX_Ok) && (remaining_bytes > 0)) 
	{
		if (remaining_bytes < chunk_size)
			chunk_size = remaining_bytes;
		/* else chunk_size remains at initialize value above */
		error = TFA98XX_WriteData(handle, FAM_TFA98XX_CF_MEM, chunk_size, (const uint8_t *)buffer + offset);
		remaining_bytes -= chunk_size;
		offset += chunk_size;
	}

	/* notify the DSP */
	if (error == kStatus_TFA98XX_Ok) 
	{
		TFA98xx_Printf("Probably here 70 71 72, flow__Flow\r\n");
		/* cf_int=0, cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
		/* set the cf_req1 and cf_int bit */
		TFA98XX_WriteBitfValue(TFA9894_BF_REQCMD, 0x01, &cfctl ); /* bit 0 */
		TFA98XX_WriteBitfValue(TFA9894_BF_CFINT, 1, &cfctl );
		error = TFA98XX_WriteRegister(handle, (TFA9894_BF_DMEM >> 8), cfctl);
	}

	return error;
}

static status_t tfa98xx_wait_result(tfa98xx_handle_t *handle, int wait_retry_count)
{
	status_t  error = kStatus_TFA98XX_Ok;
	int cf_status; /* the contents of the CF_STATUS register */
	int tries = 0;
	do 
	{
		cf_status = TFA98XX_ReadBitf(handle,TFA2_BF_ACK);
		if (cf_status < 0)
			error = -cf_status;
		tries++;
#ifdef TFA98XX_PRINT_DEBUG
		TFA98xx_Printf("%s,triesCF=%d Error=%d cf_status & 0x01=%d\r\n",__FUNCTION__, tries,error,cf_status & 0x01);
#endif /* TFA98XX_PRINT_DEBUG */
	}
	/* i2c_cmd_ack */
	/* don't wait forever, DSP is pretty quick to respond (< 1ms) */
	while ((error == kStatus_TFA98XX_Ok) && ((cf_status & 0x01) == 0) && (tries < wait_retry_count));
	if (tries >= wait_retry_count) 
	{
#ifdef TFA98XX_PRINT_DEBUG
		TFA98xx_Printf("Returning Error_DSP_not_running\r\n");
#endif /* TFA98XX_PRINT_DEBUG */
		/* something wrong with communication with DSP */
		error = kStatus_TFA98XX_DSP_not_running;
	}
	return error;
}

/* read the return code for the RPC call */
static status_t tfa98xx_check_rpc_status(tfa98xx_handle_t *handle, int *pRpcStatus)
{
	status_t  error = kStatus_TFA98XX_Ok;
	/* the value to sent to the * CF_CONTROLS register: cf_req=00000000,
	 * cf_int=0, cf_aif=0, cf_dmem=XMEM=01, cf_rst_dsp=0 */
	uint16_t cf_ctrl = 0x0002;
	/* memory address to be accessed (0: Status, 1: ID, 2: parameters) */
	uint16_t cf_mad = 0x0000;
	if (pRpcStatus == 0)
		return kStatus_TFA98XX_Bad_Parameter;
	/* 1) write DMEM=XMEM to the DSP XMEM */
	{
		/* minimize the number of I2C transactions by making use of the autoincrement in I2C */
		uint8_t buffer[4];
		/* first the data for CF_CONTROLS */
		buffer[0] = (uint8_t)((cf_ctrl >> 8) & 0xFF);
		buffer[1] = (uint8_t)(cf_ctrl & 0xFF);
		/* write the contents of CF_MAD which is the subaddress following CF_CONTROLS */
		buffer[2] = (uint8_t)((cf_mad >> 8) & 0xFF);
		buffer[3] = (uint8_t)(cf_mad & 0xFF);
		error = TFA98XX_WriteData(handle, FAM_TFA98XX_CF_CONTROLS, sizeof(buffer), buffer);
	}
	if (error == kStatus_TFA98XX_Ok) 
	{
		/* read 1 word (24 bit) from XMEM */
		error = tfa98xx_dsp_read_mem(handle, 0, 1, pRpcStatus);
	}
	return error;
}

static status_t tfa98xx_dsp_msg_status(tfa98xx_handle_t *handle, int *pRpcStatus)
{
	status_t error = kStatus_TFA98XX_Ok;

	error = tfa98xx_wait_result(handle, 10); /* 2 is only one try */
	if (error == kStatus_TFA98XX_DSP_not_running) 
	{
		TFA98xx_Printf("DSP is not running\r\n");
		*pRpcStatus = -1;
		return kStatus_TFA98XX_Ok;
	}
	else if (error != kStatus_TFA98XX_Ok)
	{
		TFA98xx_Printf("Error NOK:%d\r\n",error);
		return error;
	}
	error = tfa98xx_check_rpc_status(handle, pRpcStatus);
	TFA98xx_Printf("rpcStatus:%d\r\n",*pRpcStatus);
	return error;
}

static status_t tfa98xx_dsp_cmd_id_write_read(
    tfa98xx_handle_t *handle, uint8_t module_id, uint8_t param_id, int num_bytes, uint8_t data[])
{
	status_t error;
	uint8_t buffer[3];

	buffer[0] = 1;
	buffer[1] = module_id + 128;
	buffer[2] = param_id;


	error = TFA98XX_DspWriteMsg(handle, sizeof(uint8_t[3]), (const char *)buffer);
	if (error != kStatus_TFA98XX_Ok)
		return error;

	/* read the data from the dsp */
	error = TFA98XX_DspReadMsg(handle, num_bytes, data);
	return error;
}

static status_t  tfaRunWriteBitfieldTfa98xx(tfa98xx_handle_t *handle,  tfa98xx_Bitfield_t bf)
{
	status_t error;
        uint16_t value;
	union 
	{
		uint16_t field;
		tfa98xx_BfEnum_t Enum;
	} bfUni;

	value=bf.value;
	bfUni.field = bf.field;
    error = TFA98XX_WriteBitfVolitale(handle, bfUni.field, value);

	return error;
}

/* Adjust MTP writing sequence and adding manual copy support */
static void tfa2_manual_mtp_cpy(tfa98xx_handle_t *handle,
                                uint16_t reg_row_to_keep,
                                uint16_t reg_row_to_set,
                                uint8_t row)
{
	uint16_t value;

	//printf("tfa2_manual_mtp_cpy\n");
	TFA98XX_ReadRegister(handle, (uint8_t)reg_row_to_keep, &value);
	if(!row)
	{
		TFA98XX_WriteRegister(handle, 0xA7 , value);
		TFA98XX_WriteRegister(handle, 0xA8 , reg_row_to_set);
	}
	else
	{
		TFA98XX_WriteRegister(handle, 0xA7 , reg_row_to_set);
		TFA98XX_WriteRegister(handle, 0xA8 , value);
	}
	TFA98XX_WriteRegister(handle, 0xA3 , 0x10 | row);
}
