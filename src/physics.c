#include "entity.h"

Uint8 ent_rect_collision(Entity* self, Entity* other) {
    return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
        (self->min.x <= other->max.y && self->max.y >= other->min.y);
}