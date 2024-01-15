#ifndef CDD_EXT_FLASH_2023_08_22_H
  #define CDD_EXT_FLASH_2023_08_22_H

  #include <stdint.h>

  void CddExtFlash_WriteEnable(void);
  void CddExtFlash_Ready(void);
  void CddExtFlash_WriteReady(void);
  void CddExtFlash_WriteSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen);
  void CddExtFlash_ReadSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen);

#endif // CDD_EXT_FLASH_2023_08_22_H
