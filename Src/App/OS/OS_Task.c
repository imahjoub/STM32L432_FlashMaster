#include <stdint.h>
#include <string.h>

#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddExtFlash/CddExtFlash.h>

/* Global variables */
static uint64_t my_timer = 0U;
#if 0
static CddExtFlash_PageType TxDummyPage;
static CddExtFlash_PageType RxDummyPage;
#endif

/***************************** Task1  *****************************/
void Task01_Init(void);
void Task01_Func(void);

void Task01_Init(void)
{
#if 1
  /* Initialize the ports. */
  /* Enable the clock for GPIOA */
  RCC_AHB1ENR |= (1 << 0);

  /* Configure GPIOA Pin 5 as output */
  GPIOA_MODER |= (1 << 10);

  my_timer = 1U;

  /* Toggle the LED pin */
  GPIOA_ODR |= (uint32_t) (1UL << 5U);
#endif
}

void Task01_Func(void)
{
#if 1
  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(500U);

    /* Toggle the LED pin */
    GPIOA_ODR ^= (uint32_t) (1UL << 5U);
  }
#endif
}

/***************************** Task2  *****************************/
void Task02_Init(void);
void Task02_Func(void);

void Task02_Init(void)
{
#if 0
  /* Spi initialization */
  CddSpi_Init();

  /* Chip Select (CS) initialization */
  CddSpi_CsInit();
#endif
}

void Task02_Func(void)
{
#if 0
  TxDummyPage.Data = 0xC001CAFEU;

  (void)CddExtFlash_Init();

  (void)CddExtFlash_EraseSector();

  memset((void*)&RxDummyPage.Data, 0xFFU, sizeof(CddExtFlash_PageType));

  (void)CddExtFlash_WritePage((const CddExtFlash_PageType*)&TxDummyPage.Data);

  (void)CddExtFlash_ReadPage((CddExtFlash_PageType*)&RxDummyPage);
#endif
}


/***************************** Task3  *****************************/
void Task03_Init(void);
void Task03_Func(void);

void Task03_Init(void) { }

void Task03_Func(void)
{
}
