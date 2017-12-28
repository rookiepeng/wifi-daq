/****************************************************************************************
//    Copyright (C) 2017  Zhengyu Peng, zhengyu.peng@ttu.edu
*****************************************************************************************/

#include <stddef.h>

#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_adc.h"
#include "hw_udma.h"

#include "rom_map.h"
#include "prcm.h"

#include "adc.h"
#include "udma.h"
#include "gpio.h"

#include "udma_if.h"
#include "gpio_if.h"
#ifndef NOTERM
#include "uart_if.h"
#endif
#include "common.h"

#include "adc_conf.h"
#include "app_conf.h"
#include "tcpudp.h"

//unsigned short g_ucADCCH0BuffPRI[ADC_BUFF_SIZE];
//unsigned short g_ucADCCH0BuffALT[ADC_BUFF_SIZE];

//unsigned short g_ucADCCH1BuffPRI[ADC_BUFF_SIZE];
//unsigned short g_ucADCCH1BuffALT[ADC_BUFF_SIZE];

unsigned short g_ucADCCH2BuffPRI[ADC_BUFF_SIZE];
unsigned short g_ucADCCH2BuffALT[ADC_BUFF_SIZE];

//unsigned short g_ucADCCH3BuffPRI[ADC_BUFF_SIZE];
//unsigned short g_ucADCCH3BuffALT[ADC_BUFF_SIZE];

char ADCSeg1[ADC_BUFF_SIZE], ADCSeg0[ADC_BUFF_SIZE];

char stopAdc;

void AdcStart()
{
    unsigned short Status;
    stopAdc = 0;

    UDMAInit();
    MAP_ADCIntRegister(ADC_BASE, ADC_CH_2, ADCIntHandler);

    // CH0
    /*MAP_uDMAChannelAssign(UDMA_CH14_ADC_CH0);
    UDMASetupTransfer(UDMA_CH14_ADC_CH0 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel0FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH0BuffPRI), UDMA_DST_INC_16);

    UDMASetupTransfer(UDMA_CH14_ADC_CH0 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel0FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH0BuffALT), UDMA_DST_INC_16);

    // CH1
    MAP_uDMAChannelAssign(UDMA_CH15_ADC_CH1);
    UDMASetupTransfer(UDMA_CH15_ADC_CH1 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel2FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH1BuffPRI), UDMA_DST_INC_16);

    UDMASetupTransfer(UDMA_CH15_ADC_CH1 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel2FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH1BuffALT), UDMA_DST_INC_16);*/

    // CH2
    MAP_uDMAChannelAssign(UDMA_CH16_ADC_CH2);
    UDMASetupTransfer(UDMA_CH16_ADC_CH2 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel4FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH2BuffPRI), UDMA_DST_INC_16);

    UDMASetupTransfer(UDMA_CH16_ADC_CH2 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      //(void *)(0x4402E874 + ADC_CH_2), UDMA_SRC_INC_NONE,
                      (void *)(ADC_BASE + ADC_O_channel4FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH2BuffALT), UDMA_DST_INC_16);

    // CH3
    /*MAP_uDMAChannelAssign(UDMA_CH17_ADC_CH3);
    UDMASetupTransfer(UDMA_CH17_ADC_CH3 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel6FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH3BuffPRI), UDMA_DST_INC_16);

    UDMASetupTransfer(UDMA_CH17_ADC_CH3 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                      ADC_BUFF_SIZE,
                      UDMA_SIZE_16, UDMA_ARB_1,
                      (void *)(ADC_BASE + ADC_O_channel6FIFODATA), UDMA_SRC_INC_NONE,
                      (void *)&(g_ucADCCH3BuffALT), UDMA_DST_INC_16);*/

    ///////////////////////////////////////////////////////////////////////////////
    // Configure ADC timer which is used to timestamp the ADC data samples
    //MAP_ADCTimerConfig(ADC_BASE, 2 ^ 17);

    // Enable ADC timer which is used to timestamp the ADC data samples
    //MAP_ADCTimerEnable(ADC_BASE);

    MAP_ADCDMADisable(ADC_BASE, ADC_CH_0);
    MAP_ADCDMADisable(ADC_BASE, ADC_CH_1);
    MAP_ADCDMAEnable(ADC_BASE, ADC_CH_2);
    MAP_ADCDMADisable(ADC_BASE, ADC_CH_3);

    Status = MAP_ADCIntStatus(ADC_BASE, ADC_CH_2);
    MAP_ADCIntClear(ADC_BASE, ADC_CH_2, Status | ADC_DMA_DONE);
    MAP_ADCIntEnable(ADC_BASE, ADC_CH_2, ADC_DMA_DONE);
    MAP_ADCChannelDisable(ADC_BASE, ADC_CH_0);
    MAP_ADCChannelDisable(ADC_BASE, ADC_CH_1);
    MAP_ADCChannelEnable(ADC_BASE, ADC_CH_2);
    MAP_ADCChannelDisable(ADC_BASE, ADC_CH_3);

    MAP_ADCEnable(ADC_BASE);

#ifndef NOTERM
    UART_PRINT("ADC init\n\r");
#endif
}

//*****************************************************************************
//
//! \brief ADC Interrupt handler
//!
//! \param None
//!
//! \return None
//!
//*****************************************************************************
void ADCIntHandler()
{
#ifndef NOTERM
    UART_PRINT("ADC int\n\r");
#endif
    unsigned long ulMode;
    unsigned long ulStatus;

    ulStatus = ADCIntStatus(ADC_BASE, ADC_CH_2);
    ADCIntClear(ADC_BASE, ADC_CH_2, ulStatus | ADC_DMA_DONE);

    if (stopAdc)
    {
        ADCDMADisable(ADC_BASE, ADC_CH_2);
        ADCIntDisable(ADC_BASE, ADC_CH_2, ADC_DMA_DONE);
        ADCChannelDisable(ADC_BASE, ADC_CH_2);
        ADCDisable(ADC_BASE);
        UDMADeInit();
#ifndef NOTERM
        UART_PRINT("ADC stop\n\r");
#endif
    }
    else
    {
        ulMode = MAP_uDMAChannelModeGet(UDMA_CH16_ADC_CH2 | UDMA_PRI_SELECT);
        if (ulMode == UDMA_MODE_STOP)
        {
            /*UDMASetupTransfer(UDMA_CH14_ADC_CH0 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                          ADC_BUFF_SIZE,
                          UDMA_SIZE_16, UDMA_ARB_1,
                          (void *)(ADC_BASE + ADC_O_channel0FIFODATA), UDMA_SRC_INC_NONE,
                          (void *)&(g_ucADCCH0BuffPRI), UDMA_DST_INC_16);

            UDMASetupTransfer(UDMA_CH15_ADC_CH1 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                          ADC_BUFF_SIZE,
                          UDMA_SIZE_16, UDMA_ARB_1,
                          (void *)(ADC_BASE + ADC_O_channel2FIFODATA), UDMA_SRC_INC_NONE,
                          (void *)&(g_ucADCCH1BuffPRI), UDMA_DST_INC_16);*/

            UDMASetupTransfer(UDMA_CH16_ADC_CH2 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                              ADC_BUFF_SIZE,
                              UDMA_SIZE_16, UDMA_ARB_1,
                              (void *)(ADC_BASE + ADC_O_channel4FIFODATA), UDMA_SRC_INC_NONE,
                              (void *)&(g_ucADCCH2BuffPRI), UDMA_DST_INC_16);

            /*UDMASetupTransfer(UDMA_CH17_ADC_CH3 | UDMA_PRI_SELECT, UDMA_MODE_PINGPONG,
                          ADC_BUFF_SIZE,
                          UDMA_SIZE_16, UDMA_ARB_1,
                          (void *)(ADC_BASE + ADC_O_channel6FIFODATA), UDMA_SRC_INC_NONE,
                          (void *)&(g_ucADCCH3BuffPRI), UDMA_DST_INC_16);*/

#ifndef NOTERM
            UART_PRINT("ADC pri\n\r");
#endif

            //UDP_send("ADCDATA", 7);
            //ADCLong2Char(g_ucADCCH0BuffPRI);
            //ADCLong2Char(g_ucADCCH1BuffPRI);
            ADCLong2Char(g_ucADCCH2BuffPRI);
            //ADCLong2Char(g_ucADCCH3BuffPRI);
            //UDP_send("ADCSTOP", 7);
            /*
        UDP_send(CH0PRI, 6);
        TCP_send(g_ucADCCH0BuffPRI, ADC_BUFF_SIZE);
        UDP_send(CH1PRI, 6);
        TCP_send(g_ucADCCH1BuffPRI, ADC_BUFF_SIZE);
        UDP_send(CH2PRI, 6);
        TCP_send(g_ucADCCH2BuffPRI, ADC_BUFF_SIZE);
        UDP_send(CH3PRI, 6);
        TCP_send(g_ucADCCH3BuffPRI, ADC_BUFF_SIZE);*/
#ifndef NOTERM
            UART_PRINT("ADC pri\n\r");
#endif
        }
        else
        {
            ulMode = MAP_uDMAChannelModeGet(UDMA_CH16_ADC_CH2 | UDMA_ALT_SELECT);
            if (ulMode == UDMA_MODE_STOP)
            {

                /*UDMASetupTransfer(UDMA_CH14_ADC_CH0 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                              ADC_BUFF_SIZE,
                              UDMA_SIZE_16, UDMA_ARB_1,
                              (void *)(ADC_BASE + ADC_O_channel0FIFODATA), UDMA_SRC_INC_NONE,
                              (void *)&(g_ucADCCH0BuffALT), UDMA_DST_INC_16);

                UDMASetupTransfer(UDMA_CH15_ADC_CH1 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                              ADC_BUFF_SIZE,
                              UDMA_SIZE_16, UDMA_ARB_1,
                              (void *)(ADC_BASE + ADC_O_channel2FIFODATA), UDMA_SRC_INC_NONE,
                              (void *)&(g_ucADCCH1BuffALT), UDMA_DST_INC_16);*/

                UDMASetupTransfer(UDMA_CH16_ADC_CH2 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                                  ADC_BUFF_SIZE,
                                  UDMA_SIZE_16, UDMA_ARB_1,
                                  (void *)(ADC_BASE + ADC_O_channel4FIFODATA), UDMA_SRC_INC_NONE,
                                  (void *)&(g_ucADCCH2BuffALT), UDMA_DST_INC_16);

                /*UDMASetupTransfer(UDMA_CH17_ADC_CH3 | UDMA_ALT_SELECT, UDMA_MODE_PINGPONG,
                              ADC_BUFF_SIZE,
                              UDMA_SIZE_16, UDMA_ARB_1,
                              (void *)(ADC_BASE + ADC_O_channel6FIFODATA), UDMA_SRC_INC_NONE,
                              (void *)&(g_ucADCCH3BuffALT), UDMA_DST_INC_16);*/

                //UDP_send("ADCDATA", 7);
                //ADCLong2Char(g_ucADCCH0BuffALT);
                //ADCLong2Char(g_ucADCCH1BuffALT);
                ADCLong2Char(g_ucADCCH2BuffALT);
                //ADCLong2Char(g_ucADCCH3BuffALT);
                //UDP_send("ADCSTOP", 7);
#ifndef NOTERM
                UART_PRINT("ADC alt\n\r");
#endif
            }
        }
    }
}

void ADCLong2Char(unsigned short *adcBuffer)
{
    unsigned int i;
    for (i = 0; i < ADC_BUFF_SIZE; i += 2)
    {
        //ADCSeg0[i] = (char)(adcBuffer[i]);
        //ADCSeg1[i] = (char)(adcBuffer[i] >> 8);
        //ADCSeg2[i] = (char)(adcBuffer[i] >> 16);
        //ADCSeg3[i] = (char)(adcBuffer[i] >> 24);

        ADCSeg1[i] = (char)(adcBuffer[i / 2] >> 8);
        ADCSeg1[i + 1] = (char)(adcBuffer[i / 2]);
    }

    for (i = 0; i < ADC_BUFF_SIZE; i += 2)
    {
        //ADCSeg0[i] = (char)(adcBuffer[i]);
        //ADCSeg1[i] = (char)(adcBuffer[i] >> 8);
        //ADCSeg2[i] = (char)(adcBuffer[i] >> 16);
        //ADCSeg3[i] = (char)(adcBuffer[i] >> 24);

        ADCSeg0[i] = (char)(adcBuffer[i / 2 + 512] >> 8);
        ADCSeg0[i + 1] = (char)(adcBuffer[i / 2 + 512]);
    }

    //TCP_send(ADCSeg3, ADC_BUFF_SIZE);
    //TCP_send(ADCSeg2, ADC_BUFF_SIZE);
    //TCP_send(ADCSeg1, ADC_BUFF_SIZE);
    //TCP_send(ADCSeg0, ADC_BUFF_SIZE);

    //UDP_send(ADCSeg3, ADC_BUFF_SIZE);
    //UDP_send(ADCSeg2, ADC_BUFF_SIZE);
    UDP_send(ADCSeg1, ADC_BUFF_SIZE);
    UDP_send(ADCSeg0, ADC_BUFF_SIZE);
    //UART_PRINT("\n\rbits[13:2] : ADC sample\n\r");
    //UART_PRINT("\n\rbits[31:14]: Time stamp of ADC sample \n\r");
}

void AdcStop()
{
    stopAdc = 1;
}
