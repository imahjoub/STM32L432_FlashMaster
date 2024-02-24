#ifndef CDDEXTFLASH_2024_01_18_H
  #define CDDEXTFLASH_2024_01_18_H

  #include <stdint.h>
  #include <stdbool.h>


  /* Block/Sector Addresses of IS25LP128 */

  /* -------------------------------------------------------------------------------------------------------------
    |     Block No.    |      Blocks       |        Sectors        |         Pages          |    Address Range    |
    |    (64Kbyte)     |    (32Kbyte)      |   (4 Kbyte per Sec)   |  (256 bytes per Page)  |                     |
    |------------------|-------------------|-----------------------|------------------------|---------------------|
    |                  |                   |       Sector 0        |     Page0 - Page15     |  000000h – 000FFFh  |
    |                  |      Block 0      |-----------------------|- ----------------------|---------------------|
    |                  |                   |         ****          |         ****           |        ****         |
    |     Block 0      |-------------------|-----------------------|------------------------|---------------------|
    |                  |                   |         ****          |         ****           |        ****         |
    |                  |      Block 1      |-----------------------|------------------------|---------------------|
    |                  |                   |       Sector 15       |     Page0 - Page15     |   00F000h - 00FFFFh |
    |-------------------------------------------------------------------------------------------------------------|
    |        *                   *                    *                        *                       *          |
    |        *                   *                    *                        *                       *          |
    |        *                   *                    *                        *                       *          |
    |-------------------------------------------------------------------------------------------------------------|
    |                  |                   |      Sector 4080      |     Page0 - Page15     |  FF0000h – FF0FFFh  |
    |                  |     Block 510     |-----------------------|- ----------------------|---------------------|
    |                  |                   |         ****          |         ****           |        ****         |
    |    Block 255     |-------------------|-----------------------|------------------------|---------------------|
    |                  |                   |         ****          |         ****           |        ****         |
    |                  |     Block 511     |-----------------------|------------------------|---------------------|
    |                  |                   |       Sector 4095     |     Page0 - Page15     |  FFF000h – FFFFFFh  |
     ------------------------------------------------------------------------------------------------------------- */

  /* Define IS25LP128F commands */
  #define IS25LP128F_CMD_WRITE_ENABLE   (uint8_t)0x06U
  #define IS25LP128F_CMD_PAGE_PROGRAM   (uint8_t)0x02U
  #define IS25LP128F_CMD_NORMAL_READ    (uint8_t)0x03U
  #define IS25LP128F_CMD_SEC_ERASE      (uint8_t)0xD7U
  #define IS25LP128F_CMD_SEC_CER        (uint8_t)0xC7U
  #define IS25LP128F_CMD_READ_STATUS    (uint8_t)0x05U
  #define IS25LP128F_CMD_RDJDID         (uint8_t)0x9FU
  #define IS25LP128F_WIP                (uint8_t)0x01U  /* Write In Progress Bit */
  #define IS25LP128F_WEL                (uint8_t)0x02U  /* Write Enable Latch  */



  #define IS25LP128F_PAGE_SIZE              (uint32_t) UINT32_C(256)
  #define IS25LP128F_PAGES_NUM_USED         (uint32_t) UINT32_C(8)
  #define IS25LP128F_PAGES_GRANULAR_BORDER  (uint32_t) UINT32_C(4096)
  //#define IS25LP128F_NUM_32K_BLOCKS         (uint16_t)512U
  //#define IS25LP128F_NUM_64K_BLOCKS         (uint16_t)256U
  //#define IS25LP128F_PAGES_NUM_IN_SEC       (uint16_t)(UINT8_C(16))
  //#define IS25LP128F_PAGES_NUM_IN_32K_BLOCK (uint32_t)(IS25LP128F_PAGES_NUM_IN_SEC * UINT8_C(8))
  //#define IS25LP128F_PAGES_NUM_IN_64K_BLOCK (uint32_t)(IS25LP128F_PAGES_NUM_IN_SEC * UINT8_C(16))
  //#define IS25LP128F_PAGES_NUM_IN_CHIP      (uint32_t)(IS25LP128F_PAGES_NUM_IN_64K_BLOCK * UINT16_C(256))

  typedef struct CddExtFlash_HashContextType
  {
    uint8_t HashData[16U];
  } CddExtFlash_HashContextType;

  typedef struct CddExtFlash_PageType
  {
    uint64_t                    Data;
    uint8_t                     Reserved[256U - sizeof(uint64_t) - (1U * sizeof(uint32_t)) -  sizeof(CddExtFlash_HashContextType)];
    uint32_t                    WriteCounter;
    CddExtFlash_HashContextType HashContext;
  } CddExtFlash_PageType;

  #if(__STDC_VERSION__ >= 202311L)
  static_assert(sizeof(CddExtFlash_PageType) == 256U, "Error: Wrong configuration size of client flash page structure");
  #endif

  void     CddExtFlash_Init(void);
  bool     CddExtFlash_WritePage(const CddExtFlash_PageType* ptrPageToWrite);
  bool     CddExtFlash_ReadPage(CddExtFlash_PageType* ptrPageToRead);
  bool     CddExtFlash_EraseSector(void);
  bool     CddExtFlash_EraseChip(void);
  uint32_t CddExtFlash_GetActivePageIndex(void);
  uint32_t CddExtFlash_GetActiveWriteCounter(void);


#endif /* CDDEXTFLASH_2024_01_18_H */
