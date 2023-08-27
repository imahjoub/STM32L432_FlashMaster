#ifndef UTIL_TIMER_2023_08_24_H
  #define UTIL_TIMER_2023_08_24_H

  #include <stdbool.h>
  #include <stdint.h>

  #include <Mcal/Gpt.h>


  static inline Gpt_ValueType TimerStart(const unsigned NextTimeoutMillisec)
  {
    return (Gpt_ValueType) (Gpt_GetTimeElapsed((Gpt_ChannelType) UINT8_C(0)) + NextTimeoutMillisec);
  }

  static inline bool TimerTimeout(const Gpt_ValueType MyTimer)
  {
    return (bool) ((Gpt_GetTimeElapsed((Gpt_ChannelType) UINT8_C(0)) > MyTimer) ? true : false);
  }

#endif /* UTIL_TIMER_2023_08_24_H */
