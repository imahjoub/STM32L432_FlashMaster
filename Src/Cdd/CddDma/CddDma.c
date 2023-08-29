#include <stdbool.h>

#include <Cdd/CddDma/CddDma.h>
#include <Mcal/Reg.h>

volatile bool SpiTransferComplete = false;
volatile bool SpiReceiveComplete  = false;

void DMA2_Stream2_IRQHandler(void);
void DMA2_Stream3_IRQHandler(void);

void Dma2Stream3SpiTxInit(void)
{
  /*-------------------- DMA configuration --------------------*/
  /* Enable the peripheral clock for DMA2 */
  RCC_AHB1ENR |= (uint32_t)(1UL << 22U);

  /* Disable the DMA2 stream for the configuration */
  DMA2_STREAM3->CR = (uint32_t)(0UL << 0U);

  /* Wait until the stream is disable */
  while((DMA2_STREAM3->CR & ((uint32_t)(1UL << 0U)))) { }

  /*------------------ DMA stream3 parameters ------------------*/
  /* Enable DMA2 transfer error interrupt */
  DMA2_STREAM3->CR |= (uint32_t)(1UL << 2U);

  /* Enable DMA2 transfer complete interrupt */
  DMA2_STREAM3->CR |= (uint32_t)(1UL << 4U);

  /* Set DMA2 data transfer direction (mem to peripheral) */
  DMA2_STREAM3->CR |= (uint32_t)(1UL << 6U);

  /* Set DMA2 memory increment mode */
  DMA2_STREAM3->CR |= (uint32_t)(1UL << 10U);

  /* Set memory data size */
  //DMA2_STREAM3->CR &= (uint32_t)(~(3UL << 13U));

  /* Select channel 3 used for SPI1 */
  DMA2_STREAM3->CR |= (uint32_t)(3UL << 25U);

  /* Disable DMA2 direct mode disable */
  DMA2_STREAM3->FCR |= (uint32_t)(1UL << 2U);

  /* FIFO threshold selection: full FIFO */
  DMA2_STREAM3->FCR |= (uint32_t)(3UL << 0U);

  /* Enable DMA2_Stream3_IRQn interrupt */
  NVIC->ISER[1U] = (uint32_t)(1UL << (((uint32_t)59) & 0x1FUL));
}

void Dma2Stream2SpiRxInit(void)
{
  /*-------------------- DMA configuration --------------------*/
  /* Enable the peripheral clock for DMA2 */
 RCC_AHB1ENR |= (uint32_t)(1UL << 22U);

  /* Disable the DMA2 stream for the configuration */
  DMA2_STREAM2->CR = (uint32_t)(0UL << 0U);

  /* Wait until the stream is disable */
  while((DMA2_STREAM2->CR & ((uint32_t)(1UL << 0U)))) { }

  /*------------------ DMA stream3 parameters ------------------*/
  /* Enable DMA2 transfer error interrupt */
  DMA2_STREAM2->CR |= (uint32_t)(1UL << 2U);

  /* Enable DMA2 transfer complete interrupt */
  DMA2_STREAM2->CR |= (uint32_t)(1UL << 4U);

  /* Set DMA2 data transfer direction (peripheral to mem) */
  DMA2_STREAM2->CR &= (uint32_t)(~(3UL << 6U));

  /* Set DMA2 peripheral increment mode */
  DMA2_STREAM2->CR |= (uint32_t)(1UL << 9U);

  /* Set peripheral data size */
  //DMA2_STREAM2->CR &= (uint32_t)(~(3UL << 11U));

  /* Select channel 3 used for SPI1 */
  DMA2_STREAM2->CR |= (uint32_t)(3UL << 25U);

  /* Disable DMA2 direct mode disable */
  DMA2_STREAM2->FCR |= (uint32_t)(1UL << 2U);

  /* FIFO threshold selection: full FIFO */
  DMA2_STREAM2->FCR |= (uint32_t)(3UL << 0U);


  /* Enable DMA2_Stream2_IRQn interrupt */
  NVIC->ISER[1U] = (uint32_t)(1UL << (((uint32_t)58) & 0x1FUL));

}

void Dma2Stream3SpiSend(uint8_t* TxDataPtr, const size_t DataLen)
{
  /* Clear interrupt flags */
  DMA2_LIFCR |= (uint32_t)((1UL << 27U) | (1UL << 25U));

  /* Set peripheral address */
  DMA2_STREAM3->PAR = (uint32_t)(&(SPI_DR));

  /* Set memory address */
  DMA2_STREAM3->M0AR = (uint32_t)TxDataPtr;

  /* Set transfer length */
  DMA2_STREAM3->NDTR = (uint32_t)DataLen;

  /* Enable the DMA stream */
  DMA2_STREAM3->CR |= (uint32_t)(1UL << 0U);
}

void Dma2Stream2SpiReceive(uint8_t* RxDataPtr, const size_t DataLen)
{
  /* Clear interrupt flags */
  DMA2_LIFCR |= (uint32_t)((1UL << 21U) | (1UL << 19U));

  /* Set peripheral address */
  DMA2_STREAM2->PAR = (uint32_t)(&(SPI_DR));

  /* Set memory address */
  DMA2_STREAM2->M0AR = (uint32_t)RxDataPtr;

  /* Set transfer length */
  DMA2_STREAM2->NDTR = DataLen;

  /* Enable the DMA stream */
  DMA2_STREAM2->CR |= (uint32_t)(1UL << 0U);
}

void DMA2_Stream2_IRQHandler(void)
{
  if((DMA2_LISR) & ((uint32_t)(1UL << 21U)))
  {
    /* TBD set global var */
    SpiReceiveComplete = true;

  /* clear flag */
    DMA2_LIFCR |= (uint32_t)(1UL << 21U);
  }

  /* check if transfer error flag occurred */
  if((DMA2_LISR) & ((uint32_t)(1UL << 19U)))
  {
    /* TBD set a global variable or module error flag */
    /* clear flag */
    DMA2_LIFCR |= (uint32_t)(1UL << 19U);
  }
}

void DMA2_Stream3_IRQHandler(void)
{
  if((DMA2_LISR) & ((uint32_t)(1UL << 27U)))
  {
    /* TBD set global var */
    SpiTransferComplete = true;

    /* clear flag */
    DMA2_LIFCR |= (uint32_t)(1UL << 27U);
  }

  /* check if transfer error flag occurred */
  if((DMA2_LISR) & ((uint32_t)(1UL << 25U)))
  {
    /* TBD set a global variable or module error flag */
    /* clear flag */
    DMA2_LIFCR |= (uint32_t)(1UL << 25U);
  }
}
