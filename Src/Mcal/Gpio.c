#include "Mcal/Gpio.h"

void GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position = 0x00U;
  uint32_t iocurrent;

  /* Configure the port pins */
  while (((GPIO_Init->Pin) >> position) != 0x00U)
  {
    /* Get current io position */
    iocurrent = (GPIO_Init->Pin) & (1UL << position);
    uint32_t bit_offset_1 = position * 2U;

    if (iocurrent != 0x00U)
    {
      /*--------------------- GPIO Mode Configuration ------------------------*/
      /* In case of Output or Alternate function mode selection */
      if (((GPIO_Init->Mode & GPIO_MODE) == MODE_OUTPUT) || ((GPIO_Init->Mode & GPIO_MODE) == MODE_AF))
      {
        /* Configure the IO Speed */
        GPIOx->OSPEEDR = (GPIOx->OSPEEDR & ~(GPIO_OSPEEDR_OSPEED0 << bit_offset_1)) | (GPIO_Init->Speed << bit_offset_1);


        /* Configure the IO Output Type */
        GPIOx->OTYPER = (GPIOx->OTYPER & ~(GPIO_OTYPER_OT0 << position)) | ((((GPIO_Init->Mode & OUTPUT_TYPE) >> OUTPUT_TYPE_Pos) << position));
      }

      /* In case of Alternate function mode selection */
      if ((GPIO_Init->Mode & GPIO_MODE) == MODE_AF)
      {
        /* Configure Alternate function mapped with the current IO */
        uint32_t bit_offset_2 = ((position & 0x07U) * 4U);
        GPIOx->AFR[position >> 3U] = (GPIOx->AFR[position >> 3U] & ~(0xFu << bit_offset_2)) | (GPIO_Init->Alternate << bit_offset_2);
      }

      /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
      GPIOx->MODER = (GPIOx->MODER & ~(GPIO_MODER_MODE0 << bit_offset_1)) | (((GPIO_Init->Mode & GPIO_MODE) << bit_offset_1));
    }
    position++;
  }
}






