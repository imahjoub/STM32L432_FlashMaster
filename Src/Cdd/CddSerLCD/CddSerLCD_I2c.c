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

void CddSerLCD_I2c_PrintString(char* StringToPrint, uint8_t StringSize)
{
  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, StringSize, CDD_SERLCD_MODE_WRITE);

  /* Print string */
  CddI2c_TransferMultipleBytes((uint8_t*)StringToPrint, StringSize);

  /* Stop condition */
  CddI2c_Stop();
}


void CddSerLCD_I2c_SendCommand(uint8_t Command)
{
  /* LCD command buffer */
  const uint8_t LCDCmdBuffer[2U] = { CDD_SERLCD_SETTING_MODE, Command};
  const size_t  LCDCmdBufferSize =  (size_t)((sizeof(LCDCmdBuffer) / sizeof(LCDCmdBuffer[0])));

  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 2U, CDD_SERLCD_MODE_WRITE);

  /* Command mode */
  CddI2c_TransferMultipleBytes(LCDCmdBuffer, LCDCmdBufferSize);

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
  static const uint8_t SizeofIndexTable = 4U;
  static const uint8_t IndexToRowTable[4U] = { 0U, 64U, 20U, 84U };

  /* Start, set slave address to write */
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, SizeofIndexTable, CDD_SERLCD_MODE_WRITE);

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
  CddI2c_StartTransmission(CDD_SERLCD_ADDRESS, 20U, CDD_SERLCD_MODE_WRITE);

  for(size_t idx = (size_t) 0U; idx < (size_t) 20U; ++idx)
  {
    /* Delay to ensure the command is processed */
    CddSerLcd_I2c_msDelays(4U);

    const char CharToWrite = ((idx < SizeToWrite) ? StringToPrint[idx] : ' ');

    /* Send next character. */
    CddI2c_TransferSingleByte(CharToWrite);

    /* Delay to ensure the command is processed */
    CddSerLcd_I2c_msDelays(4U);

  }

  /* Stop condition */
  CddI2c_Stop();
}
