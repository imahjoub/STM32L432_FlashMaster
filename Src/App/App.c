#include <Mcal/Mcu.h>
#include <Mcal/Systick.h>
#include <OS/OS.h>

int main(void)
{
  /* Configure the System clock and flash */
  SystemInit();
  SetSysClock();

  /* Configure systick timer.*/
  SysTick_Init();

  /* Initialize the OS. This calls the task init-functions one time only */
  OS_Init();

  /* Start the cooperative multitasking scheduler */
  OS_Start();
}

