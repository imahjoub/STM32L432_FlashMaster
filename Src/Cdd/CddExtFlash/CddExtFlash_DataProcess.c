#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Cdd/CddSpi/CddSpi.h>

static void CddExtFlash_DataProcess_WriteEnable(void);
static void CddExtFlash_DataProcess_WriteIsEnabled(void);
static void CddExtFlash_DataProcess_Ready(void);


/* Function to enable writing */
void CddExtFlash_DataProcess_GetChipID(uint8_t* RxPtr)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send RDID command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_RDJDID);

  /* Get the RDID */
  CddSpi_ReadMultipleBytes(RxPtr, 3U);

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to enable writing */
static void CddExtFlash_DataProcess_WriteEnable(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send Write Enable command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_WRITE_ENABLE);

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Check if write is enabled */
  CddExtFlash_DataProcess_WriteIsEnabled();
}

/* Function to wait until the chip is not busy */
static void CddExtFlash_DataProcess_Ready(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* TBD Add timeout error check  */
  /* Check if device is still busy */
  while (CddSpi_WriteRead(IS25LP128F_CMD_READ_STATUS) & (IS25LP128F_WIP));

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to wait until the chip write enabled */
void CddExtFlash_DataProcess_WriteIsEnabled(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* TBD Add timeout error check */
  /* Poll Status Register until write enable latch is set */
  while (!(CddSpi_WriteRead(IS25LP128F_CMD_READ_STATUS) & (IS25LP128F_WEL)));

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to write data to a sector */
void CddExtFlash_DataProcess_WritePage(const unsigned unPageIndex, const CddExtFlash_PageType* ptrPageToWrite)
{
  /* Chip address */
  const uint32_t PageAddress = (unPageIndex * IS25LP128F_PAGES_GRANULAR_BORDER);

  /* Enable writing */
  CddExtFlash_DataProcess_WriteEnable();

  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send Page Program command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_PAGE_PROGRAM);

  /* Address byte 2 */
  CddSpi_TransferSingleByte((PageAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_TransferSingleByte((PageAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_TransferSingleByte((PageAddress >>  0U) & 0xFFU);

  /* Write data     */
  CddSpi_WriteMultipleBytes((const uint8_t*) ptrPageToWrite, (unsigned) sizeof(CddExtFlash_PageType));

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();
}

/* Function to read data from a sector */
void CddExtFlash_DataProcess_ReadPage(const unsigned unPageIndex, CddExtFlash_PageType* ptrPageToRead)
{
   /* Chip address */
   const uint32_t PageAddress = (unPageIndex * IS25LP128F_PAGES_GRANULAR_BORDER);

  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send read command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_NORMAL_READ);

  /* Address byte 2 */
  CddSpi_TransferSingleByte((PageAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_TransferSingleByte((PageAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_TransferSingleByte((PageAddress >>  0U) & 0xFFU);

  /* Write data */
  CddSpi_ReadMultipleBytes((uint8_t*) ptrPageToRead, (unsigned) sizeof(CddExtFlash_PageType));

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();
}

/* Function to erase data from a sector */
void CddExtFlash_DataProcess_EraseSector(const unsigned unPageIndex)
{
   /* Chip address */
   const uint32_t SectorAddress = (unPageIndex * IS25LP128F_PAGES_GRANULAR_BORDER);

  /* Enable writing */
  CddExtFlash_DataProcess_WriteEnable();

  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send erase sector command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_SEC_ERASE);

  /* Address byte 2 */
  CddSpi_TransferSingleByte((SectorAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_TransferSingleByte((SectorAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_TransferSingleByte((SectorAddress >>  0U) & 0xFFU);

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();
}

void CddExtFlash_DataProcess_EraseChip(void)
{
  /* Enable writing */
  CddExtFlash_DataProcess_WriteEnable();

  /* Chip select enable */
  CddSpi_CsEnable();
  /* Send erase sector command */
  CddSpi_TransferSingleByte(IS25LP128F_CMD_SEC_CER);
  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();

}

void CddExtFlash_DataProcess_PreInit(void)
{
  CddExtFlash_DataProcess_EraseChip();
}

