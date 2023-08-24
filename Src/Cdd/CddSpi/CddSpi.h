#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdint.h>
  #include <Mcal/Mcu.h>

  /* SPI1 Base address */
  #define SPI_BASE     0x40013000

  /* SPI1 registers */
  #define SPI_CR1          (*(volatile uint32_t *)(SPI_BASE + 0x00UL))
  #define SPI_CR2          (*(volatile uint32_t *)(SPI_BASE + 0x04UL))
  #define SPI_SR           (*(volatile uint32_t *)(SPI_BASE + 0x08UL))
  #define SPI_DR           (*(volatile uint32_t *)(SPI_BASE + 0x0CUL))
  #define SPI_CRCPR        (*(volatile uint32_t *)(SPI_BASE + 0x10UL))
  #define SPI_RXCRCR       (*(volatile uint32_t *)(SPI_BASE + 0x14UL))
  #define SPI_TXCRCR       (*(volatile uint32_t *)(SPI_BASE + 0x18UL))

  /* functions prototypes */
  void spi_init(void);
  uint8_t spi_transfer(uint8_t tx_data);
  void spi_read(uint8_t *rx_data, uint32_t len);
  void spi_write(uint8_t *tx_data, uint32_t len);
  void spi_cs_select(void);
  void spi_cs_deselect(void);

#endif // CDD_SPI_2023_08_22_H
