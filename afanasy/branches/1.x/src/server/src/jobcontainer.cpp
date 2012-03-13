#include "jobcontainer.h"

#include <stdio.h>
#include <string.h>
#include <memory.h>

#include "msgaf.h"
#include "useraf.h"
#include "usercontainer.h"
#include "rendercontainer.h"
#include "monitorcontainer.h"

#include <msgclasses/mcafnodes.h>

#include <qdbconnection.h>

#define AFOUTPUT
#undef AFOUTPUT
#include <macrooutput.h>

afsql::DBConnection * JobContainer::afDB = NULL;

JobContainer::JobContainer():
   AfContainer( AFJOB::MAXQUANTITY)
{
}

JobContainer::~JobContainer()
{
AFINFO("JobContainer::~JobContainer:\n");
}

void JobContainer::updateTaskState( af::MCTaskUp &taskup, RenderContainer * renders, MonitorContainer * monitoring)
{
   switch( taskup.getStatus())
   {
   case af::TaskExec::UPNULL:
   case af::TaskExec::UPNoTaskRunning:
   case af::TaskExec::UPNoJob:
   case af::TaskExec::UPLAST:
      AFERRAR("JobContainer::updateTaskState: Bad task update status (jobID=%d).\n", taskup.getNumJob());
   return;
   }

   JobContainerIt jobsIt( this);
   JobAf* job = jobsIt.getJob( taskup.getNumJob());
   if( job != NULL )
   {
      job->updateTaskState( taskup, renders, monitoring);
      return;
   }

// Job does not exist!
   AFERRAR("JobContainer::updateTaskState: Job with id=%d does not exists.\n", taskup.getNumJob());
   if( taskup.getStatus() == af::TaskExec::UPPercent) RenderAf::closeLostTask( taskup);
}

int JobContainer::job_register( JobAf *job, UserContainer *users, MonitorContainer * monitoring)
{
printf("Registering new job:\n");

   if( job == NULL )
   {
      AFERROR("JobContainer::job_register: Can't allocate memory for new job.\n");
      return 0;
   }
   if( job->isConstructed() == false )
   {
      AFERROR("JobContainer::job_register: Job was not constructed.\n");
      return 0;
   }
   if( users == NULL )
   {
      AFERROR("JobContainer::job_register: Users container is not set.\n");
      return 0;
   }

   UserAf *user;

   {  // Register new user if job has a new user name.
      AfContainerLock uLock( users,       AfContainer::WRITELOCK  );
      if( monitoring) AfContainerLock mLock( monitoring,  AfContainer::WRITELOCK  );

      AFINFA("JobContainer::job_register: Checking job user '%s'\n", job->getUserName().toUtf8().data());
      user = users->addUser( job->getUserName(), job->getHostName(), monitoring);
      if( user == NULL )
      {
         delete job;
         AFERROR("JobContainer::job_register: Can't register new user.\n");
         return 0;
      }
      {  // Add job node to container.
         AfContainerLock jLock( this,  AfContainer::WRITELOCK);

         if( add((af::Node*)job) == false )
         {
            delete job;
            AFERROR("JobContainer::job_register: Can't add job to container.\n");
            return 0;
         }
         AFINFO("JobContainer::job_register: locking job.\n");
         job->lock();
      }
      AFINFO("JobContainer::job_register: locking user.\n");
      user->lock();
      user->addJob( job);
      if( monitoring )
      {
         AFINFO("JobContainer::job_register: monitor new job events.\n");
         monitoring->addJobEvent( af::Msg::TMonitorJobsAdd, job->getId(), user->getId());
         monitoring->addEvent( af::Msg::TMonitorUsersChanged, user->getId());
      }
   }

   {  // initialize job ( create tasks output folder, execute "pre"commands if any)
      AFINFO("JobContainer::job_register: initiaizing new job with user.\n");
      if( job->initialize( user) == false)
      {
         AFERROR("JobContainer::job_register: Job initialization failed.\n");

         user->unLock();
         job->unLock();

         if( monitoring )
         {
            AfContainerLock mLock( monitoring,  AfContainer::WRITELOCK  );

            monitoring->addJobEvent( af::Msg::TMonitorJobsDel, job->getId(), user->getId());
            monitoring->addEvent( af::Msg::TMonitorUsersChanged, user->getId());
         }

         job->setZombie( NULL, NULL);

         return 0;
      }
   }

   {  // write job to database ( if it is not created from database)
      if( job->fromDataBase() == false )
      {
         AFINFO("JobContainer::job_register: writing job to database.\n");
         if( afDB == NULL )
         {
            AFERROR("JobContainer::job_register: Afanasy database is not set.\n");
         }
         else
         {
            if( afDB->DBOpen())
            {
               afDB->addJob( job);
               afDB->DBClose();
            }
         }
      }

      AFINFO("JobContainer::job_register: unlocking user and job.\n");
      user->unLock();
      job->unLock();

      if( monitoring )
      {
         AfContainerLock mLock( monitoring,  AfContainer::WRITELOCK  );

         AFINFO("JobContainer::job_register: monitor unlock job and user events.\n");
         monitoring->addJobEvent( af::Msg::TMonitorJobsChanged, job->getId(), user->getId());
         monitoring->addEvent( af::Msg::TMonitorUsersChanged, user->getId());
      }
   }

   af::printTime(); printf(" : Job registered: "); job->stdOut( false );
   return job->getId();
}

void JobContainer::getWeight( af::MCJobsWeight & jobsWeight )
{
   JobContainerIt jobsIt( this);
   for( JobAf *job = jobsIt.job(); job != NULL; jobsIt.next(), job = jobsIt.job())
   {
      int weight = job->calcWeight();
      jobsWeight.add(
            job->getName(),
            job->getId(),
            job->getLogsWeight(),
            job->getBlackListsWeight(),
            job->getProgressWeight(),
            weight
         );
   }
}

//############################################################################
//                               JobQueueIt
//############################################################################

JobContainerIt::JobContainerIt( JobContainer* jobContainer, bool skipZombies):
   AfContainerIt( (AfContainer*)jobContainer, skipZombies)
{
}

JobContainerIt::~JobContainerIt()
{
}
