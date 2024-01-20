#ifndef CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
  #define CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H

  #include <stdint.h>

  void CddExtFlash_DataProcess_WritePage(const uint32_t PageIndex, const CddExtFlash_PageType* PtrPageToWrite);
  void CddExtFlash_DataProcess_ReadPage (const uint32_t PageIndex,       CddExtFlash_PageType* PtrPageToRead);
  void CddExtFlash_DataProcess_EraseSector(const uint32_t PageIndex);

#endif // CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
