#include <stdint.h>
#include <string.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddI2c/CddI2c.h>
#include <Cdd/CddSerLCD/CddSerLCD_I2c.h>
#include <Cdd/CddSpi/CddSpi.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  /* Configure the System clock and flash */
  SystemInit();
  SetSysClock();

  /* Configure systick timer.*/
  SysTick_Init();

  (void) AppShape_CheckCircle();

  /* Initialize I2C1 */
  CddI2c_Init();
  CddSerLCD_I2c_Init();

  for(;;)
  {
    CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
    /* Delay to ensure the clear command is processed */
    CddSerLcd_I2c_msDelays(5U);
    CddSerLCD_I2c_PrintString("Hello");
    CddSerLcd_I2c_msDelays(2000U);

    CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
    /* Delay to ensure the clear command is processed */
    CddSerLcd_I2c_msDelays(5U);
    CddSerLCD_I2c_PrintString("World");
    CddSerLcd_I2c_msDelays(2000U);

  }

  return 0;
}
