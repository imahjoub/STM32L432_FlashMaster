#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>

static uint32_t CddExtFlash_ActivePageIndex = 0U;
static uint32_t CddExtFlash_WriteCounter    = 0U;


void CddExtFlash_Init(void)
{
  CddExtFlash_ActivePageIndex = 0U;
}

bool CddExtFlash_WritePage(const CddExtFlash_PageType* PtrPageToWrite)
{
   CddExtFlash_DataProcess_WritePage(CddExtFlash_ActivePageIndex, PtrPageToWrite);

  /* TBD return after a significant check */
  return true;
}

bool CddExtFlash_ReadPage(CddExtFlash_PageType* PtrPageToRead)
{
   CddExtFlash_DataProcess_ReadPage(CddExtFlash_ActivePageIndex, PtrPageToRead);

  /* TBD return after a significant check */
  return true;
}

bool CddExtFlash_EraseSector(void)
{
  CddExtFlash_DataProcess_EraseSector(CddExtFlash_ActivePageIndex);

  /* TBD return after a significant check */
  return true;
}

uint32_t CddExtFlash_GetActivePageIndex(void)
{
  return CddExtFlash_ActivePageIndex;
}

uint32_t CddExtFlash_GetActiveWriteCounter(void)
{
  return CddExtFlash_WriteCounter;
}

