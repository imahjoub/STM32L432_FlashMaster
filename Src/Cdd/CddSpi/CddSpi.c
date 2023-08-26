#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Reg.h>

void SpiInit(void)
{
  // Enable clock to PortA of SPI Pins
  RCC_AHB1ENR |= (uint32_t)(1UL << 0U);

  // Enable the Spi peripheral clock
  RCC_APB2ENR |= (uint32_t)(1UL << 12U);

  // Configure GPIO pins for SPI (SPI1 on PA5, PA6, and PA7)
  GPIOA_MODER |= (uint32_t)((2U << 10U) | (2U << 12U) | (2U << 14U)); // Set PA5, PA6, PA7 to alternate function mode
  GPIOA_AFRL  |= (uint32_t)((5U << 20U) | (5U << 24U) | (5U << 28U)); // Set alternate function for PA5, PA6, PA7 (SPI1)

  // Configure GPIO pins for SPI PA4 CS
  GPIOA_MODER   |= (uint32_t)(1UL << 8U);    // Set PA4 to output mode
  GPIOA_OSPEEDR |= (uint32_t)(3UL << 8U);    // Set output speed to high
  GPIOA_PUPDR   &= (uint32_t)(~(3UL << 8U)); // No pull-up, pull-down

  // Set Software slave management
  SPI_CR1 |= (1U << 8U); // Internal slave select
  SPI_CR1 |= (1U << 9U); // Software slave management enabled

  // Baud rate configuration
  SPI_CR1 |= (uint32_t)(6UL << 3U);

  // Configure SPI
  SPI_CR1 |= (uint32_t)((0UL << 0U)| (0UL << 1U) | (1UL << 2U)); // Set master mode, clock polarity 0, clock phase 1
  SPI_CR1 |= (uint32_t)(1UL << 6U); // Enable SPI
}

void SPICsInit(void)
{
  // Enable the GPIOA peripheral clock
  RCC_AHB1ENR |= (uint32_t)(1 << 0U);

  // Set PA4 as output
  GPIOA_MODER &= ((uint32_t)~ (uint32_t)(3 << 8U));  // Clear mode bits
  GPIOA_MODER |= (uint32_t)(1 << 8U);   // Set mode to output

  // Set output type to push-pull (default)
  GPIOA_OTYPER &= (uint32_t)(~(1 << 4U));

  // Set output speed to high
  GPIOA_OSPEEDR |= (uint32_t)(3U << 8U);

  // Set no pull-up, no pull-down
  GPIOA_PUPDR &= (uint32_t)(~(3UL << 8U));
}

uint8_t SpiTransfer(uint8_t TxData)
{
  SPI_DR = (uint8_t)TxData;

  while (!(SPI_SR & (1 << 1U))); // Wait until transmission complete

  //while (!(SPI_SR & (1 << 0))); // Wait until receive buffer not empty

  return (uint8_t)(SPI_DR);
}

void SpiSend(uint8_t *TxPtr, uint32_t DataLen)
{
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    SpiTransfer(TxPtr[i]);
  }
}

void SpiReceive(uint8_t *RxPtr, uint32_t DataLen)
{
  for (uint32_t i = 0U; i < DataLen; i++)
  {
    RxPtr[i] = SpiTransfer(0xFFU);
  }
}

void SpiCsSelect(void)
{
  GPIOA_ODR &= (uint32_t)(~(1UL << 4U));
}


void SpiCsDeselect(void)
{
  GPIOA_ODR |= (uint32_t)(1UL << 4U);
}
