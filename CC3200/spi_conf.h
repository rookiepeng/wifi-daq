/****************************************************************************************
//    Copyright (C) 2017  Zhengyu Peng, zhengyu.peng@ttu.edu
*****************************************************************************************/

#ifndef SPI_CONF_H_
#define SPI_CONF_H_

#define SPI_Interface GSPI_BASE       // SPI interface
#define SPI_IF_BIT_RATE 20000000 / 20 // * must be an integer divisor of 20000000 *

void SPI_Init();
void Master_Send(unsigned long txData);

#endif /* SPI_CONF_H_ */
