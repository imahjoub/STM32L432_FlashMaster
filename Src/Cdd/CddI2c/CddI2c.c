#include <stdbool.h>

#include <Cdd/CddI2c/CddI2c.h>
#include <Mcal/Reg.h>

#define I2C_CR2_START  (1U << 13)
#define I2C_CR2_STOP   (1U << 14)
#define I2C_ISR_TXIS   (1U << 1)
#define I2C_ISR_TC     (1U << 6)

void CddI2c_Init(void)
{
  /*---------------------  GPIO configuration  ---------------------*/
  /* Configure SCL (PB6) and SDA (PB7) as Alternate Function, Open-drain, Pull-up */
  /* Enable clock for GPIOB */
  RCC_AHB2ENR |= (uint32_t)(1UL << 1U);

  /* Configure GPIO pins for I2C1 on PB6 & PB7   */
  /* Set PF0 & PF1 to alternate function mode    */
  //GPIOB_MODER |= (uint32_t)((2UL << 12U) | (2UL << 14U));
  GPIOB_MODER &= ~(1U << 12U);
  GPIOB_MODER |=  (1U << 13U);

  GPIOB_MODER &= ~(1U << 14U);
  GPIOB_MODER |= (1U << 15U);

  /* Set alternate function for PF0 & PF1 (I2C1)  */
  GPIOB_AFRL  |= (uint32_t)((4UL << 24U) | (4UL << 28U));

  /* Set pins to output open-drain */
  GPIOB_OTYPER |= (uint32_t)((1UL << 6U) | (1UL << 7U));

  /* Set pins speed to high */
  GPIOB_OSPEEDR |= (uint32_t)((3UL << 12U) | (3UL << 14U));

  /* Clear pull-up/pull-down bits */
  GPIOB_PUPDR &= ~((3U << (2 * 6)) | (3U << (2 * 7)));

  /* Enable pull-up */
  GPIOB_PUPDR |= (1 << (2 * 6)) | (1 << (2 * 7));


  /*--------------------- I2C1 configuration  ---------------------*/
  /* Enable clock  for I2C1 */
  RCC_APB1ENR1 |= (uint32_t)(1UL << 21U);

  /* (2) Reset I2C1 */
  RCC_APB1RSTR1 |= (uint32_t)(1UL << 21U);
  RCC_APB1RSTR1 &= (uint32_t)(~(1UL << 21U));

  /* (3) Set peripheral clock frequency, timing for 100Khz */

  /* tI2CCLK = 1 / (System Clock) = 1 / 80MHz = 12.5 ns
     tPRESC = (PRESC + 1) * tI2CCLK = (3 + 1) * 12.5ns = 50 ns
     SCL High and Low Periods :
     For SCLH and SCLL, tSCLH = (SCLH + 1) x tPRESC & tSCLL = (SCLL + 1) x tPRESC
     tSCLH = (99 + 1) * 100 ns = 10000 ns(or 10 us)
     tSCLL = (99 + 1) * 100 ns = 10000 ns(or 10 us)
     Total SCL Period :
     SCL Period(tSCL) = tSCLH + tSCLL = 10 us + 10 us = 20 us
     I2C Clock Frequency :
     fI2C = 1 / tSCL = 1 / 10 us = 100kHz */

  I2C1_TIMINGR = (uint32_t)((3 << 28) |    // PRESC
                            (0 << 20) |    // SCLDEL
                            (3 << 16) |    // SDADEL
                            (99 << 8) |    // SCLH
                            (99 << 0));    // SCLL

  /* Enable I2C1 */
  I2C1_CR1 |= (uint32_t)(1UL << 0U);
}

void CddI2c_StartTransmission(uint8_t DeviceAddress, size_t DataSize, uint8_t WriteReadMode)
{
  uint32_t CddI2cTempReg = I2C1_CR2;

  /* Clearing address, number of bytes, reload, autoend, and read/write bits */
  CddI2cTempReg &= (uint32_t)(~((0xFFUL << 0U) | (0xFFUL << 16U) | (1UL << 24U) | (1UL << 25U) | (1UL << 10U)));

  /* Setting address, number of bytes, and direction */
  CddI2cTempReg |= (uint32_t)(((DeviceAddress & 0xFF) << 1U) | ((DataSize << 16U) & (0xFFUL << 16U)) | (((WriteReadMode & 0x01UL) << 10U) & (1UL << 10U)));

  /* Setting start bit */
  CddI2cTempReg |= (uint32_t)(1UL << 13U);

  I2C1_CR2 = CddI2cTempReg;

}

void CddI2c_TransferMultipleByte(uint8_t* Data, size_t DataSize)
{
  for (uint8_t i = 0U; i < DataSize; i++)
  {
    while (!(I2C1_ISR & (1UL << 1U))) { /* Wait until TX buffer is empty */ }

    /* Write data to transmit data register */
    I2C1_TXDR = Data[i] & 0xFFU;
  }

  /* Wait until the transfer is complete */
  while (!(I2C1_ISR & (1UL << 6U)));
}

void CddI2c_TransferSingleByte(uint8_t Data)
{
  while (!(I2C1_ISR & (1UL << 1U))) { /* Wait until TX buffer is empty */ }

  /* Write single byte to transmit data register */
  I2C1_TXDR = (uint32_t)(Data & 0xFFU);

  /* Wait until the transfer is complete */
  while (!(I2C1_ISR & (1UL << 6U)));
}

void CddI2c_Stop(void)
{
  /* If the stop flag is not set */
  if (!(I2C1_ISR & (1UL << 5U)))
  {
    /* Generate a stop condition */
    I2C1_CR2 |= (uint32_t)(1UL << 14U);

    /* Wait until the stop flag is set */
    while (!(I2C1_ISR & (1UL << 5U)));
  }

  /* Clear the stop flag by writing '1' to it */
  I2C1_ICR |= (uint32_t)(1UL << 5U);
}
