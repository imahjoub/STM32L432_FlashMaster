#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Reg.h>

void CddSpiInit(void)
{
  /*---------------------  GPIO configuration  ---------------------*/
  /* Enable clock to PortA of SPI Pins */
  RCC_AHB1ENR |= (uint32_t)(1UL << 0U);

  /* Configure GPIO pins for SPI (SPI1 on PA5, PA6, and PA7) */
  /* Set PA5, PA6, PA7 to alternate function mode            */
  /* Set alternate function for PA5, PA6, PA7 (SPI1)         */
  GPIOA_MODER |= (uint32_t)((2U << 10U) | (2U << 12U) | (2U << 14U));
  GPIOA_AFRL  |= (uint32_t)((5U << 20U) | (5U << 24U) | (5U << 28U));

  /*---------------------  SPI configuration  ---------------------*/
  /* Enable the Spi peripheral clock */
  RCC_APB2ENR |= (uint32_t)(1UL << 12U);

  /* Set Software slave management     */
  /* Internal slave select             */
  /* Software slave management enabled */
  SPI_CR1 |= (uint32_t)(1U << 8U);
  SPI_CR1 |= (uint32_t)(1U << 9U);

  /* Baud rate configuration */
  SPI_CR1 |= (uint32_t)(6UL << 3U);

  /* Configure SPI */
  /* Set master mode, clock polarity 0, clock phase 1 */
  SPI_CR1 |= (uint32_t)((0UL << 0U)| (0UL << 1U) | (1UL << 2U));

  /* Enable Tx/Rx buffer DMA  */
  SPI_CR2 |= (uint32_t)((1UL << 0U) | (1UL << 1U));

  /* Enable SPI */
  SPI_CR1 |= (uint32_t)(1UL << 6U);
}

void CddSpiCsInit(void)
{
  /* Enable the GPIOA peripheral clock */
  RCC_AHB1ENR |= (uint32_t)(1UL << 0U);

  /* Configure GPIO pins for SPI PA4 CS */
  /* Set PA4 to output mode             */
  /* Set output speed to high           */
  /* No pull-up, pull-down              */
  GPIOA_MODER   |= (uint32_t)(1UL << 8U);
  GPIOA_MODER   &= (uint32_t)(~(1UL << 9U));
  //GPIOA_OSPEEDR |= (uint32_t)(3UL << 8U);
  //GPIOA_PUPDR   &= (uint32_t)(~(3UL << 8U));
}

uint8_t CddSpiTransfer(uint8_t TxData)
{
  SPI_DR = (uint8_t)TxData;

  /* Wait until transmission complete */
  while (!(SPI_SR & (1UL << 1U)));

  /* TBD check why this following check does not work */
  /* while (!(SPI_SR & (1 << 0))); /* Wait until receive buffer not empty */
  return (uint8_t)(SPI_DR);
}

void CddSpiSend(uint8_t *TxPtr, uint32_t DataLen)
{
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    CddSpiTransfer(TxPtr[i]);
  }
}

void CddSpiReceive(uint8_t *RxPtr, uint32_t DataLen)
{
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    RxPtr[i] = CddSpiTransfer(0xFFU);
  }
}

void CddSpiCsEnable(void)
{
  GPIOA_ODR &= (uint32_t)(~(1UL << 4U));
}


void CddSpiCsDisable(void)
{
  GPIOA_ODR |= (uint32_t)(1UL << 4U);
}
