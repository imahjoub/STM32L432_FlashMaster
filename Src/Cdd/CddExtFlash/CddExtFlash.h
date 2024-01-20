#ifndef CDDEXTFLASH_2024_01_18_H
  #define CDDEXTFLASH_2024_01_18_H

  #include <stdint.h>
  #include <stdbool.h>


  /* Example of Block0 - Sector Addresses */

 /* -------------------------------------------------------------------------------------------------------- -------------------
    |    Block No.     |    Block No.      |    Sector No.         |    Sector Size     |      Pages        |   Address Range   |
    |    (64Kbyte)     |    (32Kbyte)      |                       |      (4 Kbyte)     |    (256Bytes)     |                   |
    -------------------------------------------------------------------------------------------------------- -------------------
    |                  |                   |      Sector 0         |         4          |  Page0 - Page15   | 000000h – 000FFFh |
    |                  |      Block 0      |---------------------  |---------------------------------------- -------------------
    |                  |                   |        ****           |        ****        |  Page0 - Page15   |        ****       |
    |     Block 0      |-------------------|---------------------  |-------------------------------------------------------------
    |                  |                   |        ****           |        ****        |  Page0 - Page15   |        ****       |
    |                  |      Block 1      |---------------------  |----------------------------------------|-------------------|
    |                  |                   |      Sector 15        |         4          |  Page0 - Page15   | 00F000h - 00FFFFh |
    -------------------------------------------------------------------------------------------------------- ------------------- * /

  /* Define IS25LP128F commands */
  #define IS25LP128F_CMD_WRITE_ENABLE   (uint8_t)0x06U
  #define IS25LP128F_CMD_PAGE_PROGRAM   (uint8_t)0x02U
  #define IS25LP128F_CMD_NORMAL_READ    (uint8_t)0x03U
  #define IS25LP128F_CMD_SEC_ERASE      (uint8_t)0xD7U
  #define IS25LP128F_CMD_READ_STATUS    (uint8_t)0x05U
  #define IS25LP128F_CMD_RDJDID         (uint8_t)0x9FU


  #define IS25LP128F_PAGE_SIZE      (uint16_t)256U
  #define IS25LP128F_NUM_32K_BLOCKS (uint16_t)512U
  #define IS25LP128F_NUM_64K_BLOCKS (uint16_t)256U
  #define IS25LP128F_SECTOR_SIZE    (uint16_t)(16U * IS25LP128F_PAGE_SIZE)
  #define IS25LP128F_32K_BLOCK_SIZE (uint16_t)(IS25LP128F_SECTOR_SIZE / 8U)
  #define IS25LP128F_64K_BLOCK_SIZE (uint16_t)(IS25LP128F_SECTOR_SIZE / 16)
  #define IS25LP128F_TOTAL_PAGES    (uint32_t)(IS25LP128F_SECTOR_SIZE * 16U)

  typedef struct
  {
    uint64_t Data;
    uint8_t  Reserved[256U - sizeof(uint64_t) - (2U * sizeof(uint32_t))];
    uint32_t WriteCounter;
    uint32_t CrcValue;
  } CddExtFlash_PageType;

  //static_assert(sizeof(CddExtFlash_PageType) == 256U, "Error: Wrong configuration size of the flash page structure");

  void CddExtFlash_Init                     (void);
  uint32_t CddExtFlash_GetActivePageIndex   (void);
  uint32_t CddExtFlash_GetActiveWriteCounter(void);
  bool CddExtFlash_EraseSector(void);
  bool CddExtFlash_WritePage(const  CddExtFlash_PageType* PtrPageToWrite);
  bool CddExtFlash_ReadPage (       CddExtFlash_PageType* PtrPageToRead);


#endif /* CDDEXTFLASH_2024_01_18_H */
