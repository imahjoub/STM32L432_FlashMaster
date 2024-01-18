#ifndef CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
  #define CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H

  #include <stdint.h>

  void CddExtFlash_WriteEnable(void);
  void CddExtFlash_Ready(void);
  void CddExtFlash_WriteReady(void);
  void CddExtFlash_WritePage(uint32_t PageAddress, uint8_t *TxPtr, uint32_t DataLen);
  void CddExtFlash_Read(uint32_t Address, uint8_t *RxPtr, uint32_t DataLen);
  void CddExtFlash_EraseSector(uint32_t SectorAddress);
  void CddExtFlash_GetChipID(uint8_t* RxPtr);

#endif // CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
