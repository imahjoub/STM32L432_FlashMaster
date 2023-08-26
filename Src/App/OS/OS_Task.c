#include <stdint.h>

#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>
#include <Util/UtilTimer.h>

void Task01_Init(void);
void Task02_Init(void);
void Task03_Init(void);

void Task01_Func(void);
void Task02_Func(void);
void Task03_Func(void);

void Task01_Init(void) { }
void Task02_Init(void) { }
void Task03_Init(void) { }

void Task01_Func(void)
{
  static uint64_t my_timer = 1U;

  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(1000U);

    // Toggle the LED pin
    GPIOA_ODR ^= (uint32_t) (1UL << 5U);
  }
}

void Task02_Func(void) { }
void Task03_Func(void) { }
