#include <stddef.h>
#include <stdint.h>

#include <OS/OS.h>
#include <OS/OS_Cfg.h>
#include <Util/UtilTimer.h>

typedef struct TCB
{
  void(*pInit)(void);
  void(*pFunc)(void);
  Gpt_ValueType CallTimeNext;
  const unsigned CallCycle;
}
TCB;

static TCB TaskList[] = OS_CFG_TASK_LIST_INIT;

void OS_Start(void)
{
  for(size_t   i = (size_t) UINT8_C(0);
               i < (size_t) (sizeof(TaskList) / sizeof(TaskList[(size_t) UINT8_C(0)]));
             ++i)
  {
    if(TimerTimeout(TaskList[i].CallTimeNext))
    {
      TaskList[i].pInit();
    }
  }

  for(;;)
  {
    for(size_t   i = (size_t) UINT8_C(0);
                 i < (size_t) (sizeof(TaskList) / sizeof(TaskList[(size_t) UINT8_C(0)]));
               ++i)
    {
      if(TimerTimeout(TaskList[i].CallTimeNext))
      {
        TaskList[i].CallTimeNext = TimerStart(TaskList[i].CallCycle);

        TaskList[i].pFunc();

        // Implement an (optional) priority mechanism.
        break;
      }
    }
  }
}
