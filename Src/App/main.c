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
#define PWR_CR_VOS                          ((uint16_t)0x4000)
#define RCC_CFGR_HPRE_DIV1                  ((uint32_t)0x00000000)
#define RCC_CFGR_PPRE2_DIV2                 ((uint32_t)0x00008000)
#define RCC_CFGR_PPRE1_DIV4                 ((uint32_t)0x00001400)
#define RCC_PLLCFGR_PLLSRC_HSE              ((uint32_t)0x00400000)
#define RCC_CR_PLLON                        ((uint32_t)0x01000000)
#define RCC_CR_PLLRDY                       ((uint32_t)0x02000000)
#define FLASH_ACR_ICEN                      ((uint32_t)0x00000200)
#define FLASH_ACR_DCEN                      ((uint32_t)0x00000400)
#define FLASH_ACR_DCEN                      ((uint32_t)0x00000400)
#define FLASH_ACR_LATENCY_5WS               ((uint32_t)0x00000005)
#define RCC_CFGR_SW_PLL                     ((uint32_t)0x00000002)
#define RCC_CFGR_SW                         ((uint32_t)0x00000003)
#define RCC_CFGR_SWS                        ((uint32_t)0x0000000C)
#define RCC_CFGR_SWS_PLL                    ((uint32_t)0x00000008)

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
    for (volatile int i = 0; i < 100000; ++i)
    {
    }
  }

  return 0;
}

void SystemInit(void)
{
  // set CP10 and CP11 Full Access
  SCB_CPACR |= ((3UL << 20)|(3UL << 22));

  // Set HSION bit
  RCC_CR |= (uint32_t)0x00000001;

  // Reset CFGR register
  RCC_CFGR = 0x00000000UL;

  // Reset HSEON, CSSON and PLLON bits
  RCC_CR &= (uint32_t)0xFEF6FFFFUL;

  // Reset PLLCFGR register
  RCC_PLLCFGR = 0x24003010UL;

  // Reset HSEBYP bit
  RCC_CR &= (uint32_t)0xFFFBFFFFUL;

  // Disable all interrupts
  RCC_CIR = 0x00000000UL;
}

void SetSysClock(void)
{
  uint32_t StartUpCounter = 0U;
  uint32_t HSEStatus      = 0U;

  // Enable HSE
  RCC_CR |= ((uint32_t)RCC_CR_HSEON);

  // Wait till HSE is ready and if Time out is reached exit
  do
  {
    HSEStatus = RCC_CR & RCC_CR_HSERDY;

    StartUpCounter++;
  }
  while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC_CR & RCC_CR_HSERDY) != 0U)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
    // Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz
    RCC_APB1ENR |= RCC_APB1ENR_PWREN;
    PWR_CR |= PWR_CR_VOS;

    // HCLK = SYSCLK / 1
    RCC_CFGR |= RCC_CFGR_HPRE_DIV1;

    // PCLK2 = HCLK / 2
    RCC_CFGR |= RCC_CFGR_PPRE2_DIV2;

    // PCLK1 = HCLK / 4
    RCC_CFGR |= RCC_CFGR_PPRE1_DIV4;

    // Configure the main PLL
    RCC_PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

    // Enable the main PLL
    RCC_CR |= RCC_CR_PLLON;

    // Wait till the main PLL is ready
    while((RCC_CR & RCC_CR_PLLRDY) == 0)
    {
    }

    // Configure Flash prefetch, Instruction cache, Data cache and wait state
    FLASH_ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

    // Select the main PLL as system clock source
    RCC_CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC_CFGR |= RCC_CFGR_SW_PLL;

    // Wait till the main PLL is used as system clock source
    while ((RCC_CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
    {
    }
  }
  else
  {
     // If HSE fails to start-up, the application will have wrong clock configuration.
     // TBD handle this case
  }

}


