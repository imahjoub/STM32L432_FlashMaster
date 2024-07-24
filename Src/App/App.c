#include <stdint.h>
#include <string.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <OS/OS.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  /* Configure the System clock and flash */
  SystemInit();
  SetSysClock();

  /* Configure systick timer.*/
  SysTick_Init();

  (void) AppShape_CheckCircle();

  /* Initialize the OS. This calls the task init-functions one time only */
  OS_Init();

  /* Start the cooperative multitasking scheduler */
  OS_Start();

  return 0;
}
