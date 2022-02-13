#include "entity.h"

void simple_movement(Entity* self, float speedx, float speedy) {
    vector2d_add(self->position, self->position, vector2d(speedx, speedy));
    self->min.x += speedx;
    self->max.x += speedx;
    self->min.y += speedy;
    self->max.y += speedy;
}

Uint8 ent_rect_collision(Entity* self, Entity* other) {
    return (self->min.x <= other->max.x && self->max.x >= other->min.x) &&
        (self->min.y <= other->max.y && self->max.y >= other->min.y);
}