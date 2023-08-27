#ifndef CDD_EXT_FLASH_2023_08_22_H
  #define CDD_EXT_FLASH_2023_08_22_H

  #include <Cdd/CddSpi/CddSpi.h>

  // Define IS25LP128F commands
  #define CMD_WRITE_ENABLE  0x06
  #define CMD_PAGE_PROGRAM  0x02

  void CddExtFlashWriteEnable(void);
  void CddExtFlashWaitForRead(void);
  void CddExtFlashWriteSector(uint32_t sector_address, uint8_t *data, uint32_t len);

#endif // CDD_EXT_FLASH_2023_08_22_H
