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

  /* TBD: delete this enum and use own code*/
  typedef enum
  {
  /******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
  /******  STM32 specific Interrupt Numbers **********************************************************************/
    WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
    PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
    TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
    RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
    FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
    RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
    EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
    EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
    EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
    EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
    EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
    DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
    DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
    DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
    DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
    DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
    DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
    DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
    ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
    CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
    CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
    TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
    TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
    TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
    TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
    TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
    TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
    TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
    RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
    OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
    TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
    TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
    TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
    TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare global interrupt                             */
    DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
    FMC_IRQn                    = 48,     /*!< FMC global Interrupt                                              */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
    TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
    TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
    TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
    DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
    DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
    DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
    DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
    DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
    CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
    CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
    CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
    CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
    OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
    DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
    DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
    DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
    USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
    I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
    I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
    OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
    OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
    OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
    OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
    DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
    FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
    SPI4_IRQn                   = 84,     /*!< SPI4 global Interrupt                                             */
    SAI1_IRQn                   = 87,     /*!< SAI1 global Interrupt                                             */
    SAI2_IRQn                   = 91,     /*!< SAI2 global Interrupt                                             */
    QUADSPI_IRQn                = 92,     /*!< QuadSPI global Interrupt                                          */
    CEC_IRQn                    = 93,     /*!< CEC global Interrupt                                              */
    SPDIF_RX_IRQn               = 94,     /*!< SPDIF-RX global Interrupt                                         */
    FMPI2C1_EV_IRQn             = 95,     /*!< FMPI2C1 Event Interrupt                                           */
    FMPI2C1_ER_IRQn             = 96      /*!< FMPI2C1 Error Interrupt                                           */
  } IRQn_Type;

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


  /* TBD delete the following code and use own macros  */
  #define NVIC_EnableIRQ      __NVIC_EnableIRQ

  static inline void __NVIC_EnableIRQ(IRQn_Type IRQn)
  {
    if((int32_t)(IRQn) >= 0)
    {
      NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
    }
  }

#endif /* REG_2023_08_26_H */
