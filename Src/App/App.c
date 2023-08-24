#include <Mcal/Mcu.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>

extern bool AppShape_CheckCircle(void);

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

int main(void)
{
  // Initialize the ports.

  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer.
  SysTick_Init();

  (void) AppShape_CheckCircle();

  OS_Start();

  return 0;
}
