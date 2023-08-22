#include <Cdd/CddSpi/CddSpi.h>

void spi_init(void)
{
  // Enable the Spi peripheral clock
  RCC_APB2ENR |= (1UL << 12);

  // Configure GPIO pins for SPI (SPI1 on PA5, PA6, and PA7)
  GPIOA_MODER |= (2U << 10) | (2U << 12) | (2U << 14); // Set PA5, PA6, PA7 to alternate function mode
  GPIOA_AFRL  |= (5U << 20) | (5U << 24) | (5U << 28); // Set alternate function for PA5, PA6, PA7 (SPI1)

  // Configure GPIO pins for SPI PA4 CS
  GPIOA_MODER   |=  (1UL << 8); // Set PA4 to output mode
  GPIOA_OSPEEDR |=  (3UL << 8); // Set output speed to high
  GPIOA_PUPDR   &= ~(3UL << 8); // No pull-up, pull-down

  // Configure SPI
  SPI_CR1 = (uint32_t)((0UL << 0) | (0UL << 1) | (1UL << 2)); // Set master mode, clock polarity 0, clock phase 1
  SPI_CR1 |= (1 << 6); // Enable SPI
}

uint8_t spi_transfer(uint8_t tx_data)
{
  SPI_DR = tx_data;

  while (!(SPI_SR & (1 << 1))); // Wait until transmission complete

  while (!(SPI_SR & (1 << 0))); // Wait until receive buffer not empty

  return (uint8_t)(SPI_DR);
}

void spi_write(uint8_t *tx_data, uint32_t len)
{
  for (uint32_t i = 0; i < len; i++)
  {
    spi_transfer(tx_data[i]);
  }
}

void spi_read(uint8_t *rx_data, uint32_t len)
{
  for (uint32_t i = 0; i < len; i++)
  {
    rx_data[i] = spi_transfer(0xFF);
  }
}

void spi_cs_select(void)
{
  GPIOA_ODR &= (uint32_t)(~(1UL << 4));
}


void spi_cs_deselect(void)
{
  GPIOA_ODR |= (uint32_t)(1UL << 4);
}
