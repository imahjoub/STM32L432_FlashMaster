#ifndef REG_2023_08_26_H
  #define REG_2023_08_26_H

  #include <stdint.h>

  /* ----------------------------------------------------------------------------------- */
  /*  Types definition                                                                   */
  /* ----------------------------------------------------------------------------------- */

  /* ----------------------------------------------------------------------------------- */
  /* Macros                                                                              */
  /* ----------------------------------------------------------------------------------- */

  /* System Control Space Base Address */
  #define SCS_BASE            (0xE000E000UL)

  /* Core peripherals */
  #define STK_BASE            ((SCS_BASE + 0x0010UL))
  #define NVIC_BASE           ((SCS_BASE + 0x0100UL))
  #define SCB_BASE            ((SCS_BASE + 0x0D00UL))

  /* SCB registers */
  #define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

  /* SysTick registers */
  #define STK_CTRL            (*(volatile uint32_t*)(STK_BASE + 0x00UL))
  #define STK_LOAD            (*(volatile uint32_t*)(STK_BASE + 0x04UL))
  #define STK_VAL             (*(volatile uint32_t*)(STK_BASE + 0x08UL))

  /* Base addresses for peripheral registers */
  #define RCC_BASE            0x40021000UL
  #define PWR_BASE            0x40007000UL
  #define FLASH_BASE          0x40022000UL
  #define GPIOA_BASE          0x48000000UL
  #define GPIOB_BASE          0x48000400UL
  #define I2C1_BASE           0x40005400UL
  #define SPI1_BASE           0x40013000UL



  /* FLASH registers */
  #define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x000UL))

  /* PWR registers */
  #define PWR_CR1             (*(volatile uint32_t*)(PWR_BASE + 0x000UL))
  #define PWR_SR2             (*(volatile uint32_t*)(PWR_BASE + 0x014UL))

  /* RCC Registers */
  #define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
  #define RCC_ICSCR           (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
  #define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
  #define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
  #define RCC_CIER            (*(volatile uint32_t*)(RCC_BASE + 0x18UL))
  #define RCC_APB1RSTR1       (*(volatile uint32_t*)(RCC_BASE + 0x38UL))
  #define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x48UL))
  #define RCC_AHB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x4CUL))
  #define RCC_APB1ENR1        (*(volatile uint32_t*)(RCC_BASE + 0x58UL))
  #define RCC_APB1ENR2        (*(volatile uint32_t*)(RCC_BASE + 0x5CUL))
  #define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x60UL))


  /* GPIOA registers */
  #define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00UL))
  #define GPIOA_OTYPER        (*(volatile uint32_t*)(GPIOA_BASE + 0x04UL))
  #define GPIOA_OSPEEDR       (*(volatile uint32_t*)(GPIOA_BASE + 0x08UL))
  #define GPIOA_PUPDR         (*(volatile uint32_t*)(GPIOA_BASE + 0x0CUL))
  #define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14UL))
  #define GPIOA_AFRL          (*(volatile uint32_t*)(GPIOA_BASE + 0x20UL))
  #define GPIOA_AFRH          (*(volatile uint32_t*)(GPIOA_BASE + 0x24UL))

  /* GPIOB registers */
  #define GPIOB_MODER         (*(volatile uint32_t*)(GPIOB_BASE + 0x00UL))
  #define GPIOB_OTYPER        (*(volatile uint32_t*)(GPIOB_BASE + 0x04UL))
  #define GPIOB_OSPEEDR       (*(volatile uint32_t*)(GPIOB_BASE + 0x08UL))
  #define GPIOB_PUPDR         (*(volatile uint32_t*)(GPIOB_BASE + 0x0CUL))
  #define GPIOB_ODR           (*(volatile uint32_t*)(GPIOB_BASE + 0x14UL))
  #define GPIOB_AFRL          (*(volatile uint32_t*)(GPIOB_BASE + 0x20UL))
  #define GPIOB_AFRH          (*(volatile uint32_t*)(GPIOB_BASE + 0x24UL))

  /* I2C1 registers */
  #define I2C1_CR1            (*(volatile uint32_t*)(I2C1_BASE + 0x00UL))
  #define I2C1_CR2            (*(volatile uint32_t*)(I2C1_BASE + 0x04UL))
  #define I2C1_OAR1           (*(volatile uint32_t*)(I2C1_BASE + 0x08UL))
  #define I2C1_OAR2           (*(volatile uint32_t*)(I2C1_BASE + 0x0CUL))
  #define I2C1_TIMINGR        (*(volatile uint32_t*)(I2C1_BASE + 0x10UL))
  #define I2C1_TIMEOUTR       (*(volatile uint32_t*)(I2C1_BASE + 0x14UL))
  #define I2C1_ISR            (*(volatile uint32_t*)(I2C1_BASE + 0x18UL))
  #define I2C1_ICR            (*(volatile uint32_t*)(I2C1_BASE + 0x1CUL))
  #define I2C1_PECR           (*(volatile uint32_t*)(I2C1_BASE + 0x20UL))
  #define I2C1_RXDR           (*(volatile uint32_t*)(I2C1_BASE + 0x24UL))
  #define I2C1_TXDR           (*(volatile uint32_t*)(I2C1_BASE + 0x28UL))

  /* SPI1 registers */
  #define SPI1_CR1            (*(volatile uint32_t*)(SPI1_BASE + 0x00UL))
  #define SPI1_CR2            (*(volatile uint32_t*)(SPI1_BASE + 0x04UL))
  #define SPI1_SR             (*(volatile uint32_t*)(SPI1_BASE + 0x08UL))
  #define SPI1_DR             (*(volatile uint16_t*)(SPI1_BASE + 0x0CUL))
  #define SPI1_CRCPR          (*(volatile uint32_t*)(SPI1_BASE + 0x10UL))
  #define SPI1_RXCRCR         (*(volatile uint32_t*)(SPI1_BASE + 0x14UL))
  #define SPI1_TXCRCR         (*(volatile uint32_t*)(SPI1_BASE + 0x18UL))

#endif /* REG_2023_08_26_H */
