#ifndef OS_2023_08_23_H
  #define OS_2023_08_23_H

  #include <stdint.h>


  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  typedef uint64_t OsTimerType;

  typedef struct TCB
  {
    void(*pInit)(void);
    void(*pFunc)(void);
    OsTimerType CallTimeNext;
    const unsigned CallCycle;
  }
  TCB;

  void OS_Start(void);

  #if defined(__cplusplus)
  }
  #endif

#endif /* OS_2023_08_23_H */
