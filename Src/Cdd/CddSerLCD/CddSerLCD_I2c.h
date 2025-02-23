#ifndef CDD_SER_LCD_I2C
  #define CDD_SER_LCD_I2C

  #include "stdint.h"
  #include <Util/UtilTimer.h>

  /* ----------------------------------------------------------------------------------- */
  /*  Defines                                                                            */
  /* ----------------------------------------------------------------------------------- */

  /* LCD Addr and characteristics */
  #define DISPLAY_ADDRESS                            0x72U            /* This is the default address of the OpenLCD */
  #define MAX_LINES                                     2U            /* display lines (1, 2 or 4)                  */
  #define MAX_COLUMNS                                  16U            /* display columns (16 or 20)                 */

  /* LCD command characters */
  #define SPECIAL_COMMAND                             254U            /* Magic number for sending a special command                                                             */
  #define SETTING_COMMAND                            0x7CU            /* 124, |, the pipe character: The command to change settings: baud, lines, width, backlight, splash, etc */

  /* LCD commands */
  #define CLEAR_COMMAND                              0x2DU            /* 45, -, the dash character: command to clear and home the display */
  #define CONTRAST_COMMAND                           0x18U            /* Command to change the contrast setting                           */
  #define ADDRESS_COMMAND                            0x19U            /* Command to change the i2c address                                */
  #define SET_RGB_COMMAND                            0x2BU            /* 43, +, the plus character: command to set backlight RGB value    */
  #define ENABLE_SYSTEM_MESSAGE_DISPLAY              0x2EU            /* 46, ., command to enable system messages being displayed         */
  #define DISABLE_SYSTEM_MESSAGE_DISPLAY             0x2FU            /* 47, /, command to disable system messages being displayed        */
  #define ENABLE_SPLASH_DISPLAY                      0x30U            /* 48, 0, command to enable splash screen at power on               */
  #define DISABLE_SPLASH_DISPLAY                     0x31U            /* 49, 1, command to disable splash screen at power on              */
  #define SAVE_CURRENT_DISPLAY_AS_SPLASH             0x0AU            /* 10, Ctrl+j, command to save current text on display as splash    */

  /* Special commands */
  #define LCD_RETURNHOME                    (uint8_t)0x02U
  #define LCD_ENTRYMODESET                  (uint8_t)0x04U
  #define LCD_DISPLAYCONTROL                (uint8_t)0x08U
  #define LCD_CURSORSHIFT                   (uint8_t)0x10U
  #define LCD_SETDDRAMADDR                  (uint8_t)0x80U

  /* Flags for display entry mode */
  #define LCD_ENTRYRIGHT                    (uint8_t)0x00U
  #define LCD_ENTRYLEFT                     (uint8_t)0x02U
  #define LCD_ENTRYSHIFTINCREMENT           (uint8_t)0x01U
  #define LCD_ENTRYSHIFTDECREMENT           (uint8_t)0x00U

  /* Flags for display on/off control */
  #define LCD_DISPLAYON                              0x04U
  #define LCD_DISPLAYOFF                             0x00U
  #define LCD_CURSORON                               0x02U
  #define LCD_CURSOROFF                              0x00U
  #define LCD_BLINKON                                0x01U
  #define LCD_BLINKOFF                               0x00U

  /* Flags for display/cursor shift */
  #define LCD_DISPLAYMOVE                            0x08U
  #define LCD_CURSORMOVE                             0x00U
  #define LCD_MOVERIGHT                              0x04U
  #define LCD_MOVELEFT                               0x00U

  /* Errors */
  #define LCD_OK                                        0U              /* No error, everything's fine             */
  #define LCD_ERROR                                     1U              /* Display error during transmission (i2c) */

  /* ----------------------------------------------------------------------------------- */
  /*  Initial display functions                                                          */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_Init(void);

  /* ----------------------------------------------------------------------------------- */
  /*  Move on the display                                                                */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_Home                 (void);
  uint8_t CddSerLcd_MoveCursorLeft       (void);
  uint8_t CddSerLcd_MoveCursorRight      (void);
  uint8_t CddSerLcd_ScrollDisplayLeft    (void);
  uint8_t CddSerLcd_ScrollDisplayRight   (void);
  uint8_t CddSerLcd_Autoscroll           (void);
  uint8_t CddSerLcd_NoAutoscroll         (void);
  uint8_t CddSerLcd_SetCursor            (uint8_t col, uint8_t row);

  /* ----------------------------------------------------------------------------------- */
  /* Write on the display                                                                */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_Clear                (void);
  uint8_t CddSerLcd_Write                (uint8_t b);
  uint8_t CddSerLcd_WriteString          (char *buffer);
  uint8_t CddSerLcd_WriteChar            (uint8_t location);
  uint8_t CddSerLcd_CreateChar           (uint8_t location, uint8_t *charmap);

  /* ----------------------------------------------------------------------------------- */
  /* Display align                                                                       */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_LeftToRight          (void);
  uint8_t CddSerLcd_RightToLeft          (void);

  /* ----------------------------------------------------------------------------------- */
  /* Show and hide items                                                                 */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_NoDisplay            (void);
  uint8_t CddSerLcd_Display              (void);
  uint8_t CddSerLcd_NoCursor             (void);
  uint8_t CddSerLcd_Cursor               (void);
  uint8_t CddSerLcd_NoBlink              (void);
  uint8_t CddSerLcd_Blink                (void);
  uint8_t CddSerLcd_EnableSystemMessages (void);
  uint8_t CddSerLcd_DisableSystemMessages(void);

  /* ----------------------------------------------------------------------------------- */
  /* Display properties                                                                  */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_SetContrast          (uint8_t new_val);
  uint8_t CddSerLcd_SetAddress           (uint8_t new_addr);
  uint8_t CddSerLcd_SetFastBacklight     (uint8_t r, uint8_t g, uint8_t b);
  uint8_t CddSerLcd_SetBacklight         (uint16_t r, uint16_t g, uint16_t b);

  /* ----------------------------------------------------------------------------------- */
  /* Edit splash screen                                                              */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_EnableSplash         (void);
  uint8_t CddSerLcd_DisableSplash        (void);
  uint8_t CddSerLcd_SaveSplash           (void);


  /* ----------------------------------------------------------------------------------- */
  /*  Only for internal use                                                              */
  /* ----------------------------------------------------------------------------------- */
  uint8_t CddSerLcd_Command              (uint8_t command);
  uint8_t CddSerLcd_SpecialCommand       (uint8_t command);


#endif /* CDD_SER_LCD_I2C */
