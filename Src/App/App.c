#include <Mcal/Mcu.h>
#include <Cdd/CddExtFlash/CddExtFlash.h>

int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer to generate half second delay
  SysTick_Init();

  spi_init();

  while(1U)
  {
    // Enable chip select
    spi_cs_select();

    // Send the command to read the chip ID
    uint8_t command = 0x9FU;
    spi_write(&command, 1U);

    // Send the command for chip ID read
    // Read the response (chip ID) from the flash memory
    uint32_t chipID = 0;
    spi_read((uint8_t *)&chipID, 3U);

    // Disable chip select
    spi_cs_deselect();
  }
}

#if 0
#include <Mcal/Mcu.h>

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

  // Configure systick timer to generate half second delay
  SysTick_Init();

  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  while(1)
  {
    if(STK_CTRL & (uint32_t)( 1UL << 16))
    {
      // Toggle the LED pin
      GPIOA_ODR ^= (1 << 5);
    }
  }

  return 0;
}
#endif
