#include <stdint.h>
#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

//#define OS_TASK_USE_LED
#define OS_TASK_USE_FLASH

static uint64_t my_timer;

#if defined(OS_TASK_USE_FLASH)
CddExtFlash_PageType AppPage;

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
  my_timer = TimerStart(1000U);

  #endif
}

void Task01_Func(void)
{
  #if defined(OS_TASK_USE_LED)

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

  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(2000U);

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
}

void Task03_Func(void)
{
}
