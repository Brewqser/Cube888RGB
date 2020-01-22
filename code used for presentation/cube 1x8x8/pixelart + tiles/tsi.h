/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file tsi.h
 * @author skoryci
 * @date Oct 2019
 * @brief File containing enums, structures and declarations.
 */

#ifndef TSI_H
#define TSI_H

#include "frdm_bsp.h"
//#include "led.h"

#define SLIDER_LENGTH         40 // in mm
#define TOTAL_ELECTRODE       2

#define ELECTRODE0   9
#define ELECTRODE1   10

#define THRESHOLD0   100
#define THRESHOLD1   100

/**
 * @brief Initialization
 */
void TSI_Init(void);
/**
 * @brief Self Calibration
 */
void TSI_SelfCalibration(void);
/**
 * @brief Simple Read
 */
uint8_t TSI_ReadSlider (void);

#endif /* TSI_H */
