#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Cdd/CddSpi/CddSpi.h>

/* Function to enable writing */
void CddExtFlash_GetChipID(uint8_t* RxPtr)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send RDID command */
  CddSpi_Transfer(IS25LP128F_CMD_RDJDID);

  /* Get the RDID */
  CddSpi_Receive(RxPtr, 3U);

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to enable writing */
void CddExtFlash_WriteEnable(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send Write Enable command */
  CddSpi_Transfer(IS25LP128F_CMD_WRITE_ENABLE);

  /* Chip select disable */
  CddSpi_CsDisable();
}

/* Function to wait until the chip is not busy */
void CddExtFlash_Ready(void)
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
void CddExtFlash_WriteReady(void)
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
void CddExtFlash_WritePage(uint32_t PageAddress, uint8_t* TxPtr, uint32_t DataLen)
{
  /* Enable writing */
  CddExtFlash_WriteEnable();

  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send Page Program command */
  CddSpi_Transfer(IS25LP128F_CMD_PAGE_PROGRAM);

  /* Address byte 2 */
  CddSpi_Transfer((PageAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_Transfer((PageAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_Transfer((PageAddress >>  0U) & 0xFFU);

  /* Write data     */
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    CddSpi_Transfer(TxPtr[i]);
  }

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_Ready();
}

/* Function to read data from a sector */
void CddExtFlash_Read(uint32_t Address, uint8_t* RxPtr, uint32_t DataLen)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send read command */
  CddSpi_Transfer(IS25LP128F_CMD_NORMAL_READ);

  /* Address byte 2 */
  CddSpi_Transfer((Address >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_Transfer((Address >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_Transfer((Address >>  0U) & 0xFFU);

  /* Write data */
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    RxPtr[i] = CddSpi_Transfer(0xFFU);
  }

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_Ready();
}

/* Function to erase data from a sector */
void CddExtFlash_EraseSector(uint32_t SectorAddress)
{
  /* Enable writing */
  CddExtFlash_WriteEnable();

  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send erase sector command */
  CddSpi_Transfer(IS25LP128F_CMD_SEC_ERASE);

  /* Address byte 2 */
  CddSpi_Transfer((SectorAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpi_Transfer((SectorAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpi_Transfer((SectorAddress >>  0U) & 0xFFU);

  /* Chip select disable */
  CddSpi_CsDisable();

  /* Wait for completion */
  CddExtFlash_Ready();
}

