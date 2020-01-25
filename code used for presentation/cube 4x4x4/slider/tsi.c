/******************************************************************************
 * This file is a part of the Sysytem Microprocessor Tutorial (C).            *
 ******************************************************************************/

/**
 * @file tsi.c
 * @author skoryci
 * @date Oct 2019
 * @brief File containing definitions.
 */

#include "tsi.h"

uint8_t elec_array[16]={ELECTRODE0,ELECTRODE1};
uint16_t gu16TSICount[16];
uint16_t gu16Baseline[16];
uint16_t gu16Threshold[16]={THRESHOLD0,THRESHOLD1};
uint16_t gu16Delta[16];
uint8_t ongoing_elec;

uint8_t end_flag = TRUE;

void TSI_SelfCalibration(void)
{
  unsigned char cnt;
  unsigned char trigger_backup;
  
  TSI0->GENCS |= TSI_GENCS_EOSF_MASK;      // Clear End of Scan Flag 
  TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module
  
  if(TSI0->GENCS & TSI_GENCS_STM_MASK)     // Back-up TSI Trigger mode from Application 
       trigger_backup = TRUE;
  else
       trigger_backup = FALSE;
  
  TSI0->GENCS &= ~TSI_GENCS_STM_MASK;      // Use SW trigger
  TSI0->GENCS &= ~TSI_GENCS_TSIIEN_MASK;    // Enable TSI interrupts
  
  TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module
  
  for(cnt=0; cnt < TOTAL_ELECTRODE; cnt++)  // Get Counts when Electrode not pressed
  {
    TSI0->DATA = ((elec_array[cnt] << TSI_DATA_TSICH_SHIFT) );
    TSI0->DATA |= TSI_DATA_SWTS_MASK;
    while(!(TSI0->GENCS & TSI_GENCS_EOSF_MASK));
    TSI0->GENCS |= TSI_GENCS_EOSF_MASK;
    gu16Baseline[cnt] = (TSI0->DATA & TSI_DATA_TSICNT_MASK); 
  }
  
  TSI0->GENCS &= ~TSI_GENCS_TSIEN_MASK;    // Disable TSI module
  TSI0->GENCS |= TSI_GENCS_TSIIEN_MASK;     // Enable TSI interrupt
  if(trigger_backup)                      // Restore trigger mode
    TSI0->GENCS |= TSI_GENCS_STM_MASK;
  else
    TSI0->GENCS &= ~TSI_GENCS_STM_MASK;
  
  TSI0->GENCS |= TSI_GENCS_TSIEN_MASK;     // Enable TSI module
  
   TSI0->DATA = ((elec_array[0]<<TSI_DATA_TSICH_SHIFT) );
   TSI0->DATA |= TSI_DATA_SWTS_MASK;
}

void TSI_Init (void)
{
  SIM->SCGC5 |= SIM_SCGC5_TSI_MASK | SIM_SCGC5_PORTB_MASK;  // Enable clock gating for TSI
  
  PORTB->PCR[16] = PORT_PCR_MUX(0);   // TSI channel 9
  PORTB->PCR[17] = PORT_PCR_MUX(0);   // TSI channel 10

  TSI0->GENCS  |= (TSI_GENCS_ESOR_MASK
               | TSI_GENCS_MODE(0)
               | TSI_GENCS_REFCHRG(4)
               | TSI_GENCS_DVOLT(0)
               | TSI_GENCS_EXTCHRG(7)  
               | TSI_GENCS_PS(4)
               | TSI_GENCS_NSCN(11)
               | TSI_GENCS_TSIIEN_MASK 
               | TSI_GENCS_STPE_MASK
               //| TSI_GENCS_STM_MASK     //Trigger for the module 0=Sofware 
               );
  
  TSI0->GENCS |= TSI_GENCS_TSIEN_MASK; 

  NVIC_ClearPendingIRQ(TSI0_IRQn);
  NVIC_EnableIRQ(TSI0_IRQn);
  
  TSI_SelfCalibration();
}

uint8_t TSI_ReadSlider (void)
{
  uint8_t a = 0;
  uint8_t b = 0;

  if(end_flag)
  {
    end_flag = FALSE;
    if((gu16Delta[0] > gu16Threshold[0]) || (gu16Delta[1] > gu16Threshold[1]))
    {
      a = (gu16Delta[0]*100)/(gu16Delta[0]+gu16Delta[1]);
      b = (gu16Delta[1]*100)/(gu16Delta[0]+gu16Delta[1]);
      return ((100 - a) + b)/2;
    }
    else return 0;
  }
  else return 0;
}

void change_electrode(void)
{
  int16_t u16temp_delta;

  gu16TSICount[ongoing_elec] = (TSI0->DATA & TSI_DATA_TSICNT_MASK);         // Save Counts for current electrode
  u16temp_delta = gu16TSICount[ongoing_elec] - gu16Baseline[ongoing_elec];  // Obtains Counts Delta from callibration reference
  if( u16temp_delta < 0)
    gu16Delta[ongoing_elec] = 0;
  else
    gu16Delta[ongoing_elec] = u16temp_delta;

  if(TOTAL_ELECTRODE > 1)  //Change Electrode to Scan
  {
    if((TOTAL_ELECTRODE-1) > ongoing_elec) ongoing_elec++;
    else   ongoing_elec = 0;
    
    TSI0->DATA = ((elec_array[ongoing_elec]<<TSI_DATA_TSICH_SHIFT));
    TSI0->DATA |= TSI_DATA_SWTS_MASK; 
  }
}

void TSI0_IRQHandler(void)
{
  end_flag = TRUE;
  TSI0->GENCS |= TSI_GENCS_EOSF_MASK; // Clear End of Scan Flag
  change_electrode();
}
