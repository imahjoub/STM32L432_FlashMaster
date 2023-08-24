#include <Mcal/Gpt.h>

static volatile Gpt_ValueType my_millisec_counter;

Gpt_ValueType Gpt_GetTimeElapsed(const Gpt_ChannelType DummyChannelIndex)
{
  (void) DummyChannelIndex;

  volatile Gpt_ValueType Counter01;
  volatile Gpt_ValueType Counter02;

  uint32_t LowPart01;
  uint32_t LowPart02;

  do
  {
    // Here we need a consistency check for reading the
    // 64-bit counter value on a 32-bit architecture.

    // Note: This is because the 64-bit counter is incremented
    // in interrupt level of SysTick.

    Counter01 = my_millisec_counter;
    Counter02 = my_millisec_counter;

    LowPart01 = (uint32_t) Counter01;
    LowPart02 = (uint32_t) Counter02;
  }
  while(LowPart01 > LowPart02);

  return Counter02;
}

void SysTick_Handler(void);

void SysTick_Handler(void)
{
  ++my_millisec_counter;
}
