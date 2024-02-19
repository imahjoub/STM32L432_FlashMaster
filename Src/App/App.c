#include <stdint.h>
#include <string.h>

#include <Cdd/CddDma/CddDma.h>
#include <Cdd/CddExtFlash/CddExtFlash.h>
#include <Cdd/CddExtFlash/CddExtFlash_DataProcess.h>
#include <Cdd/CddSpi/CddSpi.h>
#include <Cdd/CddAdxl345/CddAdxl345.h>

#include <Mcal/Mcu.h>
#include <Mcal/SysTick.h>
#include <Mcal/Reg.h>
#include <OS/OS.h>
#include <Util/UtilTimer.h>

extern bool AppShape_CheckCircle(void);

int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer.
  SysTick_Init();

  (void) AppShape_CheckCircle();

  // Initialize the OS. This calls the task init-functions one time only.
  OS_Init();

  // Start the cooperative multitasking scheduler.
  OS_Start();


#if 0
  const uint8_t TxBuf[1] = {0x9fU};
        uint8_t RxBuf[3] = {0U};


  /* Initialize Spi */
  CddSpi_Init();

  /* Initialize Spi CS */
  CddSpi_CsInit();

  CddSpi_CsEnable();
  CddSpi_WriteMultipleBytes(TxBuf, 1U);
  CddSpi_ReadMultipleBytes(RxBuf, 3U);
  CddSpi_CsDisable();
#endif
  return 0;
}


























#if 0

extern volatile bool SpiTransferComplete;
extern volatile bool SpiReceiveComplete ;

const uint8_t TxBuf[1] = {0x9fU};
      uint8_t RxBuf[3] = {0xAAU};


  /* Initialize Spi */
  //CddSpi_Init();

  /* Initialize Spi CS */
  //CddSpi_CsInit();

  //CddSpi_CsEnable();

  //Dma2Stream3SpiTxInit();
  //Dma2Stream2SpiRxInit();


  //Dma2Stream3SpiSend((uintptr_t) &TxBuf[0U], 1U);
  //while(!SpiTransferComplete) { };

  //while(!SpiReceiveComplete) { };
  //Dma2Stream2SpiReceive((uintptr_t) &RxBuf[0U], 1U);

  //CddSpi_CsDisable();

  /* Debug code */
  //CddSpi_CsEnable();
  //CddSpi_WriteMultipleBytes(TxBuf, 1U);
  //CddSpi_ReadMultipleBytes(RxBuf, 3U);
  //CddSpi_CsDisable();
#endif

