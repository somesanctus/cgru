#ifndef AF_HOST_H
#define AF_HOST_H

#include <QtCore/QString>

#include "af.h"

namespace af
{
class HostRes : public Af
{
public:
   HostRes();

   uint8_t cpu_loadavg1;
   uint8_t cpu_loadavg2;
   uint8_t cpu_loadavg3;

   uint8_t cpu_user;
   uint8_t cpu_nice;
   uint8_t cpu_system;
   uint8_t cpu_idle;
   uint8_t cpu_iowait;
   uint8_t cpu_irq;
   uint8_t cpu_softirq;


   uint32_t mem_free_mb;
   uint32_t mem_cached_mb;
   uint32_t mem_buffers_mb;

   uint32_t swap_used_mb;

   uint32_t hdd_free_gb;

   uint32_t net_recv_kbsec;
   uint32_t net_send_kbsec;

   void stdOut( bool full = false) const;

   void readwrite( Msg * msg); ///< Read or write Host Resources in message.
};

class Host : public Af
{
public:
   Host();
   ~Host();

   void setService( const QString & name, int count);

   void copy( const Host & other);

   void stdOut( bool full = false ) const;

   inline int getServicesNum()        const { return servicesnum;       }
   inline int getServiceCount( int n) const { return servicescounts[n]; }
   inline const QString & getServiceName(  int n) const { return servicesnames[n];}

   int32_t  capacity;
   int32_t  maxtasks;
   int32_t  power;
   uint32_t cpu_num;
   uint32_t cpu_mhz;
   uint32_t mem_mb;
   uint32_t swap_mb;
   uint32_t hdd_gb;
   QString  os;
   QString  properties;

   void readwrite( Msg * msg); ///< Read or write Host in message.

private:
   QStringList servicesnames;
   std::vector<int32_t> servicescounts;

private:
   int32_t servicesnum;
};
}
#endif
