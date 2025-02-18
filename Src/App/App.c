#include <stdint.h>
#include <stdbool.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <OS/OS.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>

#include <Cdd/CddSerLCD/CddSerLCD_I2c.h>
#include <Cdd/CddI2c/CddI2c.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Util/UtilTimer.h>
#include <Util/Md5/Md5.h>

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

