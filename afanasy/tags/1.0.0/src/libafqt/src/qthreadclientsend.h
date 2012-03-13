#pragma once

#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>


#include "name_afqt.h"
#include "qmsg.h"
#include "qthreadclient.h"

/// Class that can send messages in a different thread.
/** send( Msg *msg) function will write message into a buffer and execute a thread to send it,
*** or wake a thread if already exists one.
*** After sending that thead will sleep, until send function will wake it up.
**/
class afqt::QThreadClientSend : public afqt::QThreadClient
{
   Q_OBJECT
public:
   QThreadClientSend( QObject * parent, int NumConnLost = 1 );
   ~QThreadClientSend();      ///< Dectructor for safety thread exit.

   virtual void run();        ///< QThread.run() method override.
   void send( afqt::QMsg * msg);    ///< Send message function.

protected:
};
