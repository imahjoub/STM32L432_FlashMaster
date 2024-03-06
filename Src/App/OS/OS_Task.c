#include <stdint.h>
#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSerLCD/CddSerLCD.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

//#define OS_TASK_USE_LED
//#define OS_TASK_USE_FLASH
#define OS_TASK_USE_SERLCD

CddExtFlash_PageType AppPage;

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

  // Initialize the ports.
  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  // Switch on the LED.
  GPIOA_ODR |= (uint32_t) (1UL << 5U);

  // Set the next timer timeout to be 1s later,
  // Toggling will be sequentially carried out in the task.
  TaskTimer02 = TimerStart(1000U);

  #endif
}

void Task01_Func(void)
{
  #if defined(OS_TASK_USE_LED)

  if(TimerTimeout(TaskTimer02))
  {
    TaskTimer02 = TimerStart(1000U);

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
static uint64_t TaskTimer03;
static const char HelloWorldString01[] = "STM32F4_FlashMaster!";
static const char HelloWorldString02[] = "SerLcd";
static const char HelloWorldString03[] = "IS25LP128";

void Task03_Init(void);
void Task03_Func(void);

void Task03_Init(void)
{
}

void Task03_Func(void)
{
  static uint8_t LineIndex;
  static uint8_t StringIndex;

  if(TimerTimeout(TaskTimer03))
  {
    TaskTimer03 = TimerStart(1000U);

    switch(StringIndex)
    {
      case 0U:
        CddSerLCD_WriteLine(&HelloWorldString01[0], (size_t) (sizeof(HelloWorldString01) - 1U), LineIndex % 4U);
        break;
      case 1U:
        CddSerLCD_WriteLine(&HelloWorldString02[0], (size_t) (sizeof(HelloWorldString02) - 1U), LineIndex % 4U);
        break;
      case 2U:
      default:
        CddSerLCD_WriteLine(&HelloWorldString03[0], (size_t) (sizeof(HelloWorldString03) - 1U), LineIndex % 4U);
        break;
    }

    ++LineIndex;

    ++StringIndex;

    if(StringIndex == 3U)
    {
      StringIndex = 0U;
    }
  }
}
