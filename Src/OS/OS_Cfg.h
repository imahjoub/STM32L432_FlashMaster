#ifndef OS_CFG_2023_08_23_H
  #define OS_CFG_2023_08_23_H

  #include <OS/OS.h>

  extern void Task01_Init(void);
  extern void Task02_Init(void);
  extern void Task03_Init(void);

  extern void Task01_Func(void);
  extern void Task02_Func(void);
  extern void Task03_Func(void);

  TCB TaskList[3U] =
  {
    { Task01_Init, Task01_Func, 0U,  17U },
    { Task02_Init, Task02_Func, 0U, 229U },
    { Task03_Init, Task03_Func, 0U, 514U }
  };

#endif /* OS_CFG_2023_08_23_H */
