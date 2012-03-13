#pragma once

#include <QtGui/QTextEdit>
#include <name_af.h>

class Reciever
{
public:
   Reciever();
   ~Reciever();

   virtual bool caseMessage( af::Msg * msg) = 0;

   virtual void connectionLost();
   virtual void connectionEstablished();

private:
};
