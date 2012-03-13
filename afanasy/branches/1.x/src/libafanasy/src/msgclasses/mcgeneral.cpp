#include "mcgeneral.h"

#include <stdio.h>

#include <name_af.h>

//#define AFOUTPUT
////#undef AFOUTPUT
#include <macrooutput.h>

using namespace af;

MCGeneral::MCGeneral():
   name( ""),
   string( ""),
   number( 0),
   id(-1)
{
}

MCGeneral::MCGeneral( int32_t Number):
   name( ""),
   string( ""),
   number( Number),
   id(-1)
{
}

MCGeneral::MCGeneral( const QString & String):
   name( ""),
   string( String),
   number( 0),
   id(-1)
{
}


MCGeneral::MCGeneral( const QString & Name, int32_t Number):
   name( Name),
   string( ""),
   number( Number),
   id(-1)
{
}

MCGeneral::MCGeneral( const QString & Name, const QString & String):
   name( Name),
   string( String),
   number( 0),
   id(-1)
{
}

MCGeneral::MCGeneral( Msg * msg)
{
   read( msg);
}

MCGeneral::~MCGeneral()
{
}

void MCGeneral::readwrite( Msg * msg)
{
   MsgClassUserHost::readwrite( msg);

   rw_QString(    name,   msg);
   rw_QString(    string, msg);
   rw_int32_t(    number, msg);
   rw_int32_t(    id,     msg);
   rw_Int32_Vect( list,   msg);
}

bool MCGeneral::hasId( int value)
{
   int count = list.size();
   for( int i = 0; i < count; i++)
      if( list[i] == value) return true;
   return false;
}

void MCGeneral::stdOut( bool full) const
{
   MsgClassUserHost::stdOut( false);

   printf("\nName = \"%s\", Id = %d, String = \"%s\", Number = %d.\n", name.toUtf8().data(), id, string.toUtf8().data(), number);

   if( full == false ) return;

   int count = list.size();
   printf("ids[%d]=", count);
   for( int p = 0; p < count; p++) printf(" %d", list[p]);
   printf(".\n");
}
