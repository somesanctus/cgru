#pragma once

#include <QtGui/QBoxLayout>
#include <QtCore/QLinkedList>
#include <QtGui/QListWidget>
#include <QtCore/QTimer>
#include <QtGui/QWidget>

#include <msgclasses/msgclassuserhost.h>
#include <qserver.h>
#include <qthreadclientsend.h>
#include <qthreadclientup.h>

#include "infoline.h"
#include "watch.h"

class ButtonOut;
class ButtonMonitor;
class ListItems;

class QHBoxLayout;
class QVBoxLayout;
class QScrollArea;

class Dialog : public QWidget
{
   Q_OBJECT

public:
   Dialog();
   ~Dialog();

   inline bool isInitialized() const { return initialized; }
   inline bool isConnected()   const { return connected;   }

   inline int getUid() const { return uid;}

   void inline displayInfo(    const QString &message) { infoline->displayInfo(    message); }
   void inline displayWarning( const QString &message) { infoline->displayWarning( message); }
   void inline displayError(   const QString &message) { infoline->displayError(   message); }

   void sendMsg( afqt::QMsg * msg);

   void openMonitor( int type, bool open);

   inline MonitorHost * getMonitor() { return monitor;}

   void repaintStart( int mseconds = 1000);
   void repaintFinish();

signals:
   void stop();

private slots:
   void newMessage( af::Msg *msg);
   void connectionLost( af::Address* address);
   void repaintWatch();

   void actColors();
   void actSavePreferencesOnExit();
   void actSaveGUIOnExit();
   void actSaveWndRectsOnExit();
   void actSavePreferences();

protected:
   void keyPressEvent(     QKeyEvent   * event);
   void contextMenuEvent( QContextMenuEvent *event);
   void closeEvent( QCloseEvent * event);

private:
   bool connected;
   int uid;
   MonitorHost * monitor;

   int monitorType;

   afqt::QThreadClientUp   qThreadClientUpdate;
   afqt::QThreadClientSend qThreadSend;
   afqt::QServer           qServer;

   ListItems * listitems;

   InfoLine * infoline;

   QHBoxLayout *hlayoutB;
   QVBoxLayout *vlayoutB;
   QHBoxLayout *hlayout;
   QVBoxLayout *vlayout;

   QTimer repaintTimer;

   ButtonMonitor *btnMonitor[Watch::WLAST];

   ButtonOut *btn_outlft;
   ButtonOut *btn_outrht;

   af::MsgClassUserHost mcuserhost;

   bool initialized;

private:
   void sendRegister();
   void closeList();
   void connectionEstablished();
   void setDefaultWindowTitle();
};
