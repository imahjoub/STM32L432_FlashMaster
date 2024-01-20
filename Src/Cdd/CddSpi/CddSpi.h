#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdint.h>
  #include <Mcal/Mcu.h>

  /* functions prototypes */
  void    CddSpi_Init(void);
  void    CddSpi_CsInit(void);
  void    CddSpi_CsEnable(void);
  void    CddSpi_CsDisable(void);
  uint8_t CddSpi_TransferSingleByte(uint8_t TxData);
  uint8_t CddSpi_WriteRead(uint8_t TxData);
  void    CddSpi_WriteMultipleBytes(const uint8_t *TxPtr, const uint32_t DataLen);
  void    CddSpi_ReadMultipleBytes (      uint8_t *RxPtr, const uint32_t DataLen);

#endif // CDD_SPI_2023_08_22_H
