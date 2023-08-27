#ifndef CDD_EXT_FLASH_2023_08_22_H
  #define CDD_EXT_FLASH_2023_08_22_H

  #include <Cdd/CddSpi/CddSpi.h>

  void CddExtFlashWriteEnable(void);
  void CddExtFlashWaitForRead(void);
  void CddExtFlashWriteSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen);

#endif // CDD_EXT_FLASH_2023_08_22_H
