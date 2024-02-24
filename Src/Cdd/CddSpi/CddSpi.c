#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Reg.h>

void CddSpi_Init(void)
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
  SPI_CR1 |= (uint32_t)(3UL << 3U);

  /* Configure SPI */
  /* Set master mode, clock polarity 0, clock phase 0 */
  SPI_CR1 |= (uint32_t)((0UL << 0U)| (0UL << 1U) | (1UL << 2U));

  /* Enable Tx/Rx buffer DMA  */
  SPI_CR2 |= (uint32_t)((1UL << 0U) | (1UL << 1U));

  /* Enable SPI */
  SPI_CR1 |= (uint32_t)(1UL << 6U);
}

void CddSpi_CsInit(void)
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

bool CddSpi_WriteMultipleBytes(const uint8_t* pSrc, const unsigned DataLen)
{
  for(unsigned index = (unsigned) 0U; index < DataLen; ++index)
  {
    (void) CddSpi_TransferSingleByte(pSrc[index]);
  }

  /* TBD make a significant check here */
  return true;
}

bool CddSpi_ReadMultipleBytes(uint8_t* pDest, const unsigned DataLen)
{
  for(unsigned index = (unsigned) 0U; index < DataLen; ++index)
  {
    pDest[index] = CddSpi_TransferSingleByte(0xFFU);
  }

  /* TBD make a significant check here */
  return true;
}


uint8_t CddSpi_TransferSingleByte(const uint8_t TxData)
{
  /* Put data into TXFIFO */
  SPI_DR = (uint8_t)TxData;

  /* Wait until transmission complete */
  while (!(SPI_SR & (1UL << 1U)));

  /* Wait until receive buffer not empty */
  while (!(SPI_SR & (1UL << 0U)));

  /* Empty the RXFIFO */
  return (uint8_t)(SPI_DR);
}

uint8_t CddSpi_WriteRead(uint8_t TxData)
{
  uint8_t ReadBuff = 0U;
  CddSpi_TransferSingleByte(TxData);
  ReadBuff = CddSpi_TransferSingleByte(0xFFU);
  return ReadBuff;
}

void CddSpi_CsEnable(void)
{
  /* Clear the CE bit */
  GPIOA_ODR &= (uint32_t)(~(1UL << 4U));
}


void CddSpi_CsDisable(void)
{
  /* Set the CE bit */
  GPIOA_ODR |= (uint32_t)(1UL << 4U);
}
