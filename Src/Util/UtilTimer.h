#ifndef UTIL_TIMER_2023_08_24_H
  #define UTIL_TIMER_2023_08_24_H

  #include <stdbool.h>
  #include <stdint.h>

  #include <Mcal/Gpt.h>

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  static inline Gpt_ValueType TimerStart(const unsigned NextTimeoutMillisec)
  {
    return (Gpt_ValueType) (Gpt_GetTimeElapsed((Gpt_ChannelType) UINT8_C(0)) + NextTimeoutMillisec);
  }

  static inline bool TimerTimeout(const Gpt_ValueType MyTimer)
  {
    return (bool) ((Gpt_GetTimeElapsed((Gpt_ChannelType) UINT8_C(0)) > MyTimer) ? true : false);
  }

  #if defined(__cplusplus)
  }
  #endif

  #if defined(__cplusplus)
  namespace util {
  inline auto TimerStart(const unsigned NextTimeoutMillisec) noexcept -> ::Gpt_ValueType { return ::TimerStart(NextTimeoutMillisec); }

  inline auto TimerTimeout(const ::Gpt_ValueType MyTimer) noexcept -> bool { return ::TimerTimeout(MyTimer); }
  } // namespace util
  #endif

#endif /* UTIL_TIMER_2023_08_24_H */
