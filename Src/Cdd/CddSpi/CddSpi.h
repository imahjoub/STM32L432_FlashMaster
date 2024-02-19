#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdbool.h>
  #include <stdint.h>

  #include <Mcal/Mcu.h>

  /* functions prototypes */
  void    CddSpi_Init(void);
  void    CddSpi_CsInit(void);
  void    CddSpi_CsEnable(void);
  void    CddSpi_CsDisable(void);
  uint8_t CddSpi_TransferSingleByte(uint8_t TxData);
  uint8_t CddSpi_WriteRead(uint8_t TxData);
  bool    CddSpi_WriteMultipleBytes(const uint8_t* pSrc,  const unsigned DataLen);
  bool    CddSpi_ReadMultipleBytes (      uint8_t* pDest, const unsigned DataLen);

#endif // CDD_SPI_2023_08_22_H
