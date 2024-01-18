#ifndef CDDEXTFLASH_2024_01_18_H
  #define CDDEXTFLASH_2024_01_18_H

  #include <stdint.h>
  #include <stdbool.h>


  /* Example of Block0 - Sector Addresses */

 /* --------------------------------------------------------------------------------------------------------
    |    Block No.     |    Block No.      |    Sector No.         |    Sector Size     |   Address Range   |
    |    (64Kbyte)     |    (32Kbyte)      |                       |      (Kbyte)       |                   |
    --------------------------------------------------------------------------------------------------------
    |                  |                   |      Sector 0         |         4          | 000000h – 000FFFh |
    |                  |      Block 0      |---------------------  |----------------------------------------
    |                  |                   |        ****           |        ****        |        ****       |
    |     Block 0      |-------------------|---------------------  |-----------------------------------------
    |                  |                   |        ****           |        ****        |        ****       |
    |                  |      Block 1      |---------------------  |----------------------------------------|
    |                  |                   |      Sector 15        |         4          | 00F000h - 00FFFFh |
    -------------------------------------------------------------------------------------------------------- * /

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
    uint64_t PageIndex;
    uint8_t  Data[IS25LP128F_PAGE_SIZE];
    uint32_t Crc;
    uint32_t Reserved;
  } FlashPage;

  typedef struct
  {
    FlashPage Pages[IS25LP128F_TOTAL_PAGES];
    //FlashPage Pages[IS25LP128F_64K_BLOCK_SIZE][16U][IS25LP128F_SECTOR_SIZE];

    uint32_t  lastProgrammedBlock;
    uint32_t  lastProgrammedSector;
    uint32_t  lastProgrammedPage;
  } FlashChip;

  void CddExtFlash_ProgramDataToFlash(FlashChip* Flash, uint8_t* Data, uint32_t DataSize);
  void CddExtFlash_CalculateCRC(FlashPage* Page);
  bool CddExtFlash_CheckLastProgrammedPage(FlashChip* Flash, uint32_t* NextBlock, uint32_t* NextSector, uint32_t* NextPage);


#endif /* CDDEXTFLASH_2024_01_18_H */
