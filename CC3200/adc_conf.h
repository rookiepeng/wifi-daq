/****************************************************************************************
//    Copyright (C) 2017  Zhengyu Peng, zhengyu.peng@ttu.edu
*****************************************************************************************/

#ifndef ADC_CONF_H_
#define ADC_CONF_H_

#define ADC_BUFF_SIZE 1024

void ADCIntHandler();
void ADCLong2Char(unsigned short *adcBuffer);
void AdcStart();
void AdcStop();

#endif /* ADC_CONF_H_ */
