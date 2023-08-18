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
#define PWR_CR              (*(volatile uint32_t*)(PWR_BASE + 0x00))

// FLASH registers
#define FLASH_ACR           (*(volatile uint32_t*)(FLASH_BASE + 0x00))


// GPIOA registers
#define GPIOA_MODER         (*(volatile uint32_t*)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR           (*(volatile uint32_t*)(GPIOA_BASE + 0x14UL))


#define RCC_APB1ENR_PWREN    ((uint32_t)0x10000000UL)
#define RCC_CR_HSEON         ((uint32_t)0x00010000UL)
#define RCC_CR_HSERDY        ((uint32_t)0x00020000UL)

// Time out for HSE start up
#define HSE_STARTUP_TIMEOUT  ((uint16_t)0x0500)

//  Regulator voltage scaling output selection
#define RCC_PLLCFGR_PLLSRC_HSE              ((uint32_t)0x00400000)

#define PLL_M      8
#define PLL_N      288
#define PLL_P      2
#define PLL_Q      6

void SystemInit(void);
void SetSysClock(void);

int main(void)
{

  // Configure the System clock source, PLL Multiplier and Divider factors,
  // AHB/APBx prescalers and Flash settings
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
    for (volatile uint32_t i = 0; i < (uint32_t)0x000FFFFFUL; ++i)
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
  uint32_t StartUpCounter = 0U;
  uint32_t HSEStatus      = 0U;

  // Enable HSE
  RCC_CR |= ((uint32_t)(1UL << 16));

  // Wait till HSE is ready and if Time out is reached exit

  while((HSEStatus == 0U) && (StartUpCounter != HSE_STARTUP_TIMEOUT))
  {
    // check HSE clock ready flag
    HSEStatus = RCC_CR & (1UL << 17);

    StartUpCounter++;
  }

  if ((RCC_CR & (1UL << 17)) != 0U)
  {
    HSEStatus = (uint32_t)0x01U;
  }
  else
  {
    HSEStatus = (uint32_t)0x00U;
  }

  if (HSEStatus == (uint32_t)0x01U)
  {
    // Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz
    RCC_APB1ENR |= (uint32_t)(1UL << 28);

    // Regulator voltage scaling output selection VOS
    PWR_CR      |= (1UL << 14);  // Scale 3 mode

    // HCLK = SYSCLK / 1
    RCC_CFGR |= (uint32_t)0x00000000UL; // system clock not divided

    // APB high-speed prescalerr (APB2)
    // AHB clock divided by 2
    RCC_CFGR |= (uint32_t)(1UL << 15);

    // APB Low speed prescaler (APB1)
    // AHB clock divided by 4
    RCC_CFGR |= (uint32_t)( (1UL << 10) | (1UL << 12));

    // Configure the main PLL
    RCC_PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    // Enable the main PLL
    RCC_CR |= (uint32_t)(1UL << 24);

    // Wait till the main PLL is ready
    while((RCC_CR & (uint32_t)(1UL << 25)) == 0)
    {
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
  else
  {
    // If HSE fails to start-up, the application will have wrong clock configuration.
    // TBD handle this case
  }
}
