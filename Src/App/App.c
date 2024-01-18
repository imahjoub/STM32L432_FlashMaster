#include <stdbool.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

extern bool AppShape_CheckCircle(void);

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

  /* Initialize the OS */
  OS_Init();

  /* Start running the OS */
  OS_Start();

  return 0;
}
