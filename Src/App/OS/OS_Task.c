#include <stdint.h>

#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddExtFlash/CddExtFlash.h>

/* Global variables */
static uint64_t my_timer = 0U;

/***************************** Task1  *****************************/
void Task01_Init(void);
void Task01_Func(void);

void Task01_Init(void)
{
  my_timer = 1U;

  // Toggle the LED pin
  GPIOA_ODR |= (uint32_t) (1UL << 5U);
}

void Task01_Func(void)
{

  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(1000U);

    // Toggle the LED pin
    GPIOA_ODR ^= (uint32_t) (1UL << 5U);
  }
}

/***************************** Task2  *****************************/
void Task02_Init(void);
void Task02_Func(void);

void Task02_Init(void) { }

void Task02_Func(void)
{
#if 0
  /* Spi initialization */
  CddSpi_Init();

  /* Chip Select (CS) initialization */
  CddSpi_CsInit();

  /* Test variables */
  volatile uint8_t one_write_cmd = 0U;
  volatile uint8_t one_erase_cmd = 0U;

  uint8_t WTx[16U] =
  {
    0x1AU, 0x1BU, 0x1CU, 0x1DU, 0x2AU, 0x2BU, 0x2CU, 0x2DU,
    0x3AU, 0x3BU, 0x3CU, 0x3DU, 0x4AU, 0x4BU, 0x4CU, 0x4DU
  };

  uint8_t _Rx[32U] = {0x00U};

  /* Erase */
  if(one_erase_cmd < 1U)
  {
    CddExtFlash_EraseSector(UINT32_C(0x000000));
    ++one_erase_cmd;
  }

  /*Read after erase */
  CddExtFlash_Read(UINT32_C(0x000000), _Rx, 16U);

  /* Write */
  if(one_write_cmd < 1U)
  {
    CddExtFlash_WritePage(UINT32_C(0x000000), WTx, 16U);
    ++one_write_cmd;
  }

  /*Read after write */
  CddExtFlash_Read(UINT32_C(0x000000), _Rx, 30U);
#endif
}


/***************************** Task3  *****************************/
void Task03_Init(void);
void Task03_Func(void);

void Task03_Init(void) { }

void Task03_Func(void)
{
}
