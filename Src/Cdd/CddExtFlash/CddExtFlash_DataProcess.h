#ifndef CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
  #define CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H

  #include "stdint.h"

  /* ----------------------------------------------------------------------------------- */
  /*  IS25LP128F Defines                                                                 */
  /* ----------------------------------------------------------------------------------- */

  #define EXT_FLASH_MODE                        1           /* Fast mode */

  #define EXT_FLASH_PAGE_SIZE              0x0100  /* 256b     page size   (bits)    */
  #define EXT_FLASH_SECTOR_SIZE            0x1000  /* 4kB      sector size (bytes)   */
  #define EXT_FLASH_BLOCK_SIZE         0x00010000  /* 64kB     block size  (bytes)   */
  #define EXT_FLASH_SIZE               0X00100000  /* 1MB-8Mb  total size  (bytes)   */
  #define EXT_FLASH_PAGE_NUM               0x1000  /* 4096     pages                 */
  #define EXT_FLASH_SECTOR_NUM             0x0100  /* 256      sectors               */
  #define EXT_FLASH_BLOCK_NUM              0x0010  /* 16       blocks                */
  #define EXT_FLASH_DMA_CUTOFF                20U

  #define EXT_FLASH_RESET_EN                0x66U   /* sequence is 0x66 + 0x99 + 30us delay */
  #define EXT_FLASH_RESET                   0x99U   /* sequence is 0x66 + 0x99 + 30us delay */
  #define EXT_FLASH_W_ENABLE                0x06U
  #define EXT_FLASH_READ                    0x03U
  #define EXT_FLASH_FREAD                   0x0BU
  #define EXT_FLASH_FREAD_DUAL              0x3BU
  #define EXT_FLASH_FREAD_QUAD              0x6BU
  #define EXT_FLASH_PAGE_P                  0x02U
  #define EXT_FLASH_S_ERASE4K               0x20U
  #define EXT_FLASH_B_ERASE32K              0x52U
  #define EXT_FLASH_B_ERASE64K              0xD8U
  #define EXT_FLASH_CH_ERASE                0xC7U
  #define EXT_FLASH_POWERDOWN               0xB9U
  #define EXT_FLASH_POWERUP_ID              0xABU
  #define EXT_FLASH_JEDEC_ID                0x9FU
  #define EXT_FLASH_R_SR1                   0x05U
  #define EXT_FLASH_R_SFPD_REG              0x5AU
  #define EXT_FLASH_W_SR1                   0x01U
  #define EXT_FLASH_DUMMY                   0xFFU  /* dummy MUST be 0x00, in "read manufacturer" */
  #define SR1_BIT_BUSY                      (01U)  /* status only: 1 means busy device                                */
  #define SR1_BIT_WEL                       (02U)  /* status only: 1 means write enabled. set by W25_W_ENABLE command */

  /* bit masks of IS25LP128F SR1, SR2, SR3 registers */
  #define FLASH_READ_COMMAND       EXT_FLASH_READ


  /* ----------------------------------------------------------------------------------- */
  /*  Functions Prototypes                                                               */
  /* ----------------------------------------------------------------------------------- */

  void     Flash_Read                       (uint32_t addr, uint8_t* data, uint32_t dataSize);
  void     Flash_Write                      (uint32_t addr, uint8_t* data, uint32_t dataSize);
  void     Flash_SimpleWriteAPage           (uint32_t addr, uint8_t* data, uint32_t dataSize);
  void     Flash_WaitForWritingComplete     (void);
  void     Flash_WaitForWriteToBeEnabled    (void);
  void     Flash_SErase4k                   (uint32_t addr);
  void     Flash_BErase32k                  (uint32_t addr);
  void     Flash_BErase64k                  (uint32_t addr);
  void     Flash_ChipErase                  (void);
  void     Flash_PowerDown                  (void);
  void     Flash_ReadSFDP                   (uint8_t* data);
  void     Flash_Reset                      (void);
  uint8_t  Flash_Receive                    (uint8_t* data, uint16_t dataSize);
  void     Flash_unblockChip                (void);
  void     Flash_PowerUp                    (void);
  uint8_t  Flash_ReadDevID                  (void);
  uint8_t  Flash_ReadManufactutrerAndDevID  (void);
  uint8_t  Flash_Init                       (void);  //initialization: includes availability test and reset
  uint8_t  Flash_readStsRegister            (void);
  uint8_t  Flash_TestAvailability           (void);


#endif // CDD_EXT_FLASH_DATAPROCESS_2023_08_22_H
