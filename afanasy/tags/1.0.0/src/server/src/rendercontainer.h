#pragma once

#include "rendercontainer.h"
#include "clientcontainer.h"
#include "renderaf.h"

#include <msgclasses/mctaskup.h>

class MsgAf;

/// Renders container.
class RenderContainer : public ClientContainer
{
public:
   RenderContainer();
   ~RenderContainer();

/// Add new Render to container, new id returned on success, else return 0.
   MsgAf * addRender( RenderAf *newRender, MonitorContainer * monitoring = NULL);

/// Set Render with \c id zombie, by calling RenderAf::setZombie( \c updateTaskState ) function.

private:
};

/// Renders iterator.
class RenderContainerIt : public AfContainerIt
{
public:
   RenderContainerIt( RenderContainer* container, bool skipZombies = true);
   ~RenderContainerIt();

   inline RenderAf* render() { return (RenderAf*)node; }
   inline RenderAf* getRender( int id) { return (RenderAf*)(get( id)); }

private:
};
