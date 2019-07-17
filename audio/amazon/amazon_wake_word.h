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

#ifndef _AMAZON_WAKE_WORD_H_
#define _AMAZON_WAKE_WORD_H_

#include "ulpww_250k.en-US.alexa.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

uint32_t SLN_AMAZON_WAKE_ProcessWakeWord(int16_t * pi16AudioBuff, uint16_t u16BufferSize);
uint32_t SLN_AMAZON_WAKE_Initialize();
void SLN_AMAZON_WAKE_SetWakeupDetectedParams(uint8_t *pu8Wake, uint16_t *pu16WWLen);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _AMAZON_WAKE_WORD_H_ */

/*******************************************************************************
 * API
 ******************************************************************************/
