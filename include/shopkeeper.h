#ifndef __SHOPKEEPER_H__
#define __SHOPKEEPER_H__

#include "entity.h"

void Shopkeeper_think();

void Shopkeeper_onTouch(Entity* self, Entity* other);

void Shopkeeper_openMenu(Entity* self);

Entity* Shopkeeper_new();


#endif

