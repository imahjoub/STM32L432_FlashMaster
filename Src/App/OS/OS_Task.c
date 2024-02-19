#include <stdint.h>
#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

/* Global variables */
#if 0
static uint64_t my_timer = 0U;
#endif
#if 1
static CddExtFlash_PageType TxDummyPage;
static CddExtFlash_PageType RxDummyPage;
static uint8_t OneEraseCmd = 0x00U;
static uint8_t OneWriteCmd = 0x00U;
static int     PageIsok    = 0xFFU;

void OS_TaskDummy(void);

void OS_TaskDummy(void)
{
  (void) TxDummyPage;
  (void) RxDummyPage;
  (void) OneEraseCmd;
  (void) OneWriteCmd;
  (void) PageIsok;
}
#endif

/************************* TASK1 *********************************/
void Task01_Init(void);
void Task01_Func(void);

void Task01_Init(void)
{
#if 0
  // Initialize the ports.
  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  // Switch on the LED.
  GPIOA_ODR |= (uint32_t) (1UL << 5U);

  // Set the next timer timeout to be 1s later,
  // Toggling will be sequentially carried out in the task.
  my_timer = TimerStart(1000U);
#endif
}

void Task01_Func(void)
{
#if 0
  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(1000U);

    // Toggle the LED pin
    GPIOA_ODR ^= (uint32_t) (1UL << 5U);
  }
#endif
}


/************************* TASK2 *********************************/
void Task02_Init(void);
void Task02_Func(void);

void Task02_Init(void)
{
  /* Initialize Spi */
  CddSpi_Init();

  /* Initialize Spi CS */
  CddSpi_CsInit();

  TxDummyPage.Data = 0xDEADC0DEU;

  // Debug code: Let's write all new pages.
  for(uint8_t index = (uint8_t) 0U; index < (uint8_t) IS25LP128F_PAGES_NUM_USED; ++index)
  {
    const bool boResultOfReadIsOK = CddExtFlash_ReadPage((CddExtFlash_PageType*) &RxDummyPage);

    (void) CddExtFlash_WritePage((CddExtFlash_PageType*) &TxDummyPage);

    (void) boResultOfReadIsOK;

    ++TxDummyPage.Data;
  }

  //CddExtFlash_Init();
}

void Task02_Func(void)
{
#if 0

  (void)CddExtFlash_ReadPage((CddExtFlash_PageType*)&RxDummyPage);

  if(OneEraseCmd == 0)
  {
    (void)CddExtFlash_EraseSector();
    OneEraseCmd = 1U;
    memset((void*)&RxDummyPage.Data, 0xAAU, sizeof(CddExtFlash_PageType));
  }

  (void)CddExtFlash_ReadPage((CddExtFlash_PageType*)&RxDummyPage);

  if(OneWriteCmd == 0)
  {
    (void)CddExtFlash_WritePage((CddExtFlash_PageType*)&TxDummyPage.Data);
     OneWriteCmd = 1U;
  }

  PageIsok = CddExtFlash_ReadPage((CddExtFlash_PageType*)&RxDummyPage);

#endif
}


/************************* TASK3 *********************************/
void Task03_Init(void);
void Task03_Func(void);

void Task03_Init(void)
{
}

void Task03_Func(void)
{
}
