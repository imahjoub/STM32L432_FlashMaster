#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdint.h>
  #include <Mcal/Mcu.h>

  /* functions prototypes */
  void    CddSpiInit(void);
  void    CddSpiCsInit(void);
  void    CddSpiCsEnable(void);
  void    CddSpiCsDisable(void);
  uint8_t CddSpiTransfer(uint8_t TxData);
  void    CddSpiReceive(uint8_t *TxPtr, uint32_t DataLen);
  void    CddSpiSend(uint8_t *RxPtr, uint32_t DataLen);

#endif // CDD_SPI_2023_08_22_H
