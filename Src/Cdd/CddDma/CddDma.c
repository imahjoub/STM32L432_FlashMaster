
#include <Cdd/CddDma/CddDma.h>
#include <Mcal/Reg.h>

void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);

void Dma2Stream3SpiTxInit(void)
{
  /* Enable the peripheral clock for DMA2 */
 RCC_AHB1ENR |= (1UL<<22U);


}

void Dma2Stream2SpiRxInit(void)
{
  /* Enable the peripheral clock for DMA2 */
 RCC_AHB1ENR |= (1UL<<22U);

}

void Dma2Stream3SpiSend(void)
{
}

void Dma2Stream2SpiReceive(void)
{
}

void DMA2_Stream2_IRQHandler(void)
{
}

void DMA2_Stream3_IRQHandler(void)
{
}
