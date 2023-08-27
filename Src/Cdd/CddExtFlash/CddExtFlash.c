#include <Cdd/CddExtFlash/CddExtFlash.h>

/* Define IS25LP128F commands */
#define CMD_WRITE_ENABLE  0x06U
#define CMD_PAGE_PROGRAM  0x02U

/* Function to enable writing */
void CddExtFlashWriteEnable(void)
{
  /* Send Write Enable command */
  CddSpiTransfer(CMD_WRITE_ENABLE);
}

/* Function to wait until the chip is not busy */
void CddExtFlashWaitForRead(void)
{
  /* Poll Status Register until busy bit is cleared */
  while (CddSpiTransfer(0x05U) & 0x01U);
}

/* Function to write data to a sector */
void CddExtFlashWriteSector(uint32_t SectorAddress, uint8_t *DataPtr, uint32_t DataLen)
{
  /* Enable writing */
  CddExtFlashWriteEnable();

  /* Send Page Program command */
  CddSpiTransfer(CMD_PAGE_PROGRAM);

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
  CddExtFlashWaitForRead();
}
