#ifndef REG_2023_08_26_H
  #define REG_2023_08_26_H

  #include <stdint.h>

  /* ----------------------------------------------------------------------------------- */
  /*  Types definition                                                                   */
  /* ----------------------------------------------------------------------------------- */
  typedef struct
  {
    volatile uint32_t CR;     /* DMA stream x configuration register      */
    volatile uint32_t NDTR;   /* DMA stream x number of data register     */
    volatile uint32_t PAR;    /* DMA stream x peripheral address register */
    volatile uint32_t M0AR;   /* DMA stream x memory 0 address register   */
    volatile uint32_t M1AR;   /* DMA stream x memory 1 address register   */
    volatile uint32_t FCR;    /* DMA stream x FIFO control register       */
  } DMA_Stream_TypeDef;

  typedef struct
  {
    volatile uint32_t ISER[8U];        /* Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
             uint32_t RESERVED0[24U];
    volatile uint32_t ICER[8U];        /* Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
             uint32_t RSERVED1[24U];
    volatile uint32_t ISPR[8U];        /* Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
             uint32_t RESERVED2[24U];
    volatile uint32_t ICPR[8U];        /* Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
             uint32_t RESERVED3[24U];
    volatile uint32_t IABR[8U];        /* Offset: 0x200 (R/W)  Interrupt Active bit Register           */
             uint32_t RESERVED4[56U];
    volatile uint8_t  IP[240U];        /* Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
             uint32_t RESERVED5[644U];
    volatile uint32_t STIR;            /* Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
  } NVIC_Type;

  /* ----------------------------------------------------------------------------------- */
  /* Macros                                                                              */
  /* ----------------------------------------------------------------------------------- */

  /* System Control Space Base Address */
  #define SCS_BASE            (0xE000E000UL)

  /* Core peripherals */
  #define STK_BASE            ((SCS_BASE + 0x0010UL))
  #define NVIC_BASE           ((SCS_BASE + 0x0100UL))
  #define SCB_BASE            ((SCS_BASE + 0x0D00UL))

  /* NVIC configuration struct */
  #define NVIC                ((NVIC_Type*)NVIC_BASE)

  /* SCB registers */
  #define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

  /* Base addresses for peripheral registers */
  #define RCC_BASE            0x40023800UL
  #define PWR_BASE            0x40007000UL
  #define FLASH_BASE          0x40023C00UL
  #define GPIOA_BASE          0x40020000UL
  #define GPIOB_BASE          0x40020400UL
  #define GPIOF_BASE          0x40021400UL
  #define SPI1_BASE           0x40013000UL
  #define I2C1_BASE           0x40005400UL
  #define I2C2_BASE           0x40005800UL
  #define DMA2_BASE           0x40026400UL

  /* RCC Registers */
  #define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
  #define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
  #define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
  #define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x30UL))
  #define RCC_CIR             (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
  #define RCC_APB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x40UL))
  #define RCC_APB2ENR         (*(volatile uint32_t*)(RCC_BASE + 0x44UL))

  /* SysTick registers */
  #define STK_CTRL            (*(volatile uint32_t*)(STK_BASE + 0x00UL))
  #define STK_LOAD            (*(volatile uint32_t*)(STK_BASE + 0x04UL))
  #define STK_VAL             (*(volatile uint32_t*)(STK_BASE + 0x08UL))

  /* PWR registers */
  #define PWR_CR              (*(volatile uint32_t*)(PWR_BASE + 0x00UL))

  /* FLASH registers */
  #define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x00UL))

  /* GPIOA registers */
  #define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00UL))
  #define GPIOA_OTYPER        (*(volatile uint32_t*)(GPIOA_BASE + 0x04UL))
  #define GPIOA_OSPEEDR       (*(volatile uint32_t*)(GPIOA_BASE + 0x08UL))
  #define GPIOA_PUPDR         (*(volatile uint32_t*)(GPIOA_BASE + 0x0CUL))
  #define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14UL))
  #define GPIOA_AFRL          (*(volatile uint32_t*)(GPIOA_BASE + 0x20UL))

  /* GPIOB registers */
  #define GPIOB_MODER         (*(volatile uint32_t*)(GPIOB_BASE + 0x00UL))
  #define GPIOB_OTYPER        (*(volatile uint32_t*)(GPIOB_BASE + 0x04UL))
  #define GPIOB_OSPEEDR       (*(volatile uint32_t*)(GPIOB_BASE + 0x08UL))
  #define GPIOB_PUPDR         (*(volatile uint32_t*)(GPIOB_BASE + 0x0CUL))
  #define GPIOB_ODR           (*(volatile uint32_t*)(GPIOB_BASE + 0x14UL))
  #define GPIOB_AFRL          (*(volatile uint32_t*)(GPIOB_BASE + 0x20UL))
  #define GPIOB_AFRH          (*(volatile uint32_t*)(GPIOB_BASE + 0x24UL))

  /* GPIOF registers */
  #define GPIOF_MODER         (*(volatile uint32_t*)(GPIOF_BASE + 0x00UL))
  #define GPIOF_OTYPER        (*(volatile uint32_t*)(GPIOF_BASE + 0x04UL))
  #define GPIOF_OSPEEDR       (*(volatile uint32_t*)(GPIOF_BASE + 0x08UL))
  #define GPIOF_PUPDR         (*(volatile uint32_t*)(GPIOF_BASE + 0x0CUL))
  #define GPIOF_ODR           (*(volatile uint32_t*)(GPIOF_BASE + 0x14UL))
  #define GPIOF_AFRL          (*(volatile uint32_t*)(GPIOF_BASE + 0x20UL))
  #define GPIOF_AFRH          (*(volatile uint32_t*)(GPIOF_BASE + 0x24UL))

  /* SPI1 registers */
  #define SPI_CR1             (*(volatile uint32_t*)(SPI1_BASE + 0x00UL))
  #define SPI_CR2             (*(volatile uint32_t*)(SPI1_BASE + 0x04UL))
  #define SPI_SR              (*(volatile uint32_t*)(SPI1_BASE + 0x08UL))
  #define SPI_DR              (*(volatile uint32_t*)(SPI1_BASE + 0x0CUL))
  #define SPI_CRCPR           (*(volatile uint32_t*)(SPI1_BASE + 0x10UL))
  #define SPI_RXCRCR          (*(volatile uint32_t*)(SPI1_BASE + 0x14UL))
  #define SPI_TXCRCR          (*(volatile uint32_t*)(SPI1_BASE + 0x18UL))

  /* I2C1 registers */
  #define I2C1_CR1             (*(volatile uint32_t*)(I2C1_BASE + 0x00UL))
  #define I2C1_CR2             (*(volatile uint32_t*)(I2C1_BASE + 0x04UL))
  #define I2C1_OAR1            (*(volatile uint32_t*)(I2C1_BASE + 0x08UL))
  #define I2C1_OAR2            (*(volatile uint32_t*)(I2C1_BASE + 0x0CUL))
  #define I2C1_DR              (*(volatile uint32_t*)(I2C1_BASE + 0x10UL))
  #define I2C1_SR1             (*(volatile uint32_t*)(I2C1_BASE + 0x14UL))
  #define I2C1_SR2             (*(volatile uint32_t*)(I2C1_BASE + 0x18UL))
  #define I2C1_CCR             (*(volatile uint32_t*)(I2C1_BASE + 0x1CUL))
  #define I2C1_TRISE           (*(volatile uint32_t*)(I2C1_BASE + 0x20UL))

  /* I2C2 registers */
  #define I2C2_CR1             (*(volatile uint32_t*)(I2C2_BASE + 0x00UL))
  #define I2C2_CR2             (*(volatile uint32_t*)(I2C2_BASE + 0x04UL))
  #define I2C2_OAR1            (*(volatile uint32_t*)(I2C2_BASE + 0x08UL))
  #define I2C2_OAR2            (*(volatile uint32_t*)(I2C2_BASE + 0x0CUL))
  #define I2C2_DR              (*(volatile uint32_t*)(I2C2_BASE + 0x10UL))
  #define I2C2_SR1             (*(volatile uint32_t*)(I2C2_BASE + 0x14UL))
  #define I2C2_SR2             (*(volatile uint32_t*)(I2C2_BASE + 0x18UL))
  #define I2C2_CCR             (*(volatile uint32_t*)(I2C2_BASE + 0x1CUL))
  #define I2C2_TRISE           (*(volatile uint32_t*)(I2C2_BASE + 0x20UL))

  /* DMA2 Streamx base adresses */
  #define DMA2_STREAM2_BASE   (DMA2_BASE + 0x040UL)
  #define DMA2_STREAM3_BASE   (DMA2_BASE + 0x058UL)

  /* DMA2 registers */
  #define DMA2                (*(volatile uint32_t*)(DMA2_BASE + 0x000UL))
  #define DMA2_LISR           (*(volatile uint32_t*)(DMA2_BASE + 0x000UL))
  #define DMA2_LIFCR          (*(volatile uint32_t*)(DMA2_BASE + 0x008UL))

  /* DMA2 configuration struct */
  #define DMA2_STREAM2        ((DMA_Stream_TypeDef*) DMA2_STREAM2_BASE)
  #define DMA2_STREAM3        ((DMA_Stream_TypeDef*) DMA2_STREAM3_BASE)


  /* TBD get DMA working and delete the following */
  // #define NVIC_EnableIRQ      __NVIC_EnableIRQ

  //  static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
  //  {
  //    if((int32_t)(IRQn) >= 0)
  //    {
  //      NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  //    }
  //  }

#endif /* REG_2023_08_26_H */
