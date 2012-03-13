#include "cmd_task.h"

#include "../libafanasy/msgclasses/mctaskpos.h"

#define AFOUTPUT
#undef AFOUTPUT
#include "../include/macrooutput.h"

CmdTaskOutput::CmdTaskOutput()
{
   setCmd("tout");
   setArgsCount(4);
   setInfo("Get task output.");
   setHelp("tout [jobid] [block] [task] [start] Get task output.");
   setMsgType( af::Msg::TTaskOutputRequest);
   setRecieving();
}
CmdTaskOutput::~CmdTaskOutput(){}
bool CmdTaskOutput::processArguments( int argc, char** argv, af::Msg &msg)
{
   bool ok; int job; int block; int task; int number;
   job    = (QString::fromUtf8(argv[0])).toInt( &ok);
   if( ok == false ) return false;
   block  = (QString::fromUtf8(argv[1])).toInt( &ok);
   if( ok == false ) return false;
   task   = (QString::fromUtf8(argv[2])).toInt( &ok);
   if( ok == false ) return false;
   number = (QString::fromUtf8(argv[3])).toInt( &ok);
   if( ok == false ) return false;
   af::MCTaskPos mctaskpos( job, block, task, number);
   msg.set( getMsgType(), &mctaskpos);
   return true;
}
