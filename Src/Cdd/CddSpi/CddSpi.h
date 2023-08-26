#ifndef CDD_SPI_2023_08_22_H
  #define CDD_SPI_2023_08_22_H

  #include <stdint.h>
  #include <Mcal/Mcu.h>

  /* functions prototypes */
  void    SpiInit(void);
  void    SPICsInit(void);
  void    SpiCsEnable(void);
  void    SpiCsDisable(void);
  uint8_t SpiTransfer(uint8_t TxData);
  void    SpiReceive(uint8_t *TxPtr, uint32_t DataLen);
  void    SpiSend(uint8_t *RxPtr, uint32_t DataLen);

#endif // CDD_SPI_2023_08_22_H
