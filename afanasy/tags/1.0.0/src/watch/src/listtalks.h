#pragma once

#include "listnodes.h"

#include <msg.h>

class MCTalkOnlineList;

class ListTalks : public ListNodes
{
   Q_OBJECT

public:
   ListTalks( QWidget* parent);
   ~ListTalks();

   bool caseMessage( af::Msg * msg);
   ItemNode* createNewItem( af::Node *node);

protected:
   void contextMenuEvent( QContextMenuEvent *event);

private slots:
   void actSendMessage();

private:
   static int     SortType;
   static bool    SortAscending;
   static QString FilterString;
   static int     FilterType;
   static bool    FilterInclude;
};
