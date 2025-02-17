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

int main(void)
{
  /* Configure the System clock and flash */
  SystemInit();
  SetSysClock();

  /* Configure systick timer.*/
  SysTick_Init();

  /* Initialize the OS. This calls the task init-functions one time only */
  //OS_Init();

  /* Start the cooperative multitasking scheduler */
  //OS_Start();


  /* ---------------- FLASH ----------------*/
#if 1
  CddSpi_Init();
  Flash_Init();

  uint8_t ReadBuffer [260U] = { 0U };
  uint8_t WriteBuffer[256U] = { 0U };

  for(uint16_t idx = 0U; idx < 256U; idx++)
  {
    WriteBuffer[idx] = 0xAAU;
  }

  Flash_Read(0x00UL, ReadBuffer, 256U);

  uint8_t cnt = 1U;

  if(cnt == 1U)
  {
    Flash_SErase4k(0x00UL);

    Flash_Read(0x00UL, ReadBuffer, 256U);

    Flash_SimpleWriteAPage(0x00UL, WriteBuffer, 256U);

    cnt = 5U;
  }

  Flash_Read(0x00UL, ReadBuffer, 259U);
#endif
  /* ---------------- SerLCD ----------------*/

  CddI2c_Init();
  CddSerLcd_Init();

  (void)CddSerLcd_WriteString("Hello32");
  (void)CddSerLcd_Clear();

  (void)CddSerLcd_WriteString("Worlddddddddddddddddddddddd!");
  (void)CddSerLcd_Clear();

}

