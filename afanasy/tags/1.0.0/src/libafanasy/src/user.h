#ifndef AF_USER_H
#define AF_USER_H

#include <aftypes.h>
#include <time.h>

#include <QtCore/QStringList>

#include <name_af.h>
#include "afnode.h"

namespace af
{
/// Afanasy user class
/** When Afanasy register a new job, it register a new user, or add job to existing user (with the same name).
**/
class User : public Node
{
public:

/// Construct a new user from job.
   User( const QString &username, const QString &host);

/// Construct user from id only.
   User( int uid);

/// Build user data from buffer.
   User( Msg * msg);

   virtual ~User();                       ///< Destructor.

   void stdOut( bool full = false) const; ///< Print user general information.

   inline bool setHostsMask(         const QString & str  )
      { return setRegExp( hostsmask, str, "user hosts mask");}
   inline bool setHostsMaskExclude(  const QString & str  )
      { return setRegExp( hostsmask_exclude, str, "user exclude hosts mask");}

   inline bool hasHostsMask()          const { return false == hostsmask.isEmpty();          }
   inline bool hasHostsMaskExclude()   const { return false == hostsmask_exclude.isEmpty();  }

   inline const QString& getHostName() const { return hostname;}
   inline void  setHostName( const QString & str) { hostname = str;}

   inline const QString getHostsMask()          const { return hostsmask.pattern();          }
   inline const QString getHostsMaskExclude()   const { return hostsmask_exclude.pattern();  }

   inline bool checkHostsMask(         const QString & str  ) const
      { if( hostsmask.isEmpty()        ) return true;   return hostsmask.exactMatch(str); }
   inline bool checkHostsMaskExclude(  const QString & str  ) const
      { if( hostsmask_exclude.isEmpty()) return false;  return hostsmask_exclude.exactMatch(str); }

   inline int      getMaxHosts()       const { return maxhosts;       } ///< Get maximum hosts.
   inline bool     isPermanent()       const { return permanent;      } ///< Wheter the user is permanent.
   inline int      getNumJobs()        const { return numjobs;        } ///< Get jobs quantity.
   inline int      getNumRunningJobs() const { return numrunningjobs; } ///< Get active jobs quantity.
   inline int      getNumHosts()       const { return numhosts;       } ///< Get number of hosts used by user jobs.
   inline float    getNeed()           const { return need;           } ///< Get user need for hosts.
   inline uint32_t getTimeRegister()   const { return time_register;  } ///< Get register time.
   inline uint32_t getTimeOnline()     const { return time_online;    } ///< Get online time.

/// Get maximum number or errors on same host for job NOT to avoid host
   inline uint8_t  getErrorsAvoidHost()      const { return errors_avoidhost;    }
/// Get maximum number of errors in task to retry it automatically
   inline uint8_t  getErrorsRetries()        const { return errors_retries;      }
/// Get maximum number or errors on same host for task NOT to avoid host
   inline uint8_t  getErrorsTaskSameHost()   const { return errors_tasksamehost; }

   inline void setSolved( bool value) { solved = value; }
   inline bool  isSolved()            { return  solved; }

   virtual int calcWeight() const; ///< Calculate and return memory size.

protected:
   QString  hostname;          ///< User host name.
   int32_t  maxhosts;          ///< User maximum hosts.

   QRegExp hostsmask;
   QRegExp hostsmask_exclude;

/// Maximum number of errors in task to retry it automatically
   uint8_t errors_retries;
/// Maximum number or errors on same host to make job to avoid it
   uint8_t errors_avoidhost;
/// Maximum number or errors on same host for task NOT to avoid host
   uint8_t errors_tasksamehost;

   bool permanent;             ///< Whether the user is permanent.

   uint32_t time_register;      ///< User registration time (when he become permanent).

   int32_t numjobs;           ///< User jobs quantity.
   int32_t numrunningjobs;    ///< User active jobs quantity.
   int32_t numhosts;          ///< User jobs hosts number.
   uint32_t time_online;      ///< User online (server registration) time.
   float need;                ///< User need for hosts.
   bool solved;               ///< User have produced a task.

private:
   void construct();
   void readwrite( Msg * msg);   ///< Read or write user in buffer.
};
}
#endif
