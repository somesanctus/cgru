#pragma once

#include "aftypes.h"

/// Job.
namespace AFJOB
{
   const int MAXQUANTITY = 1000000;

   const char     TASKS_OUTPUTDIR[]     = "tasksoutput"; ///< Tasks output directory, relative to AFSERVER::TEMP_DIRECTORY
   const char     LOGS_DIRECTORY[]      = "jobs";        ///< Jobs logs store directory, relative to AFSERVER::TEMP_DIRECTORY
   const int      LOGS_LINESMAX         = 100;        ///< Maximum number of lines in each Job log.
   const int      LOGS_ROTATE           = 10;         ///< Number of logs to keep.

   const uint8_t  PROGRESS_BYTES  = 8;

   const char DEFAULT_NAME[]  = "job";
   const char BLOCK_DEFAULT_NAME[]        = "block";
   const char BLOCK_DEFAULT_SERVICE[]     = "generic";
   const char BLOCK_DEFAULT_PARSER[]      = "none";
   const char TASK_DEFAULT_NAME[]         = "task";

   const int TASK_DEFAULT_CAPACITY = 1000;
   const int TASK_UPDATE_TIMEOUT   = 300;  ///< Seconds for task to have no update to produce error.
   const int TASK_STOP_TIMEOUT     = 5;    ///< Time after running task was asked to stop, it become not running itself.

   const int TASK_MULTIHOSTMAXHOSTS = 100;

// When job sends it's data to server to register.
   const int NET_CONNECTTIME = 10000;
   const int NET_SENTTIME = 10000;


   const uint32_t STATE_READY_MASK        = 1<<0;
   const   char   STATE_READY_NAME[]      = "Ready";
   const   char   STATE_READY_NAME_S[]    = "RDY";
   const uint32_t STATE_RUNNING_MASK      = 1<<1;
   const   char   STATE_RUNNING_NAME[]    = "Running";
   const   char   STATE_RUNNING_NAME_S[]  = "RUN";
   const uint32_t STATE_WAITDEP_MASK      = 1<<2;
   const   char   STATE_WAITDEP_NAME[]    = "Wainting dependences";
   const   char   STATE_WAITDEP_NAME_S[]  = "WD";
   const uint32_t STATE_WAITTIME_MASK     = 1<<3;
   const   char   STATE_WAITTIME_NAME[]   = "Wainting time";
   const   char   STATE_WAITTIME_NAME_S[] = "WT";
   const uint32_t STATE_DONE_MASK         = 1<<4;
   const   char   STATE_DONE_NAME[]       = "Done";
   const   char   STATE_DONE_NAME_S[]     = "DON";
   const uint32_t STATE_ERROR_MASK        = 1<<5;
   const   char   STATE_ERROR_NAME[]      = "Error";
   const   char   STATE_ERROR_NAME_S[]    = "ERR";
   const uint32_t STATE_STDOUT_MASK       = 1<<6;
   const   char   STATE_STDOUT_NAME[]     = "StdOut";
   const   char   STATE_STDOUT_NAME_S[]   = "StO";
   const uint32_t STATE_STDERR_MASK       = 1<<7;
   const   char   STATE_STDERR_NAME[]     = "StdErr";
   const   char   STATE_STDERR_NAME_S[]   = "StE";
   const uint32_t STATE_SKIPPED_MASK      = 1<<8;
   const   char   STATE_SKIPPED_NAME[]    = "Skipped";
   const   char   STATE_SKIPPED_NAME_S[]  = "SKP";
   const uint32_t STATE_OFFLINE_MASK      = 1<<9;
   const   char   STATE_OFFLINE_NAME[]    = "Offline";
   const   char   STATE_OFFLINE_NAME_S[]  = "OFF";
}
