#include <Cdd/CddSpi/CddSpi.h>
#include <Mcal/Reg.h>



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

  /* Configure GPIO pins for SPI (SPI1 on PA5, PA6, and PA7) */
  /* Set PA5, PA6, PA7 to alternate function mode            */
  GPIOA_MODER &= (uint32_t)(~(1U << 10U));
  GPIOA_MODER |= (uint32_t) (1U << 11U);

  GPIOA_MODER &= (uint32_t)(~(1U << 12U));
  GPIOA_MODER |= (uint32_t)(1U << 13U);

  GPIOA_MODER &= (uint32_t)(~(1U << 14U));
  GPIOA_MODER |= (uint32_t) (1U << 15U);


  /* Set alternate function for PA5, PA6, PA7 (SPI1) */
  GPIOA_AFRL  |= (uint32_t)((5U << 20U));
  GPIOA_AFRL  |= (uint32_t)((5U << 24U));
  GPIOA_AFRL  |= (uint32_t)((5U << 28U));

  /* ---  SPI configuration  --- */
  /* Enable the Spi peripheral clock */
  RCC_APB2ENR |= (uint32_t)(1UL << 12U);

  /* Set Software slave management     */
  /* Internal slave select             */
  /* Software slave management enabled */
  SPI1_CR1 |= (uint32_t)(1U << 8U);
  SPI1_CR1 |= (uint32_t)(1U << 9U);

  /* Baud rate configuration */
  SPI1_CR1 |= (uint32_t)(2UL << 3U);

  /* Configure SPI */
  /* Set master mode, clock polarity 0, clock phase 0 */
  SPI1_CR1 |= (uint32_t)((0UL << 0U)| (0UL << 1U) | (1UL << 2U));

  /* Enable Tx/Rx buffer DMA  */
  //SPI1_CR2 |= (uint32_t)((1UL << 0U) | (1UL << 1U));

  /* Enable SPI */
  SPI1_CR1 |= (uint32_t)(1UL << 6U);
}


/*--------------------------------------------------
 - @brief CddSpi_CsInit

 - @desc Initializes the Chip Select (CS) lines
         for SPI communication.

 - @return void
 ---------------------------------------------------*/
void CddSpi_CsInit(void)
{
  /* Configure GPIO pins for SPI PA4 CS */
  /* Set PA4 to output mode             */
  /* Set output speed to high           */
  /* No pull-up, pull-down              */
  GPIOA_MODER   |= (uint32_t)(1UL << 8U);
  GPIOA_MODER   &= (uint32_t)(~(1UL << 9U));
}


/*--------------------------------------------------
 - @brief CddSpi_WriteMultipleBytes

 - @desc Writes multiple bytes to an SPI device.

 - @param pSrc Pointer to the source data array
 - @param DataLen The number of bytes needs to be transmitted.

 - @return bool Returns write operation was
           successful or not.
 ---------------------------------------------------*/
bool CddSpi_WriteMultipleBytes(const uint8_t* pSrc, const unsigned DataLen)
{
  for(unsigned index = (unsigned) 0U; index < DataLen; ++index)
  {
    (void) CddSpi_TransferSingleByte(pSrc[index]);
  }

  /* TBD make a significant check here */
  return true;
}

bool CddSpi_ReadMultipleBytes(uint8_t* pDest, const unsigned DataLen)
{
  for(unsigned index = (unsigned) 0U; index < DataLen; ++index)
  {
    pDest[index] = CddSpi_TransferSingleByte(0xFFU);
  }

  /* TBD make a significant check here */
  return true;
}


/*--------------------------------------------------
 - @brief CddSpi_TransferSingleByte

 - @desc This function sends one byte to the SPI bus

 - @param TxData Byte to be sent over SPI.

 - @return uint8_t Received byte from SPI transaction.
 ---------------------------------------------------*/
uint8_t CddSpi_TransferSingleByte(const uint8_t TxData)
{
  /* Put data into TXFIFO */
  SPI1_DR = (uint8_t)TxData;

  /* Wait until transmission complete */
  while (!(SPI1_SR & (1UL << 1U)));

  /* Wait until receive buffer not empty */
  while (!(SPI1_SR & (1UL << 0U)));

  /* Empty the RXFIFO */
  return (uint8_t)(SPI1_DR);
}


/*--------------------------------------------------
 - @brief CddSpi_WriteRead

 - @desc Performs a write-read operation over SPI

 - @param TxData Byte to be transmitted over SPI.

 - @return uint8_t Received byte from the SPI
 ---------------------------------------------------*/
uint8_t CddSpi_WriteRead(uint8_t TxData)
{
  uint8_t ReadBuff = 0U;
  CddSpi_TransferSingleByte(TxData);
  ReadBuff = CddSpi_TransferSingleByte(0xFFU);
  return ReadBuff;
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
