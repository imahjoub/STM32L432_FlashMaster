#include <stdint.h>
#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSerLCD/CddSerLCD_I2c.h>
#include <Cdd/CddI2c/CddI2c.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

//#define OS_TASK_USE_LED
//#define OS_TASK_USE_FLASH
#define OS_TASK_USE_SERLCD_I2C

CddExtFlash_PageType AppPage;

//static uint64_t TaskTimer02;

#if defined(OS_TASK_USE_FLASH)

static uint64_t TaskTimer02;

void OS_TaskDummy(void);

void OS_TaskDummy(void)
{
}
#endif

/************************* TASK1 *********************************/
void Task01_Init(void);
void Task01_Func(void);

void Task01_Init(void)
{
  #if defined(OS_TASK_USE_LED)

  /*. Enable GPIO Clock for GPIOB */
  RCC_AHB2ENR |= (1U << 1U);

  /*. Configure PB3 as output */
  GPIOB_MODER |= (1U << 6U);
  GPIOB_MODER &= ~(1U << 7U);

  /* Toggle the LED pin */
  GPIOB_ODR |= (uint32_t) (1UL << 3U);

  /* Set the next timer timeout to be 1s later, */
  /* Toggling will be sequentially carried out in the task. */
  TaskTimer02 = TimerStart(1000U);

  #endif
}

void Task01_Func(void)
{
  #if defined(OS_TASK_USE_LED)

  if(TimerTimeout(TaskTimer02))
  {
    TaskTimer02 = TimerStart(1000U);

    /* Toggle the LED pin */
    GPIOB_ODR ^= (uint32_t) (1UL << 3U);
  }

  #endif
}


/************************* TASK2 *********************************/

void Task02_Init(void);
void Task02_Func(void);

void Task02_Init(void)
{
  #if defined(OS_TASK_USE_FLASH)

  /* Initialize Spi */
  CddSpi_Init();

  /* Initialize Spi CS */
  CddSpi_CsInit();

  CddExtFlash_Init();

  #endif
}

void Task02_Func(void)
{
  #if defined(OS_TASK_USE_FLASH)

  if(TimerTimeout(TaskTimer02))
  {
    TaskTimer02 = TimerStart(2000U);

    // Write the new data.
    CddExtFlash_WritePage(&AppPage);
  }

  #endif
}


/************************* TASK3 *********************************/
void Task03_Init(void);
void Task03_Func(void);

void Task03_Init(void)
{
  #if defined(OS_TASK_USE_SERLCD_I2C)

  /* Initialize I2C1 */
  CddI2c_Init();
  CddSerLCD_I2c_Init();

  #endif
}

void Task03_Func(void)
{
  #if defined(OS_TASK_USE_SERLCD_I2C)

  //char HelloString[] = { "hello" };
  //char WorldString[] = { "World" };
  //
  //CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
  ///* Delay to ensure the clear command is processed */
  //CddSerLcd_I2c_msDelays(5U);
  //CddSerLCD_I2c_PrintString(HelloString, sizeof(HelloString)/sizeof(HelloString[0]));
  //CddSerLcd_I2c_msDelays(2000U);
  //
  //CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
  ///* Delay to ensure the clear command is processed */
  //CddSerLcd_I2c_msDelays(5U);
  //CddSerLCD_I2c_PrintString(WorldString, sizeof(WorldString) / sizeof(WorldString[0]));
  //CddSerLcd_I2c_msDelays(2000U);

#endif
}



