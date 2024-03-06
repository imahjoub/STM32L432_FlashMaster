#include <Cdd/CddI2c/CddI2c.h>
#include <Mcal/Reg.h>

/*
  DMA1_Channel1_stream5 I2C_RX
  DMA1_Channel1_stream5 I2C_TX

  PB8 I2C1_SCL
  PB9 I2C1_SDA
*/


void CddI2c_Init(void)
{
  /* ------- GPIO Configuration ------- */
  /* Enable the Clock to GPIOB */
  RCC_AHB1ENR = (uint32_t)(1UL << 1U);

  /* Set the PB8 and PB9 to alternate function, (AF4) */
  GPIOB_MODER |=  (uint32_t)((2UL << 16U) | (2UL << 18U));
  GPIOB_AFRH  |=  (uint32_t)((4UL << 0U)  | (4UL << 1U));

  /* Set output type of PB8 and PB9 into Output open-drain */
  GPIOB_OTYPER |= (uint32_t)((1UL << 8U) | (1UL << 9U));


  /* ------- I2C Configuration ------- */
  /* Enable clock access to I2C1 */
  RCC_APB1ENR |= (uint32_t)(1UL << 21U);

  /* Reset I2C module */
  I2C_CR1     |= (uint32_t)(1UL << 15U);

  /* Release the reset */
  I2C_CR1     &= (uint32_t)(~(1UL << 15U));

  /* Enable clock stretching */
  I2C_CR1     &= (uint32_t)(~(1UL << 7U));

  /* Disable General call */
  I2C_CR1     &= (uint32_t)(~(1UL << 6U));

  /* Select to use DMA */
  I2C_CR2     |= (uint32_t)(1UL << 11U);

  /* Set DMA last transfer */
  I2C_CR2     |= (uint32_t)(1UL << 12U);

  /* Peripheral clock frequency */
  I2C_CR2     |= (uint32_t)(16UL << 0U);


}
