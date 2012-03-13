#pragma once

#include <QtCore/QLinkedList>
#include <QtCore/QStringList>

#include <name_afqt.h>

class QApplication;

class ButtonMonitor;
class Dialog;
class ListItems;
class MonitorHost;
class Reciever;
class Wnd;
class WndList;

class Watch
{
public:
   Watch( Dialog * pDialog, QApplication * pApplication);
   ~Watch();

   static void destroy();

   enum MonType{
               WNONE,

               WJobs,
               WUsers,
               WRenders,
               WTalks,
               WMonitors,

               WLAST
            };

   static const QString BtnName[WLAST];
   static const QString WndName[WLAST];

   static bool isInitialized();
   static bool isConnected();
   static int  getUid();
   static int  getId();

   static void connectionLost();
   static void connectionEstablished();

   static void sendMsg(  afqt::QMsg * msg);

   static void addWindow(      Wnd      * wnd      );
   static void removeWindow(   Wnd      * wnd      );
   static void addReciever(    Reciever * reciever );
   static void removeReciever( Reciever * reciever );

   static bool caseMessage( af::Msg * msg);

   static void setWindowTitle( const QString & title);

   static void displayInfo(    const QString &message);
   static void displayWarning( const QString &message);
   static void displayError(   const QString &message);

   inline static const QStringList * getPreviewCmds() { return &previewcmds; }

   static void openMonitor( int type, bool open);

   static void listenJob(  int id, const QString & name);
   inline static void listenJob_rem(  int id) { listenjobids.removeAll(id);}
   static void watchTasks( int id, const QString & name);
   static void watchTasks_rem( int id);
   static void listenTask( int jobid, int block, int task, const QString & name);


   inline static Dialog      * getDialog()  { return d;}

   static void   subscribe( const QList<int> & events);
   static void unsubscribe( const QList<int> & events);

   static void setUid(   int uid );

   static void addJobId( int jId );
   static void delJobId( int jId );

   static WndList* opened[WLAST];

   static void raiseWindow( QWidget * wnd, const QString * name = NULL);

   static void repaint();
   static void repaintStart();
   static void repaintFinish();

private:
   static MonitorHost * m;
   static Dialog * d;
   static QApplication * app;

   static QLinkedList<Wnd*> windows;
   static QLinkedList<Reciever*> recievers;

   static QStringList previewcmds;

   static QLinkedList<int> listenjobids;
   static QLinkedList<int> watchtasksjobids;
   static QLinkedList<QWidget*> watchtaskswindows;
};
