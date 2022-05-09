#ifndef __NPC_H__
#define __NPC_H__

#include "entity.h"

void NPC_think();

void NPC_onTouch(Entity* self, Entity* other);

void NPC_openMenu(Entity* self);

Entity* NPC_new();

#endif