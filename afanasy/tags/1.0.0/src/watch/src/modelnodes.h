#pragma once

#include "modelitems.h"

#include <af.h>

class Item;
class ItemNode;

class ModelNodes : public ModelItems
{
Q_OBJECT
public:
   ModelNodes( QObject * parent);
   virtual ~ModelNodes();

   int addNode( ItemNode * node, int row = -1);

   int addNodeSorted( ItemNode * node, bool ascending);

   void sortnodes( const QList<ItemNode*> & itemstosort, bool ascending);

   void sortnodes( bool ascending = true);

   void sortMatch( const std::vector<int32_t> * list);

signals:
   void nodeAdded( ItemNode * node, const QModelIndex & index);

private:
};
