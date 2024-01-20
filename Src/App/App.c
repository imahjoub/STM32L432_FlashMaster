#include <stdbool.h>
#include <string.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  /* Configure the System clock and flash */
  SystemInit();
  SetSysClock();

  /* Configure systick timer */
  SysTick_Init();

  (void) AppShape_CheckCircle();

  /* Initialize the OS */
  OS_Init();

  /* Start running the OS */
  OS_Start();

  return 0;
}
