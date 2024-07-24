#include <Cdd/CddSerLCD/CddSerLCD_I2c.h>
#include <Cdd/CddI2c/CddI2c.h>

#include <Util/UtilTimer.h>

void CddSerLcd_I2c_msDelays(const unsigned ms_count)
{
  const uint64_t my_timer = TimerStart(ms_count + 1U);

  while(!TimerTimeout(my_timer))
  {
    ;
  }
}

void CddSerLCD_I2c_PrintString(char* StringToPrint)
{
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 0);

  while (*StringToPrint)
  {
    CddI2c_TransferSingleByte((uint8_t)(*StringToPrint));
    ++StringToPrint;
  }

  CddI2c_Stop();
}


void CddSerLCD_I2c_SendCommand(uint8_t Command)
{
  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 0U);

  /* Command mode */
  CddI2c_TransferSingleByte(CDD_SERLCD_SETTING_MODE);

  /* Send the command */
  CddI2c_TransferSingleByte(Command);

  /* Stop condition */
  CddI2c_Stop();
}

static void CddSerLcd_I2c_ClearLCD(void)
{
  /* Clear Display */
  CddSerLCD_I2c_SendCommand(CDD_SERLCD_CLEAR_DISPLAY);
  /* Delay to ensure the clear command is processed */
  CddSerLcd_I2c_msDelays(5U);
}

static void CddSerLcd_I2c_SetBlueBacklight(void)
{
  /* Set Backlight into Blue */
  CddSerLCD_I2c_SendCommand(CDD_SERLCD_BLUE_BACKLIGHT);
  CddSerLcd_I2c_msDelays(5U);
}

static void CddSerLcd_I2c_SetLCDSize(void)
{
  /* Change lines count to 4 */
  CddSerLCD_I2c_SendCommand(CDD_SERLCD_SIZE_LINES_04);
  CddSerLcd_I2c_msDelays(4U);

  /* Change width count to 20 */
  CddSerLCD_I2c_SendCommand(CDD_SERLCD_SIZE_WIDTH_20);
  CddSerLcd_I2c_msDelays(4U);
}

static void CddSerLcd_I2c_SelectLine(const size_t LineIndexToUse)
{
  /* To set the active cursor position, send the control character 254 followed by 128 + row + position */
  /* OpenLCD.write(254); */
  /* OpenLCD.write(128 + 64 + 9); //Change the position (128) of the cursor to 2nd row (64), position 9 (9) */

  static const uint8_t IndexToRowTable[4U] = { 0U, 64U, 20U, 84U };

  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 0U);

  CddSerLCD_I2c_SendCommand(0xFEU);
  CddSerLcd_I2c_msDelays(4U);

  CddSerLCD_I2c_SendCommand(0x80U + IndexToRowTable[LineIndexToUse] + 0x00);
  CddSerLcd_I2c_msDelays(4U);

  /* Stop condition */
  CddI2c_Stop();
}

void CddSerLCD_I2c_Init(void)
{
  /* Clear display */
  CddSerLcd_I2c_ClearLCD();

  /* Set blue backlight */
  CddSerLcd_I2c_SetBlueBacklight();

  /* Set blue backlight */
  CddSerLcd_I2c_SetLCDSize();
}

void CddSerLCD_I2c_WriteLine(const char* StringToPrint, const size_t StringSize, const size_t LineIndex)
{
  // Limit to the maximum width of the display width.
  const size_t LineIndexToUse = ((LineIndex > (size_t) 3U) ? (size_t) 3U : LineIndex);

  // Limit to the maximum width of the display width.
  const size_t SizeToWrite = ((StringSize > (size_t) 20U) ? (size_t) 20U : StringSize);

  CddSerLcd_I2c_SelectLine(LineIndexToUse);

  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 0U);

  for(size_t idx = (size_t) 0U; idx < (size_t) 20U; ++idx)
  {
    /* Chip select enable */
    CddSerLcd_I2c_msDelays(4U);

    const char CharToWrite = ((idx < SizeToWrite) ? StringToPrint[idx] : ' ');

    /* Send next character. */
    CddI2c_TransferSingleByte(CharToWrite);

    /* Chip select disable */
    CddSerLcd_I2c_msDelays(4U);

  }

  /* Stop condition */
  CddI2c_Stop();
}
