#ifndef GPIO_H
  #define GPIO_H

  #include "stdint.h"
  #include "stddef.h"

  #define GPIO_MODE_Pos                           0u
  #define GPIO_MODE                               (0x3uL << GPIO_MODE_Pos)
  #define MODE_OUTPUT                             (0x1uL << GPIO_MODE_Pos)
  #define MODE_AF                                 (0x2uL << GPIO_MODE_Pos)
  #define GPIO_PIN_4                              ((uint16_t)0x0010)  /* Pin 4 selected    */
  #define GPIO_PIN_5                              ((uint16_t)0x0020)  /* Pin 5 selected    */
  #define GPIO_PIN_6                              ((uint16_t)0x0040)  /* Pin 6 selected    */
  #define GPIO_PIN_7                              ((uint16_t)0x0080)  /* Pin 7 selected    */

  #define GPIO_OSPEEDR_OSPEED0_Pos                (0U)
  #define GPIO_OSPEEDR_OSPEED0_Msk                (0x3UL << GPIO_OSPEEDR_OSPEED0_Pos)     /*!< 0x00000003 */
  #define GPIO_OSPEEDR_OSPEED0                    GPIO_OSPEEDR_OSPEED0_Msk

  #define OUTPUT_TYPE_Pos                         4u
  #define OUTPUT_TYPE                             (0x1uL << OUTPUT_TYPE_Pos)
  #define OUTPUT_PP                               (0x0uL << OUTPUT_TYPE_Pos)
  #define OUTPUT_OD                               (0x1uL << OUTPUT_TYPE_Pos)

  #define GPIO_MODER_MODE0_Pos                     (0U)
  #define GPIO_MODER_MODE0_Msk                     (0x3UL << GPIO_MODER_MODE0_Pos)         /*!< 0x00000003 */
  #define GPIO_MODER_MODE0                         GPIO_MODER_MODE0_Msk

  #define GPIO_SPEED_FREQ_LOW                       0x00000000u  /*!< Low speed       */

  #define GPIO_NOPULL                               0x00000000u                 /* No Pull-up or Pull-down activation  */
  #define GPIO_PULLUP                               0x00000001u                 /* Pull-up activation                  */
  #define GPIO_PULLDOWN                             0x00000002u                 /* Pull-down activation                */
  #define GPIO_MODE_OUTPUT_PP                       (MODE_OUTPUT | OUTPUT_PP)   /*!< Output Push Pull Mode  */
  #define GPIO_MODE_AF_PP                           (MODE_AF | OUTPUT_PP)       /*!< Alternate Function Push Pull Mode */
  #define GPIO_SPEED_FREQ_VERY_HIGH                 0x00000003u                 /*!< Very high speed */

  #define GPIO_AF5_SPI1                              ((uint8_t)0x05)            /* SPI1 Alternate Function mapping   */

  #define GPIO_AF4_I2C1                             ((uint8_t)0x04)             /* I2C1 Alternate Function mapping   */

 #define GPIO_MODE_AF_OD                            (MODE_AF | OUTPUT_OD)       /*!< Alternate Function Open Drain Mode */

#define GPIO_OTYPER_OT0_Pos            (0U)
#define GPIO_OTYPER_OT0_Msk            (0x1UL << GPIO_OTYPER_OT0_Pos)          /*!< 0x00000001 */
#define GPIO_OTYPER_OT0                GPIO_OTYPER_OT0_Msk


  typedef struct
{
  volatile uint32_t MODER;       /*!< GPIO port mode register,               Address offset: 0x00      */
  volatile uint32_t OTYPER;      /*!< GPIO port output type register,        Address offset: 0x04      */
  volatile uint32_t OSPEEDR;     /*!< GPIO port output speed register,       Address offset: 0x08      */
  volatile uint32_t PUPDR;       /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  volatile uint32_t IDR;         /*!< GPIO port input data register,         Address offset: 0x10      */
  volatile uint32_t ODR;         /*!< GPIO port output data register,        Address offset: 0x14      */
  volatile uint32_t BSRR;        /*!< GPIO port bit set/reset  register,     Address offset: 0x18      */
  volatile uint32_t LCKR;        /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  volatile uint32_t AFR[2];      /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
  volatile uint32_t BRR;         /*!< GPIO Bit Reset register,               Address offset: 0x28      */

} GPIO_TypeDef;

typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                           This parameter can be any value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                           This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                           This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
} GPIO_InitTypeDef;


  void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);


#endif /* GPIO_H */
