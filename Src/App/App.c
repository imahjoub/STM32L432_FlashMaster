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
  CddSpiInit();

  // Chip Select (CS) initialization
  CddSpiCsInit();

  uint8_t ReadChipIDCmd[1u] = {0x9FU};
  uint8_t ReadBuff[10U]     = {0U};

  while (1)
  {
    // Enable chip select
    CddSpiCsEnable();

    // Send the command to read the chip ID
    CddSpiSend(ReadChipIDCmd, 1U);

    // Read chip ID
    CddSpiReceive(ReadBuff, 4U);

    // Disable chip select
    CddSpiCsDisable();
  }

  return 0;
}

