#include <stdbool.h>

#include <Cdd/CddI2c/CddI2c.h>
#include <Mcal/Gpio.h>
#include <Mcal/Reg.h>


/* ----------------------------------------------------------------------------------- */
/*  Functions prototypes                                                               */
/* ----------------------------------------------------------------------------------- */
static void CddI2c_TransferConfig(uint16_t DevAddress, uint8_t Size, uint32_t Mode, uint32_t Request);


/*----------------------------------------------------------------------------
- @brief CddI2c_Init

- @desc  Initializes the I2C1 peripheral by enabling the necessary clocks,
         configuring GPIO pins for I2C communication, and setting up the
         I2C module with the required

- @param void

- @return void
-----------------------------------------------------------------------------*/
void CddI2c_Init(void)
{
  /* Enable clock for GPIOB */
  RCC_AHB2ENR |= (uint32_t)(1UL << 1U);
    /* Enable clock  for I2C1 */
  RCC_APB1ENR1 |= (uint32_t)(1UL << 21U);

  /*---------------------  GPIO configuration  ---------------------*/

  /* Configure the I2C SCL & SDA pins  */
  GPIO_InitTypeDef GPIO_InitStruct = { 0U };
  GPIO_InitStruct.Pin              = GPIO_PIN_6 | GPIO_PIN_7;  /* PB8 = SCL, PB9 = SDA  */
  GPIO_InitStruct.Mode             = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull             = GPIO_NOPULL;
  GPIO_InitStruct.Speed            = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate        = GPIO_AF4_I2C1;

  GPIO_Init((GPIO_TypeDef *)GPIOB_BASE, &GPIO_InitStruct);

  /*--------------------- I2C1 configuration  ---------------------*/
  /* Enable clock  for I2C1 */
  /* Use timing configuration for your I2C speed 100kHz  */
  uint32_t Timing            = 0x00707CBBUL;
  uint32_t OwnAddress        = 0U;
  uint32_t OwnAddress2       = 0U;
  uint32_t GeneralCallMode   = CDD_I2C_GENERALCALL_DISABLE;
  uint32_t NoStretchMode     = CDD_I2C_NOSTRETCH_DISABLE;

  /* Disable the selected I2C peripheral */
  I2C1_CR1 &= (uint32_t)(~(1UL << 0U));

  /*---------------------------- I2Cx TIMINGR Configuration ------------------*/
  /* Configure I2Cx: Frequency range */
  I2C1_TIMINGR = ((Timing) & CDD_I2C_TIMING_CLEAR_MASK);

  /*---------------------------- I2Cx OAR1 Configuration ---------------------*/
  /* Disable Own Address1 before set the Own Address1 configuration */
  I2C1_OAR1 &= ~CDD_I2C_OAR1_OA1EN;

  I2C1_OAR1 = (CDD_I2C_OAR1_OA1EN | OwnAddress);

  /*---------------------------- I2Cx CR2 Configuration ----------------------*/
  /* Clear the I2C ADD10 bit */
  I2C1_CR2 &= ~CDD_I2C_CR2_ADD10;

  /* Enable the AUTOEND by default, and enable NACK (should be disable only during Slave process */
  I2C1_CR2 |= (CDD_I2C_CR2_AUTOEND | CDD_I2C_CR2_NACK);

  /*---------------------------- I2Cx OAR2 Configuration ---------------------*/
  /* Disable Own Address2 before set the Own Address2 configuration */
  I2C1_OAR2 &= ~CDD_I2C_OAR2_OA2EN;

  /* Configure I2Cx: Dual mode and Own Address2 */
  I2C1_OAR2 = ((CDD_I2C_DUALADDRESS_DISABLE | OwnAddress2) << 8);

  /*---------------------------- I2Cx CR1 Configuration ----------------------*/
  /* Configure I2Cx: Generalcall and NoStretch mode */
  I2C1_CR1 = (GeneralCallMode | NoStretchMode);

  /* Enable the selected I2C peripheral */
  I2C1_CR1 |= (uint32_t)((1UL << 0U));

}



/*----------------------------------------------------------------------------
- @brief CddI2c_TransferConfig

- @desc This function sets up the I2C transfer configuration

- @param DevAddress  : The 7-bit or 10-bit device address of the I2C slave.
         Size        : The number of bytes to transfer.
         Mode        : The I2C mode (e.g., Transmit or Receive)
         Request     : The I2C request type (e.g., Start, Stop).

- @return void
-----------------------------------------------------------------------------*/
static void CddI2c_TransferConfig(uint16_t DevAddress, uint8_t Size, uint32_t Mode, uint32_t Request)
{
  /* Slave address */
  uint32_t DeviceAddress  = (uint32_t)(DevAddress                & CDD_I2C_CR2_SADD);
  /* Number of bytes to transfer */
  uint32_t NumberOfBytes  = (uint32_t)(((uint32_t)(Size << 16U)) & CDD_I2C_CR2_NBYTES);
  /* Combine I2C Mode and Request settings */
  uint32_t ModeAndRequest = (uint32_t)((uint32_t)Mode | (uint32_t)Request);

  /* Update the I2C1_CR2 register with the new configuration */
  I2C1_CR2 |= (DeviceAddress | NumberOfBytes | ModeAndRequest);
}

/*----------------------------------------------------------------------------
- @brief I2C_Transmit

- @desc Transmits data over I2C to a specified device.

- @param DevAddress  The 7-bit or 10-bit I2C address of the target device.
         pData       Pointer to the buffer containing the data to be transmitted.
         Size        Number of bytes to transmit.

- @return void
-----------------------------------------------------------------------------*/
void I2C_Transmit(uint16_t DevAddress, uint8_t* pData, uint16_t Size)
{
  /* Configure and start the I2C transfer */
  CddI2c_TransferConfig(DevAddress, Size, CDD_I2C_CR2_AUTOEND, CDD_I2C_GENERATE_START_WRITE);

  for (uint16_t i = 0U; i < Size; ++i)
  {
    /* Wait until TXIS flag is set */
    while (!(I2C1_ISR & CDD_I2C_ISR_TXIS));

    /* Write data to TXDR */
    I2C1_TXDR = pData[i];
  }

  /* Wait for the transfer to complete */
  while (!(I2C1_ISR & CDD_I2C_ISR_STOPF));

  /* Clear the STOP flag and reset configuration */
  I2C1_ICR = CDD_I2C_ISR_STOPF;

  /* Clear Configuration Register 2 */
  I2C1_CR2 &= ~((uint32_t)( CDD_I2C_CR2_SADD   | CDD_I2C_CR2_HEAD10R | CDD_I2C_CR2_NBYTES | CDD_I2C_CR2_RELOAD | CDD_I2C_CR2_RD_WRN));
}


