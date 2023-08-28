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

  /* Memory mapping of Core Hardware */
  #define SCS_BASE            (0xE000E000UL)

  /* System Control Space Base Address */
  #define STK_BASE            (*(volatile uint32_t*)(SCS_BASE +  0x0010UL))
  #define NVIC_BASE           (*(volatile uint32_t*)(SCS_BASE +  0x0100UL))
  #define SCB_BASE            (*(volatile uint32_t*)(SCS_BASE +  0x0D00UL))

  /* NVIC configuration struct */
  #define NVIC                ((volatile NVIC_Type*)NVIC_BASE)

  /* SCB registers */
  #define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

  /* Base addresses for peripheral registers */
  #define RCC_BASE            0x40023800UL
  #define PWR_BASE            0x40007000UL
  #define FLASH_BASE          0x40023C00UL
  #define GPIOA_BASE          0x40020000UL
  #define SPI_BASE            0x40013000UL
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


  /* SPI1 registers */
  #define SPI_CR1             (*(volatile uint32_t*)(SPI_BASE + 0x00UL))
  #define SPI_CR2             (*(volatile uint32_t*)(SPI_BASE + 0x04UL))
  #define SPI_SR              (*(volatile uint32_t*)(SPI_BASE + 0x08UL))
  #define SPI_DR              (*(volatile uint32_t*)(SPI_BASE + 0x0CUL))
  #define SPI_CRCPR           (*(volatile uint32_t*)(SPI_BASE + 0x10UL))
  #define SPI_RXCRCR          (*(volatile uint32_t*)(SPI_BASE + 0x14UL))
  #define SPI_TXCRCR          (*(volatile uint32_t*)(SPI_BASE + 0x18UL))

  /* DMA2 registers */
  #define DMA2                (*(volatile uint32_t*)(DMA2_BASE+ 0x0000UL))
  #define DMA2_STREAM2_BASE   (*(volatile uint32_t*)(DMA2_BASE + 0x040UL))
  #define DMA2_STREAM3_BASE   (*(volatile uint32_t*)(DMA2_BASE + 0x058UL))

  #define DMA2_STREAM2        ((volatile DMA_Stream_TypeDef*) DMA2_STREAM2_BASE)
  #define DMA2_STREAM3        ((volatile DMA_Stream_TypeDef*) DMA2_STREAM3_BASE)

#endif /* REG_2023_08_26_H */
