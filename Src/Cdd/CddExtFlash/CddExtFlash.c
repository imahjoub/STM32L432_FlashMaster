#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSpi/CddSpi.h>

/* Define IS25LP128F commands */
#define EXTFLASH_CMD_WRITE_ENABLE   0x06U
#define EXTFLASH_CMD_PAGE_PROGRAM   0x02U
#define EXTFLASH_CMD_PAGE_READ      0x03U
#define EXTFLASH_CMD_READ_STATUS    0x05U

/* Function to enable writing */
void CddExtFlash_WriteEnable(void)
{
  /* Chip select enable */
  CddSpiCsEnable();

  /* Send Write Enable command */
  CddSpiTransfer(EXTFLASH_CMD_WRITE_ENABLE);

  /* Chip select disable */
  CddSpiCsDisable();
}

/* Function to wait until the chip is not busy */
void CddExtFlash_Ready(void)
{
  /* Chip select enable */
  CddSpiCsEnable();

  /* TBD Add timeout error check */
  /* Poll Status Register until busy bit is cleared */
  while (CddSpiWriteRead(EXTFLASH_CMD_READ_STATUS) & (0x01U));

  /* Chip select disable */
  CddSpiCsDisable();
}

/* Function to wait until the chip write enabled */
void CddExtFlash_WriteReady(void)
{
  /* Chip select enable */
  CddSpiCsEnable();

  /* TBD Add timeout error check */
  /* Poll Status Register until write enable latch is set */
  while (!(CddSpiWriteRead(EXTFLASH_CMD_READ_STATUS) & (1UL << 1U)));

  /* Chip select disable */
  CddSpiCsDisable();
}

/* Function to write data to a sector */
void CddExtFlash_WriteSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen)
{
  /* Enable writing */
  CddExtFlash_WriteEnable();

  /* Send Page Program command */
  CddSpiTransfer(EXTFLASH_CMD_PAGE_PROGRAM);

  /* Address byte 2 */
  CddSpiTransfer((SectorAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpiTransfer((SectorAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpiTransfer((SectorAddress >>  0U) & 0xFFU);

  /* Write data     */
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    CddSpiTransfer(DataPtr[i]);
  }

  /* Wait for completion */
  CddExtFlash_Ready();
}

/* Function to write data to a sector */
void CddExtFlash_ReadSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen)
{
  /* Send Page Program command */
  CddSpiTransfer(EXTFLASH_CMD_PAGE_READ);

  /* Address byte 2 */
  CddSpiTransfer((SectorAddress >> 16U) & 0xFFU);

  /* Address byte 1 */
  CddSpiTransfer((SectorAddress >>  8U) & 0xFFU);

  /* Address byte 0 */
  CddSpiTransfer((SectorAddress >>  0U) & 0xFFU);

  /* Write data     */
  for (uint32_t i = 0U; i < DataLen; ++i)
  {
    CddSpiReceive(&DataPtr[i], DataLen);
  }

  /* Wait for completion */
  CddExtFlash_Ready();
}