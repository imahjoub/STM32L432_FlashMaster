#include <Cdd/CddSerLcd/CddSerLCD_Spi.h>
#include <Cdd/CddSpi/CddSpi.h>

#include <Util/UtilTimer.h>

static void CddSerLcd_Spi_msDelays(const unsigned ms_count)
{
  const uint64_t my_timer = TimerStart(ms_count + 1U);

  while(!TimerTimeout(my_timer))
  {
    ;
  }
}

static void CddSerLcd_Spi_ClearLCD(void)
{
  /* Wait 500ms */
  CddSerLcd_Spi_msDelays(500U);
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Send clear display command and move cursor to home */
  CddSpi_TransferSingleByte(CDD_SERLCD_SETTING_MODE);
  CddSerLcd_Spi_msDelays(4U);
  CddSpi_TransferSingleByte(CDD_SERLCD_CLEAR_DISPLAY);
  CddSerLcd_Spi_msDelays(4U);

 /* Chip select disable */
  CddSpi_CsDisable();
}

static void CddSerLcd_Spi_SetBlueBacklight(void)
{
  /* Chip select enable */
  CddSpi_CsEnable();

  /* Set Backlight into Blue */
  CddSpi_TransferSingleByte(CDD_SERLCD_SETTING_MODE);
  CddSerLcd_Spi_msDelays(4U);
  CddSpi_TransferSingleByte(CDD_SERLCD_BLUE_BACKLIGHT);
  CddSerLcd_Spi_msDelays(4U);

 /* Chip select disable */
  CddSpi_CsDisable();
}

static void CddSerLcd_Spi_SetLCDSize(void)
{
  /* Change lines count to 4 */
  /* Chip select enable */
  CddSpi_CsEnable();
  CddSpi_TransferSingleByte(CDD_SERLCD_SETTING_MODE);
  CddSerLcd_Spi_msDelays(4U);
  CddSpi_TransferSingleByte(CDD_SERLCD_SIZE_LINES_04);
  CddSerLcd_Spi_msDelays(4U);
 /* Chip select disable */
  CddSpi_CsDisable();

  /* Change width count to 20 */
  /* Chip select enable */
  CddSpi_CsEnable();
  CddSpi_TransferSingleByte(CDD_SERLCD_SETTING_MODE);
  CddSerLcd_Spi_msDelays(4U);
  CddSpi_TransferSingleByte(CDD_SERLCD_SIZE_WIDTH_20);
  CddSerLcd_Spi_msDelays(4U);
 /* Chip select disable */
  CddSpi_CsDisable();
}

static void CddSerLcd_Spi_SelectLine(const size_t LineIndexToUse)
{
  /* To set the active cursor position, send the control character 254 followed by 128 + row + position */
  /* OpenLCD.write(254); */
  /* OpenLCD.write(128 + 64 + 9); //Change the position (128) of the cursor to 2nd row (64), position 9 (9) */

  static const uint8_t IndexToRowTable[4U] = { 0U, 64U, 20U, 84U };

 /* Chip select enable */
  CddSpi_CsEnable();

  CddSpi_TransferSingleByte(0xFEU);
  CddSerLcd_Spi_msDelays(4U);

  CddSpi_TransferSingleByte(0x80U + IndexToRowTable[LineIndexToUse] + 0x00);
  CddSerLcd_Spi_msDelays(4U);

 /* Chip select disable */
  CddSpi_CsDisable();
}

void CddSerLCD_Spi_Init(void)
{
  /* Clear display */
  CddSerLcd_Spi_ClearLCD();

  /* Set blue backlight */
  CddSerLcd_Spi_SetBlueBacklight();

  /* Set blue backlight */
  CddSerLcd_Spi_SetLCDSize();
}

void CddSerLCD_Spi_WriteLine(const char* StringToPrint, const size_t StringSize, const size_t LineIndex)
{
  // Limit to the maximum width of the display width.
  const size_t LineIndexToUse = ((LineIndex > (size_t) 3U) ? (size_t) 3U : LineIndex);

  // Limit to the maximum width of the display width.
  const size_t SizeToWrite = ((StringSize > (size_t) 20U) ? (size_t) 20U : StringSize);

  CddSerLcd_Spi_SelectLine(LineIndexToUse);

  for(size_t idx = (size_t) 0U; idx < (size_t) 20U; ++idx)
  {
    /* Chip select enable */
    CddSpi_CsEnable();
    CddSerLcd_Spi_msDelays(4U);

    const char CharToWrite = ((idx < SizeToWrite) ? StringToPrint[idx] : ' ');

    /* Send next character. */
    CddSpi_TransferSingleByte(CharToWrite);

    /* Chip select disable */
    CddSerLcd_Spi_msDelays(4U);
    CddSpi_CsDisable();

  }

}
