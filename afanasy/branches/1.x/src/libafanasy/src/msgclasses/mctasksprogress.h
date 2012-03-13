#ifndef AF_MCTASKSPROGRESS_H
#define AF_MCTASKSPROGRESS_H

#include "msgclass.h"
#include <taskprogress.h>

namespace af
{

class MCTasksProgress : public MsgClass
{
public:
   MCTasksProgress( int JobId);
   MCTasksProgress( Msg * msg);
   ~MCTasksProgress();

   void stdOut( bool full = false ) const;

   void add( int block, int task, TaskProgress * tp);

   inline int getJobId() const { return jobid;      }
   inline int getCount() const { return tasks.size();}

   inline const std::list<int32_t> * getBlocks() const { return &blocks; }
   inline const std::list<int32_t> * getTasks()  const { return &tasks;  }
   inline std::list<TaskProgress*> * getTasksRun() { return &tasksprogress; }

private:
   bool clientside;
   int32_t jobid;

   std::list<int32_t> blocks;
   std::list<int32_t> tasks;

   std::list<TaskProgress*> tasksprogress;

private:
   void readwrite( Msg * msg);
};
}
#endif
