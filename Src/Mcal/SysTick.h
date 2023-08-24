#ifndef SYSTICK_2023_08_24_H
  #define SYSTICK_2023_08_24_H

  /* SysTick base address */
  #define STK_BASE            0xE000E010UL

  /* SysTick registers */
  #define STK_CTRL           (*(volatile uint32_t*)(STK_BASE + 0x00UL))
  #define STK_LOAD           (*(volatile uint32_t*)(STK_BASE + 0x04UL))
  #define STK_VAL            (*(volatile uint32_t*)(STK_BASE + 0x08UL))


  void SysTick_Init(void);

#endif /* SYSTICK_2023_08_24_H */
