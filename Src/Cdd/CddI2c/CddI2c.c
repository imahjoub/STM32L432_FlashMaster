#include <stdbool.h>

#include <Cdd/CddI2c/CddI2c.h>
#include <Mcal/Reg.h>


void CddI2c_Init(void)
{
  /*---------------------  GPIO configuration  ---------------------*/
  /* Configure SCL (PB6) and SDA (PB7) as Alternate Function, Open-drain, Pull-up */
  /* Enable clock for GPIOB */
  RCC_AHB1ENR |= (uint32_t)(1UL << 1U);

  /* Configure GPIO pins for I2C1 on PB6 & PB7   */
  /* Set PF0 & PF1 to alternate function mode    */
  GPIOB_MODER |= (uint32_t)((2UL << 12U) | (2UL << 14U));

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
  RCC_APB1ENR |= (uint32_t)(1UL << 21U);

  /* Fully reset the I2C1 */
  I2C1_CR1 |= (uint32_t)(1UL << 15U);
  I2C1_CR1 &= (uint32_t)(~(1UL << 15U));

  /* Set the peripheral clock frequency to 16MHz */
  I2C1_CR2 |= (uint32_t)(16UL << 0U);

  /* Set the frequency of I2C SCL line to 100kHz  */
  I2C1_CCR |= (uint32_t)(80UL << 0U);

  I2C1_TRISE |= 0x10; /* Configure maximum rise tim

  /* Enable I2C1 */
  I2C1_CR1 |= (uint32_t)(1UL << 0U);
}

void CddI2c_StartTransmission(uint8_t address, uint8_t direction)
{
  /* Generate start condition */
  I2C1_CR1 |= (uint32_t)(1UL << 8U);

  /* Wait for the start condition to be sent */
  while (!(I2C1_SR1 & (uint32_t)(1UL << 0U)));

  /* Send slave address and direction */
  I2C1_DR = (address << 1) | direction;

  /* Wait for address to be acknowledged */
  if (direction == 0)
  {
    while (!(I2C1_SR1 & ((uint32_t)(1UL << 1U)))); /* I2C_SR1_ADDR */
  }

  else
  {
    while (!(I2C1_SR1 & ((uint32_t)(1UL << 1U))));  /* I2C_SR1_ADDR */
  }

  /* Clear the ADDR flag by reading SR1 and SR2 */
  volatile uint32_t temp = I2C1_SR1 | I2C1_SR2;

  (void)temp;
}


void CddI2c_TransferSingleByte(uint8_t data)
{
  /* Send the data */
  I2C1_DR = data;
  /* Wait for the data to be transferred */
  while (!(I2C1_SR1 & (uint32_t)(1UL << 7U)));
}

uint8_t CddI2c_ReadAck(void)
{
  /* Enable ACK bit for acknowledgment */
  I2C1_CR1 |= (uint32_t)(1UL << 10U); /*I2C1_CR1_ACK */

  /* Wait for the byte to be received */
  while (!(I2C1_SR1 & ((uint32_t)(1UL << 6U))));

  /* Return the data in the data register */
  return (uint8_t)I2C1_DR;
}

uint8_t CddI2c_ReadNack(void)
{
  /* Disable ACK bit for non-acknowledgment */
  I2C1_CR1 &= (uint32_t)(~(1UL << 10U));  /* I2C_CR1_ACK */

  /* Generate stop condition after byte is received */
  I2C1_CR1 |= (uint32_t)(1UL << 9U);

  /* Wait for the byte to be received */
  while (!(I2C1_SR1 & ((uint32_t)(1UL << 6U))));

  /* Return the data in the data register */
  return (uint8_t)I2C1_DR;
}

void CddI2c_Stop(void)
{
  /* Generate stop condition */
  I2C1_CR1 |= (uint32_t)(1UL << 9U);
}

