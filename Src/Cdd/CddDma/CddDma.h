#ifndef CDD_DMA_2023_08_27_H
  #define CDD_DMA_2023_08_27_H

  #include <stdio.h>

  void Dma2Stream3SpiTxInit(void);
  void Dma2Stream2SpiRxInit(void);
  void Dma2Stream2SpiReceive(uint32_t RxData, const size_t DataLen);
  void Dma2Stream3SpiSend(uint32_t TxData, const size_t DataLen);

#endif /* CDD_DMA_2023_08_27_H */


