#include <Mcal/Mcu.h>
#include <Mcal/Reg.h>


void SystemInit(void)
{
  /* Set coprocessor access control register CP10 and CP11 Full Access (Enable floating point unit) */
  SCB_CPACR |= (uint32_t)((uint32_t)(3UL << 20U) | (uint32_t)(3UL << 22U));

  /* Reset HSEON, CSSON, HSEBYP and PLLON bits */
  RCC_CR &= (uint32_t)((~(1UL << 16)) | (~(1UL << 18))) | (~(1UL << 19)) | (~(1UL << 24));

  /* Reset CFGR register */
  RCC_CFGR = (uint32_t)0x40000000UL;

  /* Reset PLLCFGR register */
  RCC_PLLCFGR = (uint32_t)0x00001000UL;

  /* Disable all interrupts */
  RCC_CIER = (uint32_t)0x00000000UL;

  /* Configure Flash prefetch, Instruction cache, Data cache and wait state (3 wait states) */
  FLASH_ACR = (uint32_t)((1UL << 9) | (1UL << 10) | (3UL << 0));
}

void SetSysClock(void)
{
  /* Set HSION (HSI16 clock enable) enable bit */
  RCC_CR |= (uint32_t)(1UL << 8U);

  /* wait until HSI16 clock is ready */
  while (!(RCC_CR & (uint32_t)(1UL << 10UL)))
  {
    __asm volatile("nop");
  }

  /* PWREN: Power interface clock enable */
  RCC_APB1ENR1 |= (uint32_t)(1UL << 28);

  /* Enable main PLL */
  RCC_CR &= (uint32_t)(~(uint32_t)(1UL << 24));

  /* Wait until main PLL is enabled */
  while (RCC_CR & (uint32_t)(1UL << 25))
  {
    __asm volatile("nop");
  }

  /*  PLL configuration for 80MHz system clock from 16MHz HSI   */
  /*  f(VCO clock) = 16MHz * (40 / 4) = 160MHz                  */
  /*  f(System Clock) = f(VCO clock) / PLLR = 80MHz             */

  RCC_PLLCFGR = (uint32_t)((2UL << 0U)    /* Set PLL source to HSI */
                         | (3UL << 4U)    /* Set PLLM to 4         */
                         | (40UL << 8U)   /* Set PLLN to 40        */
                         | (0UL << 25U)); /* Set PLLR to 2         */

  /* Enable Main PLLCLK output for the system clock */
  RCC_PLLCFGR |= (uint32_t)(1UL << 24);

  /* Enable main PLL */
  RCC_CR |= (uint32_t)(1UL << 24);

  /* Wait until main PLL is enabled */
  while (!(RCC_CR & (uint32_t)(1UL << 25)))
  {
    __asm volatile("nop");
  }

  /* Select PLL as system clock source */
  RCC_CFGR &= (uint32_t)(~(3UL << 0));
  RCC_CFGR |= (uint32_t)(3UL << 0U);

  /* Wait till the main PLL is used as system clock source */
  while ((RCC_CFGR & (uint32_t)(0x0CU << 0)) != (0x0CU << 0))
  {
    __asm volatile("nop");
  }
}
