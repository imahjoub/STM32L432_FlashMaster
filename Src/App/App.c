#include <stdbool.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddDma/CddDma.h>

extern bool AppShape_CheckCircle(void);
extern volatile bool SpiTransferComplete;
extern volatile bool SpiReceiveComplete;

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
  uint8_t ReadBuff[4U]     = {0xFFU, 0xFFU, 0xFFU, 0xFFU};


   Dma2Stream3SpiTxInit();
   Dma2Stream2SpiRxInit();

  while (1)
  {
    // Enable chip select
    CddSpiCsEnable();

    // Send the command to read the chip ID
    //CddSpiSend(ReadChipIDCmd, 1U);

    // Read chip ID
    //CddSpiReceive(ReadBuff, 4U);


    Dma2Stream3SpiSend(ReadChipIDCmd, 1U);
    while(!(SpiTransferComplete))
    {
      // Do nothing
    }
    SpiTransferComplete = false;

    Dma2Stream2SpiReceive(ReadBuff, 4U);
    while(!(SpiReceiveComplete))
    {
      // Do nothing
    }
    SpiReceiveComplete = false;

    // Disable chip select
    CddSpiCsDisable();
  }

  return 0;
}

