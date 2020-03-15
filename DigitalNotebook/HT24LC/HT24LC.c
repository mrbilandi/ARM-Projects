//-----------------------------------------------------------------------------
// Copyright:      Ripak Co.LTD
// Author:         CMSIS_I2C_lib modefied by Mojtaba Rostami 
// Remarks:
// Date: 					 2013/10/23
// known Problems: HT24LC_LDbWr & HT24LC_LDbRd
// Version:        1.0.0
// Description:    EEPROM driver, 24LCXX 
//-----------------------------------------------------------------------------
#include	"HT24LC.h"

////////////////I2C0 Initialization Function///////////////////////////////////////////////
void I2C0_Init (void)
{
	PINSEL_CFG_Type PinCfg;
	
	//Init I2C pin connect
	PinCfg.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Funcnum = 1;
	PinCfg.Pinnum = 27;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 28;
	PINSEL_ConfigPin(&PinCfg);
	// Initialize I2C0 clockrate
	I2C_Init(LPC_I2C0, I2C_CLOCKRATE);
	/* Enable I2C0 operation */
	I2C_Cmd(LPC_I2C0, I2C_MASTER_MODE, ENABLE);
}////////////////End I2C0 Initialization Function///////////////////////////////////////////////

////////////////I2C0 Initialization Function///////////////////////////////////////////////
void I2C1_Init (void)
{
	PINSEL_CFG_Type PinCfg;
	
	//Init I2C pin connect
	PinCfg.OpenDrain = PINSEL_PINMODE_OPENDRAIN;
	PinCfg.Pinmode = PINSEL_PINMODE_PULLUP;
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);
	// Initialize I2C1 clockrate
	I2C_Init(LPC_I2C1, I2C_CLOCKRATE);
	/* Enable I2C1 operation */
	I2C_Cmd(LPC_I2C1, I2C_MASTER_MODE, ENABLE);
}////////////////End I2C0 Initialization Function///////////////////////////////////////////////


////////////////EEPROM Long Double Write Function///////////////////////////////////////////////
int8_t HT24LC_LDbWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Transmit setup */
	I2C_M_SETUP_Type txsetup;
	uint8_t wrdata[9+2],*dp,i,offset=8+2;
	uint32_t tmp;
	
	wrdata[0]=offset+pgaddr*offset;
	
	dp=(uint8_t *)data;
	for(i=0;i<8+2;i++)
		wrdata[i+1]=dp[i];
	
	txsetup.sl_addr7bit = HT24LC_ADDR;
	txsetup.tx_data = wrdata;
	txsetup.tx_length = sizeof(wrdata);
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		for (tmp = 0x100000; tmp; tmp--);
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Long Double Write Function///////////////////////////////////////////////

////////////////EEPROM Long Double Read Function///////////////////////////////////////////////
int8_t HT24LC_LDbRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Receive setup */
	I2C_M_SETUP_Type rxsetup;
	uint8_t rddata[8+2],*dp,offset=8+2,addr;
	
	addr=offset+pgaddr*offset;
	dp=(uint8_t *)data;
	
	rxsetup.sl_addr7bit = HT24LC_ADDR;
	rxsetup.tx_data = &addr;// Get address to read at writing address
	rxsetup.tx_length = 1;
	rxsetup.rx_data = dp;
	rxsetup.rx_length = sizeof(rddata);
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Long Double Read Function///////////////////////////////////////////////


////////////////EEPROM Page Write Function///////////////////////////////////////////////
int8_t HT24LC_PageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Transmit setup */
	I2C_M_SETUP_Type txsetup;
	uint8_t wrdata[9],*dp,i,offset=8;
	uint32_t tmp;
	
	wrdata[0]=offset+pgaddr*offset;
	
	dp=(uint8_t *)data;
	for(i=0;i<8;i++)
		wrdata[i+1]=dp[i];
	
	txsetup.sl_addr7bit = HT24LC_ADDR;
	txsetup.tx_data = wrdata;
	txsetup.tx_length = sizeof(wrdata);
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		for (tmp = 0x100000; tmp; tmp--);
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Page Write Function///////////////////////////////////////////////

////////////////EEPROM Page Read Function///////////////////////////////////////////////
int8_t HT24LC_PageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Receive setup */
	I2C_M_SETUP_Type rxsetup;
	uint8_t rddata[8],*dp,offset=8,addr;
	
	addr=offset+pgaddr*offset;
	dp=(uint8_t *)data;
	
	rxsetup.sl_addr7bit = HT24LC_ADDR;
	rxsetup.tx_data = &addr;// Get address to read at writing address
	rxsetup.tx_length = 1;
	rxsetup.rx_data = dp;
	rxsetup.rx_length = sizeof(rddata);
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Page Read Function///////////////////////////////////////////////

////////////////EEPROM Half page Write Function///////////////////////////////////////////////
int8_t HT24LC_HfPageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Transmit setup */
	I2C_M_SETUP_Type txsetup;
	uint8_t wrdata[9-4],*dp,i,offset=8-4;
	uint32_t tmp;
	
	wrdata[0]=offset+pgaddr*offset;
	
	dp=(uint8_t *)data;
	for(i=0;i<8-4;i++)
		wrdata[i+1]=dp[i];
	
	txsetup.sl_addr7bit = HT24LC_ADDR;
	txsetup.tx_data = wrdata;
	txsetup.tx_length = sizeof(wrdata);
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		for (tmp = 0x100000; tmp; tmp--);
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Write Function///////////////////////////////////////////////

////////////////EEPROM Half page Read Function///////////////////////////////////////////////
int8_t HT24LC_HfPageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Receive setup */
	I2C_M_SETUP_Type rxsetup;
	uint8_t rddata[8-4],*dp,offset=8-4,addr;
	
	addr=offset+pgaddr*offset;
	dp=(uint8_t *)data;
	
	rxsetup.sl_addr7bit = HT24LC_ADDR;
	rxsetup.tx_data = &addr;// Get address to read at writing address
	rxsetup.tx_length = 1;
	rxsetup.rx_data = dp;
	rxsetup.rx_length = sizeof(rddata);
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Read Function///////////////////////////////////////////////

////////////////EEPROM Half page Write Function///////////////////////////////////////////////
int8_t HT24LC_HHfPageWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Transmit setup */
	I2C_M_SETUP_Type txsetup;
	uint8_t wrdata[9-6],*dp,i,offset=8-6;
	uint32_t tmp;
	
	wrdata[0]=offset+pgaddr*offset;
	
	dp=(uint8_t *)data;
	for(i=0;i<8-6;i++)
		wrdata[i+1]=dp[i];
	
	txsetup.sl_addr7bit = HT24LC_ADDR;
	txsetup.tx_data = wrdata;
	txsetup.tx_length = sizeof(wrdata);
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		for (tmp = 0x100000; tmp; tmp--);
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Write Function///////////////////////////////////////////////

////////////////EEPROM Half page Read Function///////////////////////////////////////////////
int8_t HT24LC_HHfPageRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Receive setup */
	I2C_M_SETUP_Type rxsetup;
	uint8_t rddata[8-6],*dp,offset=8-6,addr;
	
	addr=offset+pgaddr*offset;
	dp=(uint8_t *)data;
	
	rxsetup.sl_addr7bit = HT24LC_ADDR;
	rxsetup.tx_data = &addr;// Get address to read at writing address
	rxsetup.tx_length = 1;
	rxsetup.rx_data = dp;
	rxsetup.rx_length = sizeof(rddata);
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Read Function///////////////////////////////////////////////

////////////////EEPROM Half page Write Function///////////////////////////////////////////////
int8_t HT24LC_ByteWr(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Transmit setup */
	I2C_M_SETUP_Type txsetup;
	uint8_t wrdata[9-7],*dp,i,offset=8-7;
	uint32_t tmp;
	
	wrdata[0]=offset+pgaddr*offset;
	
	dp=(uint8_t *)data;
	for(i=0;i<8-7;i++)
		wrdata[i+1]=dp[i];
	
	txsetup.sl_addr7bit = HT24LC_ADDR;
	txsetup.tx_data = wrdata;
	txsetup.tx_length = sizeof(wrdata);
	txsetup.rx_data = NULL;
	txsetup.rx_length = 0;
	txsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &txsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		for (tmp = 0x100000; tmp; tmp--);
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Write Function///////////////////////////////////////////////

////////////////EEPROM Half page Read Function///////////////////////////////////////////////
int8_t HT24LC_ByteRd(LPC_I2C_TypeDef *I2Cx,uint8_t HT24LC_ADDR,uint8_t pgaddr,void *data)
{
	/* Receive setup */
	I2C_M_SETUP_Type rxsetup;
	uint8_t rddata[8-7],*dp,offset=8-7,addr;
	
	addr=offset+pgaddr*offset;
	dp=(uint8_t *)data;
	
	rxsetup.sl_addr7bit = HT24LC_ADDR;
	rxsetup.tx_data = &addr;// Get address to read at writing address
	rxsetup.tx_length = 1;
	rxsetup.rx_data = dp;
	rxsetup.rx_length = sizeof(rddata);
	rxsetup.retransmissions_max = 3;

	if (I2C_MasterTransferData(I2Cx, &rxsetup, I2C_TRANSFER_POLLING) == SUCCESS){
		return (0);
	} else {
		return (-1);
	}
}////////////////End EEPROM Half page Read Function///////////////////////////////////////////////

