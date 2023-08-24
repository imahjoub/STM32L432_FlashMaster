#ifndef OS_CFG_2023_08_23_H
  #define OS_CFG_2023_08_23_H

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  extern void Task01_Init(void);
  extern void Task02_Init(void);
  extern void Task03_Init(void);

  extern void Task01_Func(void);
  extern void Task02_Func(void);
  extern void Task03_Func(void);

  #define OS_CFG_TASK_LIST_ENTRY(init, func, t0, cycle) { (init), (func), (t0), (cycle) }

  #define OS_CFG_TASK_LIST_INIT \
  { \
    OS_CFG_TASK_LIST_ENTRY(Task01_Init, Task01_Func, 0U,  97U), \
    OS_CFG_TASK_LIST_ENTRY(Task02_Init, Task02_Func, 0U, 229U), \
    OS_CFG_TASK_LIST_ENTRY(Task03_Init, Task03_Func, 0U, 514U)  \
  }

  #if defined(__cplusplus)
  }
  #endif

#endif /* OS_CFG_2023_08_23_H */
