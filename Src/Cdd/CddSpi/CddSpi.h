#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdint.h>
  #include <Mcal/Mcu.h>

  /* functions prototypes */
  void spi_init(void);
  uint8_t spi_transfer(uint8_t tx_data);
  void spi_read(uint8_t *rx_data, uint32_t len);
  void spi_write(uint8_t *tx_data, uint32_t len);
  void spi_cs_select(void);
  void spi_cs_deselect(void);

#endif // CDD_SPI_2023_08_22_H
