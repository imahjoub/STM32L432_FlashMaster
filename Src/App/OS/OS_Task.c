#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddSerLCD/CddSerLCD_I2c.h>
#include <Cdd/CddI2c/CddI2c.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>
#include <Util/Md5/Md5.h>

//#define OS_TASK_USE_LED
#define OS_TASK_USE_FLASH
#define OS_TASK_USE_SERLCD_I2C

static uint64_t TaskTimer02;
static uint8_t ReadBuffer [260U]    = { 0U };
static uint8_t WriteBuffer[256U]    = { 0U };
static uint8_t HashWriteBuffer[256] = { 0U };
static uint8_t HashReadBuffer [256] = { 0U };


typedef enum { JobIdle, JobRead, JobWrite, JobErase, JobCheck, JobSucceeded, JobFailed }  ExtFlash_JobType;
ExtFlash_JobType ExtFlashCurrentJob = JobIdle;

bool JobEraseDone = false;
bool JobWriteDone = false;
bool HashIsOk     = false;

#if defined(OS_TASK_USE_FLASH)


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
uint8_t ostask_buffer_id[3U] = {0x00U};

void Task02_Init(void);
void Task02_Func(void);

void Task02_Init(void)
{
  #if defined(OS_TASK_USE_FLASH)

  /* Initialize Spi */
  CddSpi_Init();
  Flash_Init();

  for (uint16_t idx = 0U; idx < 256U; idx++)
  {
    WriteBuffer[idx] = 0xAAU;
  }

  #endif
}

void Task02_Func(void)
{
#if defined(OS_TASK_USE_FLASH)

  if(TimerTimeout(TaskTimer02))
  {
    TaskTimer02 = TimerStart(5000U);

    switch (ExtFlashCurrentJob)
    {
    case JobIdle:
      ExtFlashCurrentJob = JobErase;
      break;

    case JobErase:
     if(JobEraseDone == false)
     {
       Flash_SErase4k(0x00UL);
       ExtFlashCurrentJob = JobWrite;
       JobEraseDone = true;
     }
     break;

    case JobWrite:
      if(JobWriteDone == false)
      {
        Flash_SimpleWriteAPage(0x00UL, WriteBuffer, 256U);
        ExtFlashCurrentJob = JobRead;
        JobWriteDone = true;
      }
      break;

    case JobRead:
      Flash_Read(0x00UL, ReadBuffer, 259U);
      ExtFlashCurrentJob = JobCheck;
      break;

    case JobCheck:
      Md5_Calculate((uint8_t*)&WriteBuffer, 256U, (uint8_t*)&HashWriteBuffer);
      Md5_Calculate((uint8_t*)&ReadBuffer, 256U,  (uint8_t*)&HashReadBuffer);
      HashIsOk = Md5_Check((uint8_t*)&HashWriteBuffer, (uint8_t*)&HashReadBuffer);
      ExtFlashCurrentJob = HashIsOk ? JobSucceeded : JobFailed;
      break;

    case JobSucceeded:
      /* Do nothing */
      break;

    case JobFailed:
      /* Do nothing */
      break;

    default:
      /* Do nothing */
      break;
    }
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
  CddSerLcd_Init();
#endif
}

void Task03_Func(void)
{
#if defined(OS_TASK_USE_SERLCD_I2C)

  switch (ExtFlashCurrentJob)
  {
  case JobIdle:
    (void)CddSerLcd_WriteString("FlashMaster JobIdle...");
    (void)CddSerLcd_Clear();
    break;

  case JobErase:
    (void)CddSerLcd_WriteString("FlashMaster JobErase...");
    (void)CddSerLcd_Clear();
    break;

  case JobWrite:
    (void)CddSerLcd_WriteString("FlashMaster JobWrite...");
    (void)CddSerLcd_Clear();
    break;

  case JobRead:
    (void)CddSerLcd_WriteString("FlashMaster JobRead...");
    (void)CddSerLcd_Clear();
    break;

  case JobCheck:
    (void)CddSerLcd_WriteString("FlashMaster JobCheck...");
    (void)CddSerLcd_Clear();
  break;

  case JobSucceeded:
    (void)CddSerLcd_WriteString("FlashMaster JobSucceeded...");
    (void)CddSerLcd_Clear();
    break;

  case JobFailed:
    (void)CddSerLcd_WriteString("FlashMaster JobFailed...");
    (void)CddSerLcd_Clear();
    break;

  default:
    break;
  }

#endif
}



