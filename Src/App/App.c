#include "cpu.h"

// Base address for GPIOA
#define GPIOA_BASE          0x40020000UL

// GPIOA registers
#define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14UL))


int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  while (1)
  {
    // Toggle the LED pin
    GPIOA_ODR ^= (1 << 5);

    // Simple delay
    for (volatile uint32_t i = 0; i < (uint32_t)0x005FFFFFUL; ++i)
    {
    }
  }

  return 0;
}
