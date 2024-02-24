#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Util/Md5/Md5.h>

static uint32_t CddExtFlash_ActivePageIndex;
static uint32_t CddExtFlash_WriteCounter;

extern CddExtFlash_PageType AppPage;

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

  for(uint32_t Index = (uint32_t) 0U; Index < IS25LP128F_PAGES_NUM_USED ; ++Index)
  {
    CddExtFlash_DataProcess_ReadPage(Index, &PageToRead);

    CddExtFlash_HashContextType HashResultCalculated;

    // Calculate the new MD5.
    const size_t length_to_read = (size_t) &PageToRead.HashContext.HashData[0U] - (size_t) &PageToRead.Data;

    Md5_Calculate((uint8_t*) &PageToRead.Data, length_to_read, &HashResultCalculated.HashData[0U]);

    const int ResultOfMemCompare =
      memcmp((const void*) &PageToRead.HashContext.HashData[0U],
             (const void*) &HashResultCalculated.HashData[0U],
             sizeof(CddExtFlash_HashContextType));

    const bool PageIsValid = (ResultOfMemCompare == 0);

    if(PageIsValid && (PageToRead.WriteCounter > ulMaxWriteCounter))
    {
      // Initialize the "Application"
      AppPage.Data = PageToRead.Data;

      ulMaxWriteCounter = PageToRead.WriteCounter;

      CddExtFlash_WriteCounter = ulMaxWriteCounter;

      CddExtFlash_ActivePageIndex = (uint8_t) Index;
    }
  }

  ++CddExtFlash_ActivePageIndex;

  if(CddExtFlash_ActivePageIndex == (uint8_t) IS25LP128F_PAGES_NUM_USED)
  {
    CddExtFlash_ActivePageIndex = (uint8_t) 0U;
  }
}

bool CddExtFlash_WritePage(const CddExtFlash_PageType* ptrPageToWrite)
{
  const size_t length_to_write = (size_t) &ptrPageToWrite->HashContext.HashData[0U] - (size_t) &ptrPageToWrite->Data;

  CddExtFlash_PageType PageToWrite = *ptrPageToWrite;

  // Increment the running index.
  ++CddExtFlash_WriteCounter;
  PageToWrite.WriteCounter = CddExtFlash_WriteCounter;

  CddExtFlash_HashContextType result_of_md5;

  // Calculate the MD5.
  Md5_Calculate((uint8_t*) &PageToWrite.Data, length_to_write, &result_of_md5.HashData[0U]);

  // Copy the calculated MD5 into the new flash memory buffer.
  memcpy((void*) &PageToWrite.HashContext.HashData[0U], (const void*) &result_of_md5.HashData[0U], sizeof(CddExtFlash_HashContextType));

  // Erase the active page.
  CddExtFlash_DataProcess_EraseSector(CddExtFlash_ActivePageIndex);

  // Write the new flash memory buffer.
  CddExtFlash_DataProcess_WritePage(CddExtFlash_ActivePageIndex, (const CddExtFlash_PageType*) &PageToWrite);

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

  CddExtFlash_DataProcess_ReadPage(CddExtFlash_ActivePageIndex, ptrPageToRead);

  CddExtFlash_HashContextType HashResultCalculated;

  // Calculate the new MD5.
  const size_t length_to_read = (size_t) &ptrPageToRead->HashContext.HashData[0U] - (size_t) &ptrPageToRead->Data;

  Md5_Calculate((uint8_t*)&ptrPageToRead->Data, length_to_read, &HashResultCalculated.HashData[0U]);

  CddExtFlash_PageIsValid = (ptrPageToRead->HashContext.HashData == HashResultCalculated.HashData);

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
