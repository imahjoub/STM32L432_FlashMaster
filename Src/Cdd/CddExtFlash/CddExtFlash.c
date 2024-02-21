#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Util/Md5/Md5.h>

static uint32_t CddExtFlash_ActivePageIndex = 0U;
static uint32_t CddExtFlash_WriteCounter    = 0U;

uint32_t CddExtFlash_GetActivePageIndex(void)
{
  return CddExtFlash_ActivePageIndex;
}

uint32_t CddExtFlash_GetActiveWriteCounter(void)
{
  return CddExtFlash_WriteCounter;
}

void CddExtFlash_Init(void)
{
  /* Initialization */
  CddExtFlash_PageType PageToRead;

  uint32_t ulMaxWriteCounter = (uint32_t) UINT32_C(0);

  for(uint32_t i = (uint32_t) 0U; i < IS25LP128F_PAGES_NUM_USED ; ++i)
  {
    const uint32_t StartAddressOfNextPage = (uint32_t) (i * IS25LP128F_PAGES_GRANULAR_BORDER);

    CddExtFlash_DataProcess_ReadPage(StartAddressOfNextPage, &PageToRead);

    if(PageToRead.WriteCounter > ulMaxWriteCounter)
    {
      ulMaxWriteCounter = PageToRead.WriteCounter;

      CddExtFlash_WriteCounter = ulMaxWriteCounter;

      CddExtFlash_ActivePageIndex = (uint8_t) i;
    }

    CddExtFlash_ActivePageIndex = (uint8_t) 0U;
  }

}

bool CddExtFlash_WritePage(const CddExtFlash_PageType* ptrPageToWrite)
{
  const size_t length_to_write = (size_t) &ptrPageToWrite->HashContext.HashData[0U] - (size_t) &ptrPageToWrite->Data;

  CddExtFlash_PageType LocalPageToWrite = *ptrPageToWrite;

  // Increment the running index.
  ++LocalPageToWrite.WriteCounter;

  CddExtFlash_HashContextType result_of_md5;

  // Calculate the MD5.
  Md5_Calculate((uint8_t*) &LocalPageToWrite.Data, length_to_write, &result_of_md5.HashData[0U]);

  // Copy the calculated MD5 into the new flash memory buffer.
  memcpy((void*) &LocalPageToWrite.HashContext.HashData[0U], (const void*) &result_of_md5.HashData[0U], sizeof(CddExtFlash_HashContextType));

  // Erase the active page.
  CddExtFlash_DataProcess_EraseSector(CddExtFlash_ActivePageIndex);

  // Write the new flash memory buffer.
  CddExtFlash_DataProcess_WritePage(CddExtFlash_ActivePageIndex, (const CddExtFlash_PageType*) &LocalPageToWrite);

  ++CddExtFlash_ActivePageIndex;

  if(CddExtFlash_ActivePageIndex == (uint8_t) IS25LP128F_PAGES_NUM_USED)
  {
    CddExtFlash_ActivePageIndex = (uint8_t) 0U;
  }

  return true;
}

bool CddExtFlash_ReadPage(CddExtFlash_PageType* ptrPageToRead)
{
  bool CddExtFlash_PageIsValid = true;

  const size_t length_to_read = (size_t) &ptrPageToRead->HashContext.HashData[0U] - (size_t) &ptrPageToRead->Data;

  CddExtFlash_DataProcess_ReadPage(CddExtFlash_ActivePageIndex, ptrPageToRead);

  uint8_t result_of_md5[16U];

  // Calculate the new MD5.
  Md5_Calculate((uint8_t*)&ptrPageToRead->Data, length_to_read, result_of_md5);

  CddExtFlash_PageIsValid = Md5_Check(result_of_md5, &ptrPageToRead->HashContext.HashData[0U]);

  return CddExtFlash_PageIsValid;
}

bool CddExtFlash_EraseSector(void)
{
  #if 0
  CddExtFlash_DataProcess_EraseSector(CddExtFlash_ActivePageIndex);

  ++CddExtFlash_ActivePageIndex;

  if(CddExtFlash_ActivePageIndex == (uint8_t) IS25LP128F_PAGES_NUM_USED)
  {
    CddExtFlash_ActivePageIndex = (uint8_t) 0U;
  }
  #endif

  return true;
}

bool CddExtFlash_EraseChip(void)
{
  CddExtFlash_DataProcess_EraseChip();

  return true;
}
