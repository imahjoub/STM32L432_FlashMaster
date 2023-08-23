#include <Mcal/Gpt.h>
#include <Mcal/Mcu.h>
#include <OS/Os.h>

#include <Cdd/CddExtFlash/CddExtFlash.h>



extern bool AppShape_CheckCircle(void);

void Task01_Init(void);
void Task02_Init(void);
void Task03_Init(void);

void Task01_Func(void);
void Task02_Func(void);
void Task03_Func(void);

void Task01_Init(void) { }
void Task02_Init(void) { }
void Task03_Init(void) { }

void Task01_Func(void)
{
  static uint64_t my_timer = 1U;

  if(TimerTimeout(my_timer))
  {
    my_timer = TimerStart(1000U);

    // Toggle the LED pin
    GPIOA_ODR ^= (uint32_t) (1UL << 5U);
  }
}

void Task02_Func(void) { }
void Task03_Func(void) { }

#if 1

int main(void)
{
  // Initialize the ports.

  // Enable the clock for GPIOA
  RCC_AHB1ENR |= (1 << 0);

  // Configure GPIOA Pin 5 as output
  GPIOA_MODER |= (1 << 10);  // Set pin 5 to output mode

  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer.
  SysTick_Init();

  (void) AppShape_CheckCircle();

  OS_Start();

  return 0;
}
#endif

#if 0
#include <Mcal/Mcu.h>
#include <Cdd/CddExtFlash/CddExtFlash.h>


int main(void)
{
  // Configure the System clock and flash
  SystemInit();
  SetSysClock();

  // Configure systick timer to generate half second delay
  SysTick_Init();

  SpiInit();

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

#endif
