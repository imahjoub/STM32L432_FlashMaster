#include <Mcal/Gpt.h>
#include <Mcal/Reg.h>
#include <Mcal/SysTick.h>

void SysTick_Init(void)
{
  /* Reset the SysTick control register */
  STK_CTRL = (uint32_t)0x00000000UL;

  /* Set the SysTick reload register to be equivalent to 1ms */
  STK_LOAD = (uint32_t)(79999UL); /* we operate with 80Mhz */

  /* Initialize the SysTick counter value (clear it to zero) */
  STK_VAL = (uint32_t)0x00000000UL;

  /* Set the SysTicl clock source to be the main processor clock */
  STK_CTRL = (uint32_t)0x00000004UL;

  /* Enable the SysTick interrupt */
  STK_CTRL |= (uint32_t)(2UL);

  /* Enable the SysTick counter */
  STK_CTRL |= (uint32_t)(1UL << 0);
}
