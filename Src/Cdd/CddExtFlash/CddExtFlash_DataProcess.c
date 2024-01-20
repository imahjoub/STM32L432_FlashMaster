#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Cdd/CddSpi/CddSpi.h>

/*                Static functions                     */
static void CddExtFlash_DataProcess_WriteEnable   (void);
static void CddExtFlash_DataProcess_Ready         (void);
static void CddExtFlash_DataProcess_WriteIsEnabled(void);


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

  /* TBD Add timeout error check */
  /* Poll Status Register until busy bit is cleared */
  while (CddSpi_WriteRead(IS25LP128F_CMD_READ_STATUS) & (0x01U));

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to wait until the chip write enabled */
static void CddExtFlash_DataProcess_WriteIsEnabled(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* TBD Add timeout error check */
  /* Poll Status Register until write enable latch is set */
  while (!(CddSpi_WriteRead(IS25LP128F_CMD_READ_STATUS) & (1UL << 1U)));

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to write data to a sector */
void CddExtFlash_DataProcess_WritePage(const uint32_t PageIndex, const CddExtFlash_PageType* PtrPageToWrite)
{
  /* Chip Address */
  const uint32_t PageAddress = (PageIndex * sizeof(CddExtFlash_PageType));

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

  /* Write data */
  CddSpi_WriteMultipleBytes((const uint8_t*)PtrPageToWrite, (uint32_t)sizeof(CddExtFlash_PageType));

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();
}

/* Function to read data from a sector */
void CddExtFlash_DataProcess_ReadPage(const uint32_t PageIndex, CddExtFlash_PageType* PtrPageToRead)
{
  /* Chip Address */
  const uint32_t PageAddress = (PageIndex * sizeof(CddExtFlash_PageType));

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

  /* Read data */
  CddSpi_ReadMultipleBytes((uint8_t*)PtrPageToRead, (uint32_t)sizeof(CddExtFlash_PageType));

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_DataProcess_Ready();
}

/* Function to erase data from a sector */
void CddExtFlash_DataProcess_EraseSector(const uint32_t PageIndex)
{
  /* Chip Address */
  const uint32_t SectorAddress = (PageIndex * sizeof(CddExtFlash_PageType));

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

