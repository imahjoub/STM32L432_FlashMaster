
#include "Cdd/CddSerLCD/CddSerLCD_I2c.h"
#include <Cdd/CddI2c/CddI2c.h>
#include "string.h"


/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
static void CddSerLcd_msDelays(unsigned ms_count);


/*----------------------------------------------------------------------------*/
/*                             Global variables                               */
/*----------------------------------------------------------------------------*/
static uint8_t CddSerLcd_SlaveAddr = DISPLAY_ADDRESS;
static uint8_t CddSerLcd_Control   = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
static uint8_t CddSerLcd_Mode      = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;


/*----------------------------------------------------------------------------
- @brief CddSerLcd_msDelays

- @desc ms delay function

- @param ms_count delay time in ms

- @return void
-----------------------------------------------------------------------------*/
static void CddSerLcd_msDelays(unsigned ms_count)
{
  ms_count *= 10U;

  const uint64_t my_timer = TimerStart(ms_count + 1U);

  while (!TimerTimeout(my_timer))
  {
    ;
  }
}

/*----------------------------------------------------------------------------
- @brief CddSerLcd_Init

- @desc Initial start of the display

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Init(void)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
  uint8_t TransmitData[6U] =
  {
    SPECIAL_COMMAND,                            /* special command character */
    LCD_DISPLAYCONTROL | CddSerLcd_Control,       /* display command           */
    SPECIAL_COMMAND,                            /* command character         */
    LCD_ENTRYMODESET   | CddSerLcd_Mode,          /* entry mode command        */
    SETTING_COMMAND,                            /* Put LCD into setting mode */
    CLEAR_COMMAND                               /* clear display             */
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(50U);

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_Home

- @desc Send the home command to the display,  This returns the cursor
        to return to the beginning of the display

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Home(void)
{
  return CddSerLcd_Command(LCD_RETURNHOME);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_SetCursor

- @desc Set the cursor position to a particular column and row.

- @param col   - column number (0...19)
         row   - row number    (0... 3)

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SetCursor(uint8_t col, uint8_t row)
{
  uint8_t row_offsets[] = {0x00U, 0x40U, 0x14U, 0x54U};

  /*send the command */

  uint8_t RetValue = (uint8_t)CddSerLcd_SpecialCommand((uint8_t)LCD_SETDDRAMADDR | (col + row_offsets[row]));

  return RetValue;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_MoveCursorLeft

- @desc Move the cursor one character to the left.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_MoveCursorLeft(void)
{
  return CddSerLcd_SpecialCommand(LCD_CURSORSHIFT | LCD_CURSORMOVE | LCD_MOVELEFT);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_MoveCursorRight

- @desc Move the cursor one character to the right.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_MoveCursorRight(void)
{
  return CddSerLcd_SpecialCommand(LCD_CURSORSHIFT | LCD_CURSORMOVE | LCD_MOVERIGHT);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_ScrollDisplayLeft

- @desc Scroll the display one character to the left, without changing the text

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_ScrollDisplayLeft(void)
{
  return CddSerLcd_SpecialCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_ScrollDisplayRight

- @desc Scroll the display one character to the right, without changing the text

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_ScrollDisplayRight(void)
{
  return CddSerLcd_SpecialCommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_Autoscroll

- @desc Turn autoscrolling on.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Autoscroll(void)
{
   CddSerLcd_Mode |= LCD_ENTRYSHIFTINCREMENT;
   return CddSerLcd_SpecialCommand(LCD_ENTRYMODESET | CddSerLcd_Mode);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_NoAutoscroll

- @desc Turn autoscrolling off.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_NoAutoscroll(void)
{
  CddSerLcd_Mode &= (uint8_t)(~LCD_ENTRYSHIFTINCREMENT);

  return CddSerLcd_SpecialCommand(LCD_ENTRYMODESET | CddSerLcd_Mode);
}


/*----------------------------------------------------------------------------*/
/*                        write on the display                                */
/*----------------------------------------------------------------------------*/

 /*----------------------------------------------------------------------------
- @brief CddSerLcd_Clear

- @desc Send the clear command to the display and forces
        the cursor to return to the beginning

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Clear(void)
{
  uint8_t retval = CddSerLcd_Command(CLEAR_COMMAND);

  CddSerLcd_msDelays(10U);

  return retval;
}


 /*----------------------------------------------------------------------------
- @brief CddSerLcd_Write

- @desc  Write a byte to the display

- @param ByteToWrite     - byte to write

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Write(uint8_t ByteToWrite)
{
  uint8_t retval = LCD_OK;

  // transmission of data stream
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), &ByteToWrite, 1U);

  CddSerLcd_msDelays(10U); // wait a bit

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_WriteString

- @desc  Write a character buffer to the display.

- @param *buffer - pointer to the string to write

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_WriteString(char *buffer)
{
  uint8_t retval = LCD_OK;

  // transmission of data stream
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U) , (uint8_t*)buffer, (uint16_t)strlen(buffer));

  CddSerLcd_msDelays(50U); //This takes a bit longer

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_CreateChar

- @desc  Create a customer character

- @param location - character number 0 to 7
         charmap  - byte array of 8 for character

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_CreateChar(uint8_t location, uint8_t *charmap)
{
  location &= 0x7U; // we only have 8 locations 0-7

  // create i2c data stream
  uint8_t retval = LCD_OK;

  uint8_t TransmitData[10U] =
  {
    SETTING_COMMAND,
      27U + location,
         charmap[0U],
         charmap[1U],
         charmap[2U],
         charmap[3U],
         charmap[4U],
         charmap[5U],
         charmap[6U],
         charmap[7U]
  };

  // transmission of data stream
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));   // transmit data

  CddSerLcd_msDelays(50); //This takes a bit longer

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_WriteChar

- @desc  Write a customer character to the display

- @param location - character number 0 to 7

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_WriteChar(uint8_t location)
{
  location &= 0x7U; // we only have 8 locations 0-7

  return  CddSerLcd_Command(35U + location);
}

/*----------------------------------------------------------------------------*/
/*                       display align                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
- @brief CddSerLcd_LeftToRight

- @desc  Set the text to flow from left to right

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_LeftToRight(void)
{
  CddSerLcd_Mode |= LCD_ENTRYLEFT;
  return CddSerLcd_SpecialCommand(LCD_ENTRYMODESET | CddSerLcd_Mode);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_RightToLeft

- @desc  Set the text to flow from right to left.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_RightToLeft(void)
{
   CddSerLcd_Mode &= (uint8_t)(~LCD_ENTRYLEFT);
   return CddSerLcd_SpecialCommand(LCD_ENTRYMODESET | CddSerLcd_Mode);
}



/*----------------------------------------------------------------------------*/
/*                        show and hide items                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
- @brief CddSerLcd_NoDisplay

- @desc  Turn the display off quickly.

- @param  void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_NoDisplay(void)
{
  CddSerLcd_Control &= (uint8_t)(~LCD_DISPLAYON);
  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_Display

- @desc  Turn the display on quickly.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Display(void)
{
  CddSerLcd_Control |= LCD_DISPLAYON;
  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_NoCursor

- @desc   Turn the underline cursor off.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_NoCursor(void)
{
  CddSerLcd_Control &= (uint8_t)(~LCD_CURSORON);
  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_Cursor

- @desc   Turn the underline cursor on.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Cursor(void)
{
  CddSerLcd_Control |= LCD_CURSORON;
  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}



/*----------------------------------------------------------------------------
- @brief CddSerLcd_NoBlink

- @desc  Turn the blink cursor off.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_NoBlink(void)
{
  CddSerLcd_Control &= (uint8_t)(~LCD_BLINKON);
  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_Blink

- @desc  Turn the blink cursor on.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Blink(void)
{
  CddSerLcd_Control |= LCD_BLINKON;

  return CddSerLcd_SpecialCommand(LCD_DISPLAYCONTROL | CddSerLcd_Control);
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_EnableSystemMessages

- @desc  This allows user to see printing messages like 'UART: 57600'
          and 'Contrast: 5.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_EnableSystemMessages(void)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
    uint8_t TransmitData[2U] =
    {
      SETTING_COMMAND,                   /* special command character */
      ENABLE_SYSTEM_MESSAGE_DISPLAY,     /* set '.' character         */
    };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U);

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_DisableSystemMessages

- @desc  This allows user to disable printing messages like 'UART: 57600'
          and 'Contrast: 5.

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_DisableSystemMessages(void)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
    uint8_t TransmitData[2U] =
    {
      SETTING_COMMAND,
      DISABLE_SYSTEM_MESSAGE_DISPLAY,
    };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U);

  return retval;
}


/*----------------------------------------------------------------------------*/
/*                         display properties                                 */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
- @brief CddSerLcd_SetBacklight

- @desc  Uses a standard rgb byte triplit eg. (255, 0, 255) to
         set the backlight color.

- @param  r     - 0...255
          g     - 0...255
          b     - 0...255

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SetBacklight(uint16_t r, uint16_t g, uint16_t b)
{
  uint8_t retval = LCD_OK;

  // size reduction of the percentage to a value between 0 and 29
  if(r != 0U) { r = (uint16_t)((r * 29U) / 255U); }
  if(g != 0U) { g = (uint16_t)((g * 29U) / 255U); }
  if(b != 0U) { b = (uint16_t)((b * 29U) / 255U); }

  // create i2c data stream
  uint8_t TransmitData[10U] =
  {
    SPECIAL_COMMAND,                                                        /* Send special command character  */
    LCD_DISPLAYCONTROL | (CddSerLcd_Control & (uint8_t)(~LCD_DISPLAYON)),   /* turn display off                */
    SETTING_COMMAND,     (128U + (uint8_t)r),                               /* red  : 0...100% ~ 0...29        */
    SETTING_COMMAND,     (158U + (uint8_t)g),                               /* green: 0...100% ~ 0...29        */
    SETTING_COMMAND,     (188U + (uint8_t)b),                               /* blue : 0...100% ~ 0...29        */
    SPECIAL_COMMAND,                                                        /* Send special command character  */
    LCD_DISPLAYCONTROL | (CddSerLcd_Control |= LCD_DISPLAYON)
  }; // turn display off as before

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(50U);

  return retval;
}

/*----------------------------------------------------------------------------
- @brief CddSerLcd_SetFastBacklight

- @desc  New faster backlight function - Uses a standard rgb byte triplit
         eg. (255, 0, 255) to set the backlight color.

- @param  r     - 0...255
          g     - 0...255
          b     - 0...255

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SetFastBacklight(uint8_t r, uint8_t g, uint8_t b)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
  uint8_t TransmitData[5U] =
  {
    SETTING_COMMAND,                 /* special command character      */
    SET_RGB_COMMAND,                 /* set RGB character '+' or plus  */
    r,                               /* red value                      */
    g,                               /* green value                    */
    b                                /* blue value                     */
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_SetContrast

- @desc  Change the contrast from 0 to 255. 120 is default.

- @param new_val - new contrast value

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SetContrast(uint8_t new_val)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
  uint8_t TransmitData[3U] =
  {
    SETTING_COMMAND,                  /* special command character */
    CONTRAST_COMMAND,                 /* send contrast command     */
    new_val                           /* set new contrast value    */
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10);

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_SetAddress

- @desc Change the I2C Address. 0x72 is the default.
         Note that this change is persistent. If anything
         goes wrong you may need to do a hardware reset
         to unbrick the display.

- @param new_val - new contrast value

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SetAddress(uint8_t new_addr)
{
  uint8_t retval = LCD_OK;

  /* create i2c data stream */
  uint8_t TransmitData[3U] =
  {
    SETTING_COMMAND,             /* special command character */
    ADDRESS_COMMAND,             /* send address command      */
    new_addr                     /* set new address           */
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  /* Update our own address so we can still talk to the display */
  if(retval == LCD_OK) { CddSerLcd_SlaveAddr = new_addr; }

  /* This may take awhile */
  CddSerLcd_msDelays(50);

  return retval;
}

/*----------------------------------------------------------------------------*/
/*                         edit splash screen                                 */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
- @brief CddSerLcd_EnableSplash

- @desc  Enable splash screen at power on

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_EnableSplash(void)
{
  uint8_t retval = LCD_OK;

  /* create i2c data stream */
  uint8_t TransmitData[2U] =
  {
    SETTING_COMMAND,                  /* special command character */
    ENABLE_SPLASH_DISPLAY,            /* set '.' character         */
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U);

  return retval;
}

/*----------------------------------------------------------------------------
- @brief CddSerLcd_DisableSplash

- @desc  Disable splash screen at power on

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_DisableSplash(void)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
  uint8_t TransmitData[2U] =
  {
    SETTING_COMMAND,
    DISABLE_SPLASH_DISPLAY,
  };

  /* transmission of data stream */
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U);

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_SaveSplash

- @desc Save the current display as the splash

- @param void

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SaveSplash(void)
{
  uint8_t retval = LCD_OK;

  // create i2c data stream
  uint8_t TransmitData[2U] =
  {
    SETTING_COMMAND,
    SAVE_CURRENT_DISPLAY_AS_SPLASH,
  };

  // transmission of data stream
  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U);

  return retval;
}


/*----------------------------------------------------------------------------*/
/*                only for internal use - don't touch!                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
- @brief CddSerLcd_Command

- @desc Send a command to the display

- @param command

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_Command(uint8_t command)
{
  uint8_t retval = LCD_OK;

  uint8_t TransmitData[2U] = {SETTING_COMMAND, command};

  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(10U); /* Wait a bit longer for special display commands */

  return retval;
}


/*----------------------------------------------------------------------------
- @brief CddSerLcd_SpecialCommand

- @desc Send a special command to the display.

- @param command

- @return status   - 0...OK, other...error
-----------------------------------------------------------------------------*/
uint8_t CddSerLcd_SpecialCommand(uint8_t command)
{
  uint8_t retval = LCD_OK;

  uint8_t TransmitData[2U] = {SPECIAL_COMMAND, command};

  I2C_Transmit((uint16_t)(DISPLAY_ADDRESS << 1U), TransmitData, sizeof(TransmitData));

  CddSerLcd_msDelays(50U); //Wait a bit longer for special display commands

  return retval;
}













