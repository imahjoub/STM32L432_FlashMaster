#ifndef CPU_2023_08_19_H
  #define CPU_2023_08_19_H

  #include <stdint.h>

  // Base addresses for peripheral registers
  #define SCB_BASE            0xE000ED00UL
  #define RCC_BASE            0x40023800UL
  #define PWR_BASE            0x40007000UL
  #define FLASH_BASE          0x40023C00UL

  // SCB registers
  #define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

  // RCC Registers
  #define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
  #define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
  #define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
  #define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x30UL))
  #define RCC_CIR             (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
  #define RCC_APB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x40UL))

  // PWR registers
  #define PWR_CR              (*(volatile uint32_t*)(PWR_BASE + 0x00UL))

  // FLASH registers
  #define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x00UL))

  void SystemInit(void);
  void SetSysClock(void);

#endif // CPU_2023_08_19_H
