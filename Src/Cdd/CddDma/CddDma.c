
#include <Cdd/CddDma/CddDma.h>
#include <Mcal/Reg.h>

void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);

void Dma2Stream3SpiTxInit(void)
{
  /*-------------------- DMA configuration --------------------*/
  /* Enable the peripheral clock for DMA2 */
 RCC_AHB1ENR |= (uint32_t)(1UL << 22U);

  /* Disable the DMA2 stream for the configuration */
  DMA2_Stream3->CR = (uint32_t)(0UL << 0U);

  // Wait until the stream is disable */
  while((DMA2_Stream3->CR & ((uint32_t)(1UL << 0U)))) { }

  /*------------------ DMA stream3 parameters ------------------*/
  /* Enable DMA2 transfer error interrupt */
  DMA2_Stream3->CR |= (uint32_t)(1UL << 2U);

  /* Enable DMA2 transfer complete interrupt */
  DMA2_Stream3->CR |= (uint32_t)(1UL << 4U);

  /* Set DMA2 data transfer direction (mem to peripheral) */
  DMA2_Stream3->CR |= (uint32_t)(1UL << 6U);

  /* Set DMA2 memory increment mode */
  DMA2_Stream3->CR |= (uint32_t)(1UL << 10U);

  /* Select channel 3 used for SPI1 */
  DMA2_Stream3->CR |= (uint32_t)(3UL << 25U);

  /* Disable DMA2 direct mode disable */
  DMA2_Stream3->FCR |= (uint32_t)(1UL << 2U);

  /* FIFO threshold selection: full FIFO */
  DMA2_Stream3->FCR |= (uint32_t)(3UL << 0U);

  /* TBD Add MSize */

  /* TBD Enable DMA interrupt trough NVIC */
}

void Dma2Stream2SpiRxInit(void)
{
  /*-------------------- DMA configuration --------------------*/
  /* Enable the peripheral clock for DMA2 */
 RCC_AHB1ENR |= (uint32_t)(1UL << 22U);

  /* Disable the DMA2 stream for the configuration */
  DMA2_Stream2->CR = (uint32_t)(0UL << 0U);

  // Wait until the stream is disable */
  while((DMA2_Stream2->CR & ((uint32_t)(1UL << 0U)))) { }

  /*------------------ DMA stream3 parameters ------------------*/
  /* Enable DMA2 transfer error interrupt */
  DMA2_Stream2->CR |= (uint32_t)(1UL << 2U);

  /* Enable DMA2 transfer complete interrupt */
  DMA2_Stream2->CR |= (uint32_t)(1UL << 4U);

  /* Set DMA2 data transfer direction (peripheral to mem) */
  DMA2_Stream2->CR &= (uint32_t)(~(1UL << 6U) | ~(1UL << 7U));

  /* Set DMA2 memory increment mode */
  DMA2_Stream2->CR |= (uint32_t)(1UL << 10U);

  /* Select channel 3 used for SPI1 */
  DMA2_Stream2->CR |= (uint32_t)(3UL << 25U);

  /* Disable DMA2 direct mode disable */
  DMA2_Stream2->FCR |= (uint32_t)(1UL << 2U);

  /* FIFO threshold selection: full FIFO */
  DMA2_Stream2->FCR |= (uint32_t)(3UL << 0U);

  /* TBD Add PSize */

  /* TBD Enable DMA interrupt trough NVIC */

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
