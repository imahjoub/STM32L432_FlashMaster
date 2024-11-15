#ifndef CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
  #define CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H

  #include <stdint.h>
  #include <Cdd/CddExtFlash/CddExtFlash.h>

  void CddExtFlash_DataProcess_WritePage(const unsigned unPageIndex, const CddExtFlash_PageType* ptrPageToWrite);
  void CddExtFlash_DataProcess_ReadPage(const unsigned unPageIndex, CddExtFlash_PageType* ptrPageToRead);
  void CddExtFlash_DataProcess_GetChipID(uint8_t* RxPtr);
  void CddExtFlash_DataProcess_EraseSector(const unsigned unPageIndex);
  void CddExtFlash_DataProcess_EraseChip(void);
  void CddExtFlash_DataProcess_PreInit(void);

#endif // CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
