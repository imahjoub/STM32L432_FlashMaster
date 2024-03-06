#include <stdint.h>
#include <string.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddSerLcd/CddSerLcd.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer.
  SysTick_Init();

  (void) AppShape_CheckCircle();

  CddSpi_Init();
  CddSpi_CsInit();

  CddSerLCD_Init();

  // Initialize the OS. This calls the task init-functions one time only.
  OS_Init();

  // Start the cooperative multitasking scheduler.
  OS_Start();

  return 0;
}

