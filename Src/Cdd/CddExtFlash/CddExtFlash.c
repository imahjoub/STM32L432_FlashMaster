#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>

void CddExtFlash_ProgramDataToFlash(FlashChip* Flash, uint8_t* Data, uint32_t DataSize)
{
  (void)Flash;
  (void)Data;
  (void)DataSize;
}

void CddExtFlash_CalculateCRC(FlashPage* Page)
{
  (void)Page;
}

bool CddExtFlash_CheckLastProgrammedPage(FlashChip* Flash, uint32_t* NextBlock, uint32_t* NextSector, uint32_t* NextPage)
{
  (void)Flash;
  (void)NextBlock;
  (void)NextSector;
  (void)NextPage;
  return true;
}

