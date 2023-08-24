#include <Mcal/Gpt.h>
#include <OS/OS.h>
#include <OS/OS_Cfg.h>

void OS_Start(void)
{
  for(unsigned i = 0U; i < sizeof(TaskList) / sizeof(TaskList[0U]); ++i)
  {
    if(TimerTimeout(TaskList[i].CallTimeNext))
    {
      TaskList[i].pInit();
    }
  }

  for(;;)
  {
    for(unsigned i = 0U; i < sizeof(TaskList) / sizeof(TaskList[0U]); ++i)
    {
      if(TimerTimeout(TaskList[i].CallTimeNext))
      {
        TaskList[i].CallTimeNext = TimerStart(TaskList[i].CallCycle);

        TaskList[i].pFunc();

        // (Optional) priority mechanism
        break;
      }
    }
  }
}
