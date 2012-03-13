#pragma once

#include <afjob.h>
#include <msgclasses/mctaskup.h>
#include <taskexec.h>
#include <dbrender.h>

class MsgAf;
class MsgQueue;
class JobContainer;
class RenderContainer;

/// Afanasy server side of Render host.
class RenderAf: public afsql::DBRender
{
public:
/// Construct Render from message and provided address.
   RenderAf( af::Msg * msg, const af::Address * addr = NULL);
   ~RenderAf();

/// Construct offline render for database.
   RenderAf( int Id);

/// Set registration time ( and update time).
   void setRegisterTime();

/// Awake offline render
   bool online( RenderAf * render, MonitorContainer * monitoring);

/// Add task \c taskexec to render, \c start or only capture it
   void setTask( af::TaskExec *taskexec, MonitorContainer * monitoring, bool start = true);

/// Start tast \c taskexec on remote render host, task must be set before and exists on render.
   void startTask( af::TaskExec *taskexec);

/// Make Render to stop task.
   void stopTask( int jobid, int blocknum, int tasknum, int number);

/// Make Render to stop task.
   inline void stopTask( const af::TaskExec * taskexec)
      { stopTask(taskexec->getJobId(), taskexec->getBlockNum(), taskexec->getTaskNum(), taskexec->getNumber());}

/// Make Render to stop task.
   inline void stopTask( const af::MCTaskUp &taskup)
      { stopTask(taskup.getNumJob(), taskup.getNumBlock(), taskup.getNumTask(), taskup.getNumber());}

/// Make Render to finish task.
   void taskFinished( const af::TaskExec * taskexec, MonitorContainer * monitoring);

/// Refresh parameters.
   void refresh( time_t currentTime, AfContainer * pointer, MonitorContainer * monitoring);

/// Get host parameters from farm.
   bool getFarmHost( af::Host * newHost = NULL);

   void sendOutput( af::MCListenAddress & mclisten, int JobId, int Block, int Task);

/// Deregister render, on SIGINT client recieving.
   void deregister( JobContainer * jobs, MonitorContainer * monitoring );

/// Set some Render attribute.
   bool action( const af::MCGeneral & mcgeneral, int type, AfContainer * pointer, MonitorContainer * monitoring);

   inline QStringList* getLog() { return &log; }   ///< Get log.
   void getServices( af::Msg * msg) const;         ///< Get services information.

   virtual int calcWeight() const; ///< Calculate and return memory size.

   bool canRunService( const QString & type) const; ///< Check whether block can run a service

   bool update( af::Render * render);   ///< Update Render.

public:
   /// Set jobs container.
   inline static void setRenderContainer( RenderContainer *Rendercontainer){ renders = Rendercontainer;}

   /// Stop task on render if it is not running (for server)
   static void closeLostTask( const af::MCTaskUp &taskup);

private:
   QString hostname;
   QString hostdescription;

   std::vector<int> servicescounts;
   int servicesnum;

   QStringList log;                          ///< Log.

private:
   void init();

   void addService( const QString & type);
   void remService( const QString & type);

   void ejectTasks( JobContainer * jobs, MonitorContainer * monitoring, uint32_t upstatus);  ///< Stop task with \c message to log.

   void exitClient( int type, JobContainer * jobs, MonitorContainer * monitoring);   ///< Exit Render client program.

/// Set Render to Ofline. \c updateTaskState - whether to update it's state.
   void offline( JobContainer * jobs, uint32_t updateTaskState, MonitorContainer * monitoring, bool toZombie = false );

   void appendLog( const QString &message);  ///< Append task log with a \c message .

private:
   static RenderContainer * renders;
};
