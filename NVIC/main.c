#include <lpc17xx_gpio.h>
#include <lpc17xx_pinsel.h>
#include <lpc17xx_exti.h>
#include <delay.h>

//LED(s)	defines
#define LED_PORT	2
#define LED1			(1<<0)
#define LED2			(1<<1)
//KEY(S) defines:
#define KEY_PORT	2
#define KEY1			(1<<11)
#define KEY1_INT_PIN	11

void EINT0_IRQHandler (void);
void EINT3_IRQHandler (void);
void mydelay(void);

EXTI_InitTypeDef extcfg={EXTI_EINT0,EXTI_MODE_EDGE_SENSITIVE,EXTI_POLARITY_LOW_ACTIVE_OR_FALLING_EDGE};
PINSEL_CFG_Type	pincfg={PINSEL_PORT_2,PINSEL_PIN_10,PINSEL_FUNC_1,PINSEL_PINMODE_PULLUP,PINSEL_PINMODE_NORMAL};

FlagStatus flag=RESET;

int main(void){
	PINSEL_ConfigPin(&pincfg);
	EXTI_Init();
	EXTI_Config(&extcfg);
	NVIC_SetPriorityGrouping(4);//Number of Group priorities = 8 , Subpriorities = 4
	NVIC_SetPriority(EINT0_IRQn, 1);//7:5=0 ,4:3=1 Group priorities = 0 , Subpriorities = 1
	NVIC_SetPriority(EINT3_IRQn, 4);//7:5=1 ,4:3=0 Group priorities = 1 , Subpriorities = 0
	
	NVIC_EnableIRQ(EINT0_IRQn);
	//LEDs Pin Configuration:
	GPIO_SetDir(LED_PORT, LED1, 1);	
	GPIO_SetDir(LED_PORT, LED2, 1);
	//KEY1 INT Configuration:
	GPIO_IntCmd(KEY_PORT, KEY1, 1);
	//Enable IRQ of EXTI3:
	NVIC_EnableIRQ(EINT3_IRQn);
	//init delay:
	delay_init();
	for(;;){
		if(flag){
			GPIO_SetValue(LED_PORT, LED1);
			delay(500);
			GPIO_ClearValue(LED_PORT, LED1);
			delay(500);
		}
	}
}

void EINT0_IRQHandler (void){
	uint8_t i;
	EXTI_ClearEXTIFlag(EXTI_EINT0);
	//flag=SET;
		for(i=0;i<5;i++){	
			GPIO_SetValue(LED_PORT, LED1);
			mydelay();
			GPIO_ClearValue(LED_PORT, LED1);
			mydelay();
		}
} 

void EINT3_IRQHandler (void){
	uint8_t i;
	if(GPIO_GetIntStatus(KEY_PORT, KEY1_INT_PIN, 1)){
		GPIO_ClearInt(KEY_PORT, KEY1);
		//flag=RESET;
		for(i=0;i<5;i++){	
			GPIO_SetValue(LED_PORT, LED2);
			mydelay();
			GPIO_ClearValue(LED_PORT, LED2);
			mydelay();
		}
	}
} 

void mydelay(void){
	uint32_t i;
	for(i=0;i<8000000;i++);
}
	
