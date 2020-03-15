//-----------------------------------------------------------------------------
// Copyright:      Ripak Co.LTD
// Author:         CMSIS_I2C_lib modefied by Mojtaba Rostami 
// Remarks:
// Date: 					 2013/10/23
// known Problems: HT24LC_LDbWr & HT24LC_LDbRd
// Version:        1.0.0
// Description:    EEPROM driver, 24LCXX 
//-----------------------------------------------------------------------------
#ifndef HT24LC_H_
#define HT24LC_H_

#include "..\driver\lpc17xx_i2c.h"
#include "..\driver\lpc17xx_pinsel.h"

/** Used I2C device definition */
#define I2CDEV LPC_I2C0
/* Definition of internal register of EEPROM HT24LC */
/* 7 bit address */
#define HT24LC_SLVADDR		(0xA0>>1)
/*I2C0 clockrate*/
#define I2C_CLOCKRATE					200000

void I2C0_Init (void);
void I2C1_Init (void);

/*Long Double function for these Data types(10 Bytes):
long double
*/
int8_t HT24LC_LDbWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
int8_t HT24LC_LDbRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);

/*Page function for these Data types(8 Bytes):
int64_t
uint64_t
double
*/
int8_t HT24LC_PageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
int8_t HT24LC_PageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);

/*Half page function for these Data types(4 Bytes):
uint32_t
int32_t
float
*/
int8_t HT24LC_HfPageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
int8_t HT24LC_HfPageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);

/*Half Half page function for these Data types(2 Bytes):
uint16_t
int16_t
*/
int8_t HT24LC_HHfPageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
int8_t HT24LC_HHfPageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);

/*Byte function for these Data types(1 Bytes):
char
uint8_t
int8_t
*/
int8_t HT24LC_ByteWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
int8_t HT24LC_ByteRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t addr,void *data);
#endif /* LPC17XX_I2C_H_ */