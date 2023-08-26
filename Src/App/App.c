#include <stdbool.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddSpi/CddSpi.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Spi initialization
  SpiInit();

  // Chip Select (CS) initialization
  SPICsInit();

  uint8_t ReadChipIDCmd[1u] = {0x9FU};
  uint8_t ReadBuff[10U]     = {0U};

  while (1)
  {
    // Enable chip select
    SpiCsEnable();

    // Send the command to read the chip ID
    SpiSend(ReadChipIDCmd, 1U);

    SpiReceive(ReadBuff, 4U);

    // Disable chip select
    SpiCsDisable();
  }

  return 0;
}

