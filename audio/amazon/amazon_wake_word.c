// ############################################################################
// #             Copyright (C), NXP Semiconductors
// #                       (C), NXP B.V. of Eindhoven
// #
// # All rights are reserved. Reproduction in whole or in part is prohibited
// # without the written consent of the copyright owner.
// # NXP reserves the right to make changes without notice at any time.
// # NXP makes no warranty, expressed, implied or statutory, including but
// # not limited to any implied warranty of merchantability or fitness for
// # any particular purpose, or that the use will not infringe any third
// # party patent, copyright or trademark. NXP must not be liable for any
// # loss or damage arising from its use.
// ############################################################################

/* FreeRTOS kernel includes. */
#include "board.h"
/* Freescale includes. */
#include "fsl_debug_console.h"
#include "pdm_pcm_definitions.h"
#include "pryon_lite.h"
#include "audio_samples.h"
#include "amazon_wake_word.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define PRL_MODEL_ALIGN __attribute__((aligned(16)))
/*******************************************************************************
 * Global Vars
 ******************************************************************************/

PryonLiteDecoderConfig config = PryonLiteDecoderConfig_Default;
PryonLiteModelAttributes modelAttributes;
static PryonLiteDecoderHandle sDecoder = NULL;

uint8_t * pu8WakeupDetected = NULL;
uint16_t * pu8WakeupSize = NULL;

char* decoderBuffer = NULL; // should be an array large enough to hold the largest decoder

// initialize decoder
PryonLiteSessionInfo sessionInfo;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void SLN_AMAZON_WAKE_SetWakeupDetectedParams(uint8_t *pu8Wake, uint16_t *pu16WWLen) {
	pu8WakeupDetected = pu8Wake;
	pu8WakeupSize = pu16WWLen;
}

static void loadModel(PryonLiteDecoderConfig* config)
{
    // In order to detect keywords, the decoder uses a model which defines the parameters,
    // neural network weights, classifiers, etc that are used at runtime to process the audio
    // and give detection results.

    // Each model is packaged in two formats:
    // 1. A .bin file that can be loaded from disk (via fopen, fread, etc)
    // 2. A .cpp file that can be hard-coded at compile time

    config->sizeofModel = sizeof(prlBinaryModelData); // example value, will be the size of the binary model byte array
    config->model = &prlBinaryModelData[0]; // pointer to model in memory
}

// keyword detection callback
static void detectionCallback(PryonLiteDecoderHandle handle, const PryonLiteResult* result)
{
	*pu8WakeupDetected = (0 == strcmp(result->keyword, "ALEXA") ? 1 : 0);
	*pu8WakeupSize = ((result->endSampleIndex - result->beginSampleIndex) / 160);
}

// VAD event callback
static void vadCallback(PryonLiteDecoderHandle handle, const PryonLiteVadEvent* vadEvent)
{
    //printf("VAD state %d\n", (int) vadEvent->vadState);
}

uint32_t SLN_AMAZON_WAKE_Initialize()
{
    loadModel(&config);

    // Query for the size of instance memory required by the decoder
    PryonLiteError err = PryonLite_GetModelAttributes(config.model, config.sizeofModel, &modelAttributes);

    config.decoderMem = pvPortMalloc(modelAttributes.requiredDecoderMem);

    if (config.decoderMem == NULL) {
    	while(1);
    }

    config.sizeofDecoderMem = modelAttributes.requiredDecoderMem;

    config.detectThreshold = 500; // default threshold
    config.resultCallback = detectionCallback; // register detection handler
    config.vadCallback = vadCallback; // register VAD handler
    config.useVad = 1;  // enable voice activity detector

    sessionInfo.samplesPerFrame = 160;  // enable voice activity detector

    err = PryonLiteDecoder_Initialize(&config, &sessionInfo, &sDecoder);

    if (err != PRYON_LITE_ERROR_OK)
    {
        // Set detection threshold for all keywords (this function can be called any time after decoder initialization)
        int detectionThreshold = 500;
        err = PryonLiteDecoder_SetDetectionThreshold(sDecoder, NULL, detectionThreshold);

    }

    return err;
}

uint32_t SLN_AMAZON_WAKE_ProcessWakeWord(int16_t * pi16AudioBuff,
                                 uint16_t u16BufferSize) {
	PryonLiteError err;

	uint16_t u16Bytes = 0;

	err = PryonLiteDecoder_PushAudioSamples(sDecoder, pi16AudioBuff, sessionInfo.samplesPerFrame);

	return err;
}
