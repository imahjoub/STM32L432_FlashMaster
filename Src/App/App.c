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

uint8_t Tx[1U] = {0x9FU};
uint8_t Rx[4U] = {0xFFU, 0xFFU, 0xFFU, 0xFFU};


int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Spi initialization
  CddSpiInit();

  // Chip Select (CS) initialization
  CddSpiCsInit();

   Dma2Stream3SpiTxInit();
   Dma2Stream2SpiRxInit();

  for(;;)
  {
    // Enable chip select
    CddSpiCsEnable();

    Dma2Stream3SpiSend((uint32_t)Tx, 1U);
    while(!(SpiTransferComplete)) { /* Do nothing */ }
    SpiTransferComplete = false;

    Dma2Stream2SpiReceive((uint32_t)Rx, 1U);
    while(!(SpiReceiveComplete)) { /* Do nothing */ }
    SpiReceiveComplete = false;

    // Disable chip select
    CddSpiCsDisable();
  }

  return 0;
}

