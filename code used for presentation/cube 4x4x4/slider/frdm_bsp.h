/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file frdm_bsp.h
 * @author skoryci
 * @date Oct 2019
 * @brief File containing info about evaluation board used in project.
 */

#ifndef FRDM_BSP_H
#define FRDM_BSP_H

//#define DEBUG
#define FRDM_KL46Z       										/* define eval used in project */

#ifndef TRUE
# define TRUE        (1)
#endif

#ifndef	FALSE
# define FALSE       (0)
#endif

#define SYSTEM_CLOCK  SystemCoreClock
#define BUS_CLOCK     SYSTEM_CLOCK/2

#define MASK(x)		(uint32_t) (1UL << (x))   /* turn bit number into 32b mask */
#define DELAY(x)   for(int i=0;i<(x*BUS_CLOCK/3000);i++){}; /* wait */

#ifdef FRDM_KL05Z
# include "MKL05Z4.h"                       /* header with CMSIS */
#endif /* FRDM_KL05Z */

#ifdef FRDM_KL25Z
# include "MKL25Z4.h"                       /* header with CMSIS */
#endif /* FRDM_KL05Z */

#ifdef FRDM_KL46Z
# include "MKL46Z4.h"                       /* header with CMSIS */
#endif /* FRDM_KL46Z */

	
#endif /* FRDM_BSP_H */
