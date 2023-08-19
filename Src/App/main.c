#include <stdint.h>

// Base addresses for peripheral registers
#define SCB_BASE            0xE000ED00UL
#define RCC_BASE            0x40023800UL
#define GPIOA_BASE          0x40020000UL
#define PWR_BASE            0x40007000UL
#define FLASH_BASE          0x40023C00UL

// SCB registers
#define SCB_CPACR           (*(volatile uint32_t*)(SCB_BASE + 0x88UL))

// RCC Registers
#define RCC_CR              (*(volatile uint32_t*)(RCC_BASE + 0x00UL))
#define RCC_PLLCFGR         (*(volatile uint32_t*)(RCC_BASE + 0x04UL))
#define RCC_CFGR            (*(volatile uint32_t*)(RCC_BASE + 0x08UL))
#define RCC_AHB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x30UL))
#define RCC_CIR             (*(volatile uint32_t*)(RCC_BASE + 0x0CUL))
#define RCC_APB1ENR         (*(volatile uint32_t*)(RCC_BASE + 0x40UL))

// PWR registers
#define PWR_CR              (*(volatile uint32_t*)(PWR_BASE + 0x00UL))

// FLASH registers
#define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x00UL))


// GPIOA registers
#define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14UL))


void SystemInit(void);
void SetSysClock(void);

int main(void)
{

  // Configure the System clock source
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

void SystemInit(void)
{
  // set coprocessor access control register CP10 and CP11 Full Access
  SCB_CPACR |= (uint32_t)((3UL << 20) | (3UL << 22));

  // Set HSION (internal high-speed clock) enable bit
  RCC_CR |= (uint32_t)(1UL << 0);

  // Reset HSEON, CSSON, HSEBYP and PLLON bits
  RCC_CR &= (uint32_t)((~(1UL << 16)) | (~(1UL << 18))) | (~(1UL << 19)) | (~(1UL << 24));

  // Reset CFGR register
  RCC_CFGR = (uint32_t)0x00000000UL;

  // Reset PLLCFGR register
  RCC_PLLCFGR = (uint32_t)0x24003010UL;

  // Disable all interrupts
  RCC_CIR = (uint32_t)0x00000000UL;
}


void SetSysClock(void)
{
  // Enable HSE
  RCC_CR |= ((uint32_t)(1UL << 16));

  // Wait till HSE is ready
  while(!(RCC_CR & ((uint32_t)1UL << 17)))
  {
    __asm volatile("nop");
  }

  // PWREN: Power interface clock enable
  RCC_APB1ENR |= (uint32_t)(1UL << 28);

  // Set HCLK  = sysclk / 1
  // Set PCLK2 = hclk   / 2
  // Set PCLK1 = hclk   / 4
  RCC_CFGR |= (uint32_t)((5UL << 10) | (1UL << 15));

  // Configure the main PLL
  // PLL_M = 8
  // PLL_N = 360
  // PLL_P = 0 -> 2
  // PLL_Q = 7
  // SYSCLK = 180 MHz
  RCC_PLLCFGR = (uint32_t)(8UL << 0) | (360UL << 6) | (0UL << 16) | (1UL << 22) | (7UL << 24);

  // Enable the main PLL
  RCC_CR |= (uint32_t)(1UL << 24);

  // Wait till the main PLL is ready
  while(!(RCC_CR & (uint32_t)1UL << 25))
  {
    __asm volatile("nop");
  }

  // Configure Flash prefetch, Instruction cache, Data cache and wait state
  // Instruction cache enable
  // Data cache enable
  // Latency : 5 wait states (e ratio of the CPU clock period to the Flash memory access time)
  FLASH_ACR = (uint32_t)((1UL << 9) | (1UL << 10) | (5UL << 0));

  // Select the main PLL as system clock source
  RCC_CFGR &= (uint32_t)(~(3UL << 0));
  RCC_CFGR |= (uint32_t)(2UL << 0);

  // Wait till the main PLL is used as system clock source
  while ((RCC_CFGR & (uint32_t)(0x0CU << 0)) != (8UL << 0))
  {
  }
}
