volatile unsigned long SysTickCnt;

void delay(unsigned long tick);
void delay_init(void);

void SysTick_Handler (void) {
  SysTickCnt++;
}

void delay (unsigned long tick) {
  unsigned long systickcnt;

  systickcnt = SysTickCnt;
  while ((SysTickCnt - systickcnt) < tick);
}

void delay_init(void) {
	SysTick_Config(SystemCoreClock/1000 - 1); /* Generate interrupt each 1 ms   */
}
