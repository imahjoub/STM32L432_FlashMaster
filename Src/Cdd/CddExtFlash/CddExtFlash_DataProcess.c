
#include "Cdd/CddExtFlash/CddExtFlash_DataProcess.h"
#include "Cdd/CddSpi/CddSpi.h"
#include <Util/UtilTimer.h>

static void Flash_msDelays(unsigned ms_count);

/*----------------------------------------------------------------------------
- @brief Flash_msDelays

- @desc ms delay function

- @param ms_count delay time in ms

- @return void
-----------------------------------------------------------------------------*/
static void Flash_msDelays(unsigned ms_count)
{
  ms_count *= 10U;

  const uint64_t my_timer = TimerStart(ms_count + 1U);

  while (!TimerTimeout(my_timer))
  {
    ;
  }
}

/*----------------------------------------------------------------------------
- @brief Flash_Receive

- @desc

- @param void

- @return void
-----------------------------------------------------------------------------*/
uint8_t Flash_Receive(uint8_t* data, uint16_t dataSize)
{
  SPI_Receive(data, dataSize);

  return data[0U];
}


/*----------------------------------------------------------------------------
- @brief Flash_WaitForWriteToBeEnabled

- @desc keeps looping inside this function until "BUSY" bit in SR1 register
        becomes 0, meaning that the runnin data operation (writing or erasing)
        on the chip, ended

- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_WaitForWriteToBeEnabled(void)
{
  uint8_t buffer[2U] = { EXT_FLASH_R_SR1, 0XFF };
  CddSpi_CsEnable();
  buffer[0U] = EXT_FLASH_R_SR1;

  SPI_Transmit(&buffer[0U], 1U);

  do
  {
    Flash_Receive(&buffer[1U], 1U);  //SR1 is repeteadly sent until Flash is selected
  } while (!(buffer[1U] & SR1_BIT_WEL));

  CddSpi_CsDisable();
}


/*----------------------------------------------------------------------------
- @brief Flash_WaitForWritingComplete

- @desc keeps looping inside this function until "BUSY" bit in SR1 register
        becomes 0, meaning that the runnin data operation (writing or erasing)
        on the chip, ended
- @param void

- @return void
-----------------------------------------------------------------------------*/

void Flash_WaitForWritingComplete(void)
{
  uint8_t buffer[2U] = { EXT_FLASH_R_SR1, 0XFF};
  CddSpi_CsEnable();
  buffer[0U] = EXT_FLASH_R_SR1;

  SPI_Transmit(&buffer[0U], 1);

  do
  {
    buffer[1U] = 0xFFU;
    Flash_Receive(&buffer[1U], 1U);  /*SR1 is repeteadly sent until Flash is selected */
  } while ((buffer[1U] & SR1_BIT_BUSY));

  CddSpi_CsDisable();
}


/*----------------------------------------------------------------------------
- @brief Flash_Read

- @desc reads from Flash Eeprom

- @param  addr    EEPROM address to start reading
          data    buffer to fill with read data
          dataSize  number of bytes to read

- @return void
-----------------------------------------------------------------------------*/
void Flash_Read(uint32_t addr, uint8_t* data, uint32_t dataSize)
{
  //uint16_t data_to_transfer;

  uint8_t buffer[5];

  buffer[0U] = FLASH_READ_COMMAND;
  buffer[1U] = ((addr >> 16U) & 0xFFU);
  buffer[2U] = ((addr >>  8U) & 0xFFU);
  buffer[3U] = ((addr >>  0U) & 0xFFU);
  buffer[4U] = EXT_FLASH_DUMMY;

  CddSpi_CsEnable();

  SPI_Transmit(buffer, 4U);  // "normal/slow" read command doesn't need sending dummy byte

  uint8_t DummyRead[1U] = {0xFFU};

  for (unsigned index = (unsigned)0U; index < dataSize; ++index)
  {
    data[index] = Flash_Receive(DummyRead, 1U);
  }

  CddSpi_CsDisable();
}


/*----------------------------------------------------------------------------
- @brief Flash_SimpleWriteAPage

- @desc it writes into a single FLASH page

- @param  addr    EEPROM address to start writing
          data    buffer containing data to write into EEPROM
          dataSize  number of bytes to write

- @return void
-----------------------------------------------------------------------------*/
void Flash_SimpleWriteAPage(uint32_t addr, uint8_t* data, uint32_t dataSize)
{
  uint8_t buffer_WEL[1U];

  /* write enable */
  CddSpi_CsEnable();
  buffer_WEL[0U] = EXT_FLASH_W_ENABLE;
  SPI_Transmit(buffer_WEL, 1U);
  CddSpi_CsDisable();
  Flash_WaitForWriteToBeEnabled();


  uint8_t buffer[4U];
  buffer[0] = EXT_FLASH_PAGE_P;
  buffer[1] = ((addr >> 16U) & 0xFFU);
  buffer[2] = ((addr >>  8U) & 0xFFU);
  buffer[3] = ((addr >>  0U) & 0xFFU);

  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4U);
  SPI_Transmit(data, dataSize);
  CddSpi_CsDisable();

  Flash_WaitForWritingComplete();
}


/*----------------------------------------------------------------------------
- @brief Flash_Write

- @desc function writing into EEPROM
        Handling "write enable" commands
        It splits (if needed) received data into the single pages,
        lounching writing sessions for each page
        and waiting the writing complete each time

- @param  addr    EEPROM address to start writing
          data    buffer containing data to write into EEPROM
          dataSize  number of bytes to write

- @return void
-----------------------------------------------------------------------------*/
void Flash_Write(uint32_t addr, uint8_t* data, uint32_t dataSize)
{
  uint8_t  buffer[4U];
  uint16_t quota;
  uint32_t inpage_addr;

  if (dataSize != 0)
  {
    // quota is the data size transferred until now
    quota = 0U;

    // define the starting write position inside the first Flash page to write...
    inpage_addr = addr & (EXT_FLASH_PAGE_SIZE - 1U);

    // so I can detect if more than 1 Flash page has still to be written
    while ((dataSize - quota + inpage_addr) > EXT_FLASH_PAGE_SIZE)
    {
      //loop here inside, until more than 1 Flash page...
      CddSpi_CsEnable();
      buffer[0] = EXT_FLASH_W_ENABLE;
      SPI_Transmit(buffer, 1);
      CddSpi_CsDisable();
      Flash_SimpleWriteAPage(addr + quota, data + quota, (EXT_FLASH_PAGE_SIZE - inpage_addr));
      quota += (uint16_t)(EXT_FLASH_PAGE_SIZE - inpage_addr);
      // having aligned data to page border on the first writing
      // next writings start from 0 position inside a page
      inpage_addr = 0;
      Flash_WaitForWritingComplete();
    }

    // now just the final Flash page
    if (dataSize - quota)
    {
      CddSpi_CsEnable();
      buffer[0] = EXT_FLASH_W_ENABLE;
      SPI_Transmit(buffer, 1);
      CddSpi_CsDisable();
      Flash_SimpleWriteAPage(addr + quota, data + quota, (uint16_t)(dataSize - quota));
      Flash_WaitForWritingComplete();
    }
  }
}



/*----------------------------------------------------------------------------
- @brief Flash_SErase4k

- @desc  Erase to 0XFF all bytes in a 4k block
         4k block bounary is 0x1000, that means:
         0x1000, 0x2000, 0x3000, ..
         waiting the writing complete in each page

- @param  addr  starting erase address
          (it must be a 4k sector boundary)

- @return void
-----------------------------------------------------------------------------*/
void Flash_SErase4k(uint32_t addr)
{
  uint8_t buffer[4U];

  /* Write Enable */
  CddSpi_CsEnable();
  buffer[0U] = EXT_FLASH_W_ENABLE;
  SPI_Transmit(buffer, 1U);
  CddSpi_CsDisable();

  Flash_WaitForWriteToBeEnabled();

  /* Erase sector: 15 pages */
  buffer[0U] = EXT_FLASH_S_ERASE4K;
  buffer[1U] = ((addr >> 16U) & 0xFFU);
  buffer[2U] = ((addr >>  8U) & 0xFFU);
  buffer[3U] = ((addr >>  0U) & 0xFFU);

  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4U);
  CddSpi_CsDisable();

  Flash_WaitForWritingComplete();
}


/*----------------------------------------------------------------------------
- @brief Flash_BErase32k

- @desc  Erase to 0XFF all bytes in a 32k block
         32k block bounary is 0x08000, that means:
         0x008000, 0x010000, 0x018000, ...
         waiting the writing complete in each page

- @param  addr  starting erase address
         (it must be a 32k block boundary)

- @return void
-----------------------------------------------------------------------------*/
void Flash_BErase32k(uint32_t addr) {
  uint8_t buffer[4];
  CddSpi_CsEnable();
  buffer[0] = EXT_FLASH_W_ENABLE;
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();

  buffer[0] = EXT_FLASH_B_ERASE32K;
  buffer[1] = (addr >> 16) & 0xFF;
  buffer[2] = (addr >> 8) & 0xFF;
  buffer[3] = addr & 0xFF;
  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4);
  CddSpi_CsDisable();
  Flash_WaitForWritingComplete();
}



/*----------------------------------------------------------------------------
- @brief Flash_BErase64k

- @desc  Erase to 0XFF all bytes in a 64k block
         64k block bounary is 0x08000, that means:
         0x010000, 0x020000, 0x030000, ...
         waiting the writing complete in each page

- @param  addr  starting erase address
         (it must be a 64k block boundary)

- @return void
-----------------------------------------------------------------------------*/
void Flash_BErase64k(uint32_t addr)
{
  uint8_t buffer[4];
  CddSpi_CsEnable();
  buffer[0] = EXT_FLASH_W_ENABLE;
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();

  buffer[0] = EXT_FLASH_B_ERASE64K;
  buffer[1] = (addr >> 16) & 0xFF;
  buffer[2] = (addr >> 8) & 0xFF;
  buffer[3] = addr & 0xFF;
  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4);
  CddSpi_CsDisable();
  Flash_WaitForWritingComplete();
}



/*----------------------------------------------------------------------------
- @brief Flash_ChipErase

- @desc  Full chip erase to 0XFF
         Chip Erase may need up to 100s

- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_ChipErase(void)
{
  uint8_t buffer[4];
  CddSpi_CsEnable();
  buffer[0] = EXT_FLASH_W_ENABLE;
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();

  buffer[0] = EXT_FLASH_CH_ERASE;
  CddSpi_CsEnable();
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();
  Flash_WaitForWritingComplete();
}



/*----------------------------------------------------------------------------
- @brief Flash_PowerDown

- @desc  Initiates a powerdown after a powerDown only accepted a porweUp command
         opwerDown operation is 3us long

- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_PowerDown(void)
{
  uint8_t buffer[4];

  buffer[0] = EXT_FLASH_POWERDOWN;
  CddSpi_CsEnable();
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();
}


/*----------------------------------------------------------------------------
- @brief Flash_PowerUp

- @desc   Release from powerdown (3 us to restart) or read device ID

- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_PowerUp(void)
{
  uint8_t buffer[4];

  buffer[0] = EXT_FLASH_POWERUP_ID;
  CddSpi_CsEnable();
  SPI_Transmit(buffer, 1);
  CddSpi_CsDisable();
  Flash_msDelays(1);
}


/*----------------------------------------------------------------------------
- @brief Flash_ReadDevID

- @desc  read device id from chip

- @param void

- @return device id
-----------------------------------------------------------------------------*/
uint8_t Flash_ReadDevID(void)
{
  uint8_t buffer[4];
  uint8_t data;

  buffer[0U] = EXT_FLASH_POWERUP_ID;
  buffer[1U] = EXT_FLASH_DUMMY;
  buffer[2U] = EXT_FLASH_DUMMY;
  buffer[3U] = EXT_FLASH_DUMMY;

  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4U);
  Flash_Receive(&data, 1U);
  CddSpi_CsDisable();

  return (uint8_t)data;
}


/*----------------------------------------------------------------------------
- @brief Flash_ReadManufactutrerAndDevID

- @desc  ReadManufactutrerAndDevID

- @param void

- @return ManufactutrerAndDevID
-----------------------------------------------------------------------------*/
uint8_t Flash_ReadManufactutrerAndDevID(void)
{
  uint8_t  buffer[4U];
  uint8_t data[2U] = { 0xFFU, 0xFFU};

  buffer[0U] = EXT_FLASH_POWERUP_ID;
  buffer[1U] = EXT_FLASH_DUMMY;
  buffer[2U] = EXT_FLASH_DUMMY;
  buffer[3U] = EXT_FLASH_DUMMY;

  CddSpi_CsEnable();
  SPI_Transmit(buffer, 4U);
  Flash_Receive(data, 2U);
  CddSpi_CsDisable();

  return data;
}

/*----------------------------------------------------------------------------
- @brief Flash_ReadSFDP

- @desc

- @param void

- @return 256byte SFDP register content:
-----------------------------------------------------------------------------*/
void Flash_ReadSFDP(uint8_t* data)
{
  uint8_t buffer[5U];

  buffer[0U] = EXT_FLASH_R_SFPD_REG;

  for (uint8_t k = 1U; k < 5U; k++)
  {
    buffer[k] = 0U;
  }

  CddSpi_CsEnable();

  SPI_Transmit(buffer, 5U);
  Flash_Receive(data, 256U);

  CddSpi_CsDisable();
}




/*----------------------------------------------------------------------------
- @brief Flash_TestAvailability

- @desc  testing chip alive and kicking
         reading SFDP record, it must return
         a string beginning with "SFDP"

- @param void

- @return 1   test passed
          0   test failed
-----------------------------------------------------------------------------*/
uint8_t Flash_TestAvailability(void)
{
  uint8_t data[256U] = {0U};

  uint8_t test = 1U;

  for (uint8_t k = 0U; k != 254U; k++)
  {
    data[k] = 0xFFU;
  }

  Flash_ReadSFDP(data);

  if (data[0] != 'S') { test = 0U; }
  if (data[1] != 'F') { test = 0U; }
  if (data[2] != 'D') { test = 0U; }
  if (data[3] != 'P') { test = 0U; }

  return test;
}


/*----------------------------------------------------------------------------
- @brief Flash_unblockChip

- @desc remove write protection from chip

- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_unblockChip(void)
{
  uint8_t buffer[4];
  buffer[0U] = EXT_FLASH_W_ENABLE;
  buffer[1U] = EXT_FLASH_W_SR1;
  buffer[2U] = 0U;
  buffer[3U] = 0U;

  CddSpi_CsEnable();
  SPI_Transmit(&buffer[0], 1);
  CddSpi_CsDisable();

  CddSpi_CsEnable();
  SPI_Transmit(&buffer[1U], 1U);
  SPI_Transmit(&buffer[2U], 1U);
  CddSpi_CsDisable();

  Flash_WaitForWritingComplete();
}

/*----------------------------------------------------------------------------
- @brief Flash_readStsRegister

- @desc Read status register

- @param void

- @return status register
-----------------------------------------------------------------------------*/
uint8_t Flash_readStsRegister(void)
{

  uint8_t Transfer[1U] = {0U};
  uint8_t Receive[1U]  = {0xFFU};

  CddSpi_CsEnable();

  Transfer[0U] = EXT_FLASH_R_SR1;
  SPI_Transmit(Transfer, 1);

  Flash_Receive(Receive, 2U);  //SR1 is repeteadly sent until Flash is selected

  CddSpi_CsDisable();

  return (uint32_t)Receive;

}




/*----------------------------------------------------------------------------
- @brief Flash_readStsRegister

- @desc reading manufacutrer and device ID
        checking if connected device is a Winbond Flash

- @param void

- @return status register
-----------------------------------------------------------------------------*/
uint8_t Flash_Init(void)
{
  uint32_t JedecID = 1U;

  Flash_msDelays(6);  // supposing init is called on system startup: 5 ms (tPUW) required after power-up to be fully available
  Flash_Reset();

  if (!Flash_TestAvailability()) { JedecID = 0;}

  JedecID = Flash_ReadManufactutrerAndDevID();  //select the memSize byte

  if (((JedecID >> 16) & 0XFF) != 0x9D) { JedecID = 0; }

  return (uint8_t)JedecID;
}



/*----------------------------------------------------------------------------
- @brief Flash_Reset

- @desc reset the chip


- @param void

- @return void
-----------------------------------------------------------------------------*/
void Flash_Reset(void)
{
  uint8_t command;
  command = EXT_FLASH_RESET_EN;
  CddSpi_CsEnable();
  SPI_Transmit(&command, 1);
  CddSpi_CsDisable();

  command = EXT_FLASH_RESET;
  CddSpi_CsEnable();
  SPI_Transmit(&command, 1);
  CddSpi_CsDisable();
  Flash_msDelays(1);  // 30us needed by resetting
}
