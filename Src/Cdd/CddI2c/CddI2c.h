#ifndef Cdd_I2C_2024_03_06_H
  #define Cdd_I2C_2024_03_06_H

  #include "stddef.h"
  #include "stdint.h"


  #define CDD_I2C_OAR2_OA2EN                  (0x1UL << 15U)                            /* Own address 2 enable                                    */
  #define CDD_I2C_TIMING_CLEAR_MASK           (0xF0FFFFFFU)                             /*  I2C TIMING clear register Mask                         */
  #define CDD_I2C_ISR_TXIS                    (0x1UL << 1U)                             /* Transmit interrupt status                               */
  #define CDD_I2C_ISR_STOPF                   (0x1UL << 5U)                             /* STOP detection flag                                     */
  #define CDD_I2C_CR2_AUTOEND                 (0x1UL << 25U)                            /* Automatic end mode (master mode)                        */
  #define CDD_I2C_CR2_START                   (0x1UL << 13U)                            /* START generation                                        */
  #define CDD_I2C_CR2_SADD                    (0x3FFUL << 0U)                           /* Slave address (master mode)                             */
  #define CDD_I2C_CR2_HEAD10R                 (0x1UL << 12U)                            /* 10-bit address header only read direction (master mode) */
  #define CDD_I2C_CR2_NBYTES                  (0xFFUL << 16U)                           /* Number of bytes                                         */
  #define CDD_I2C_CR2_RELOAD                  (0x1UL << 24U)                            /* NBYTES reload mode                                      */
  #define CDD_I2C_CR2_RD_WRN                  (0x1UL << 10U)                            /* Transfer direction (master mode)                        */
  #define CDD_I2C_CR2_ADD10                   (0x1UL << 11U)                            /* 10-bit addressing mode (master mode)                    */
  #define CDD_I2C_CR2_AUTOEND                 (0x1UL << 25U)                            /* Automatic end mode (master mode)                        */
  #define CDD_I2C_CR2_NACK                    (0x1UL << 15U)                            /* NACK generation (slave mode)                            */
  #define CDD_I2C_OAR1_OA1EN                  (0x1UL << 15U)                            /* Own address 1 enable                                    */

  #define CDD_I2C_DUALADDRESS_DISABLE         (0x00000000U)
  #define CDD_I2C_ADDRESSINGMODE_7BIT         (0x00000001U)
  #define CDD_I2C_DUALADDRESS_DISABLE         (0x00000000U)
  #define CDD_I2C_GENERALCALL_DISABLE         (0x00000000U)
  #define CDD_I2C_GENERATE_START_WRITE        (uint32_t)(0x80000000U | CDD_I2C_CR2_START)
  #define CDD_I2C_NOSTRETCH_DISABLE           (0x00000000U)


  void CddI2c_Init(void);
  void I2C_Transmit(uint16_t DevAddress, uint8_t* pData, uint16_t Size);

#endif /* Cdd_I2C_2024_03_06_H */
