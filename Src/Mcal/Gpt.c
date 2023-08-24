#include <Mcal/Gpt.h>

static Gpt_ValueType my_millisec_counter;

Gpt_ValueType Gpt_GetTimeElapsed(const Gpt_ChannelType DummyChannelIndex)
{
  (void) DummyChannelIndex;

  return my_millisec_counter;
}

void SysTick_Handler(void);

void SysTick_Handler(void)
{
  ++my_millisec_counter;
}
