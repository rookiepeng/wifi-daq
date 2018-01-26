/*
 *   adc_conf.h: header file of adc_conf.c
 * 
 *   Copyright (C) 2017  Zhengyu Peng, https://zpeng.me
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADC_CONF_H_
#define ADC_CONF_H_

#define ADC_BUFF_SIZE 1024

void ADCIntHandler();
void ADCLong2Char(unsigned short *adcBuffer);
void AdcStart();
void AdcStop();

#endif /* ADC_CONF_H_ */
