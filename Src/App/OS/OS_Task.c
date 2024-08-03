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
//#define OS_TASK_USE_SERLCD_I2C

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

  CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
  /* Delay to ensure the clear command is processed */
  CddSerLcd_I2c_msDelays(5U);
  CddSerLCD_I2c_PrintString("Hello");
  CddSerLcd_I2c_msDelays(2000U);

  CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
  /* Delay to ensure the clear command is processed */
  CddSerLcd_I2c_msDelays(5U);
  CddSerLCD_I2c_PrintString("World");
  CddSerLcd_I2c_msDelays(2000U);

  #endif
}



