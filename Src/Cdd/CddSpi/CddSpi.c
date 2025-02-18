#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Gpio.h>
#include <Mcal/Reg.h>


/*--------------------------------------------------
 - static functions
-------------------------------------------------- */
static void WaitFifoStateUntilTimeout(uint32_t Fifo, uint32_t State);
static void CheckEndRxTxTransaction(void);

/*--------------------------------------------------
 - @brief CddSpi_Init

 - @desc Initializes the SPI module.

 - @return void
 ---------------------------------------------------*/
void CddSpi_Init(void)
{
  /* ---  GPIO configuration  --- */
  /* Enable clock for GPIOA */
  RCC_AHB2ENR |= (uint32_t)(1UL << 0U);
  RCC_APB2ENR |= (uint32_t)(1UL << 12U);

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };

  // Configure SPI1 SCK (PA5), MISO (PA6), MOSI (PA7)
  GPIO_InitStruct.Pin       = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;

  GPIO_Init((GPIO_TypeDef *)GPIOA_BASE, &GPIO_InitStruct);

  // Configure CS pin as output
  GPIO_InitStruct.Pin   = GPIO_PIN_4;
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  GPIO_Init((GPIO_TypeDef *)GPIOA_BASE, &GPIO_InitStruct);

  /* Disable SPI peripheral */
  SPI1_CR1 &= ~(uint32_t)(1UL << 6U);



  /*----------------------- SPIx CR1 & CR2 Configuration ---------------------*/
  /* Configure : SPI Mode, Communication Mode, Clock polarity and phase, NSS management,
  Communication speed, First bit and CRC calculation state */

  SPI1_CR1 |= (((0x1UL << 2U) | (0x1UL << 8U))    // SPI_MODE_MASTER;
              |((0x1UL << 9U)                )    // SPI_NSS_SOFT;
              |((0x2UL << (3U))              ));  // SPI_BAUDRATEPRESCALER_8


  SPI1_CR2 |=   (((0x1UL << 9U)  >> 16U))     // SPI_NSS_SOFT
              | ((0x00000700U)          )     // SPI_DATASIZE_8BIT
              | ((0x1UL << 12U)         );    //

  /* Set RX FIFO threshold to 8-bit */
  SPI1_CR2 |= (1UL << 12U);


  /* Enable SPI peripheral */
  SPI1_CR1 |= (uint32_t)(1UL << 6U);
}


/*--------------------------------------------------
 - @brief CddSpi_CsEnable

 - @desc Enables the SPI Chip Select (CS) line

 - @param void

 - @return void
 ---------------------------------------------------*/
void CddSpi_CsEnable(void)
{
  /* Clear the CE bit */
  GPIOA_ODR &= (uint32_t)(~(1UL << 4U));
}


/*--------------------------------------------------
 - @brief CddSpi_CsDisable

 - @desc Disables the SPI Chip Select (CS) line

 - @param void

 - @return void
 ---------------------------------------------------*/
void CddSpi_CsDisable(void)
{
  /* Set the CE bit */
  GPIOA_ODR |= (uint32_t)(1UL << 4U);
}


/*--------------------------------------------------
 - @brief SPI_Transmit

 - @desc This function sends data to the SPI bus

 - @param pTxBuffer: data to be sent over SPI.
          DataSize : data length

 - @return void
 ---------------------------------------------------*/
void SPI_Transmit(const uint8_t* pTxBuffer, uint32_t DataSize)
{
  /* Set the transaction information */
  uint16_t TxTransferCount = DataSize;

  while(TxTransferCount > 0U)
  {
    /* Wait until TXE flag is set to send data */
    if(SPI1_SR & (0x1UL << CDD_SPI_SR_TXE_POS))
    {
      *((volatile uint8_t*) & SPI1_DR) = *((const uint8_t*)(const uint8_t*)pTxBuffer);
      (const uint8_t*)pTxBuffer++;
      TxTransferCount--;
    }
  }

  /* Check the end of the transaction */
  CheckEndRxTxTransaction();
}

/*--------------------------------------------------
 - @brief SPI_TransmitReceive

 - @desc function performs a write-read operation over SPI

 - @param pRxBuffer: receive buffer to store data
           DataSize : data length

 - @return void
 ---------------------------------------------------*/
void SPI_TransmitReceive(uint8_t *pRxBuffer, uint32_t DataSize)
{
  uint32_t RxTransferCount = DataSize;
  uint32_t TxTransferCount = DataSize;

  /* Transmit and Receive data */
  while((TxTransferCount > 0U) || (RxTransferCount > 0U))
  {
    /* Transmit data if TXE is set and Tx buffer has data */
    if((SPI1_SR & (1UL << 1U)) && (TxTransferCount > 0U))
    {
      *((volatile uint8_t*)&SPI1_DR) = (uint8_t)0xFFU;
      TxTransferCount--;
    }

    /* Receive data if RXNE is set and Rx buffer has space */
    if((SPI1_SR & (1UL << 0U)) && (RxTransferCount > 0U))
    {
      *pRxBuffer++ = *((volatile uint8_t*)&SPI1_DR);
      RxTransferCount--;
    }
  }
}


/*--------------------------------------------------
 - @brief SPI_Receive

 - @desc function performs a read operation over SPI

 - @param pRxBuffer: receive buffer to store data
           DataSize : data length

 - @return void
 ---------------------------------------------------*/
void SPI_Receive(uint8_t *pRxBuffer, uint32_t DataSize)
{
  /* Call transmit-receive function to send Dummy data on Tx line and generate clock on CLK line */
  SPI_TransmitReceive(pRxBuffer, DataSize);
}



/*--------------------------------------------------
 - @brief WaitFifoStateUntilTimeout

 - @desc

 - @param


 - @return void
 ---------------------------------------------------*/
static void WaitFifoStateUntilTimeout(uint32_t Fifo, uint32_t State)
{
  while ((SPI1_SR & Fifo) != State)
  {
    /* If FIFO is FRLVL and state is EMPTY, flush the data register */
    if ((Fifo == CDD_SPI_SR_FRLVL) && (State == CDD_SPI_FRLVL_EMPTY))
    {
      (void)*(volatile uint8_t *)&SPI1_DR; // Flush SPI1_DR with a blank read
    }
  }
}


/*--------------------------------------------------
 - @brief CheckEndRxTxTransaction

 - @desc

 - @param


 - @return void
 ---------------------------------------------------*/
static void CheckEndRxTxTransaction(void)
{
  /* Control if the TX fifo is empty */
  WaitFifoStateUntilTimeout(CDD_SPI_FLAG_FTLVL, CDD_SPI_FTLVL_EMPTY);

  /* Control if the RX fifo is empty */
  WaitFifoStateUntilTimeout(CDD_SPI_SR_FRLVL, CDD_SPI_FRLVL_EMPTY);

}
