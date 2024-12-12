#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector2.h"
#include "entity.h"

class Physics {
public:
  Vector2 get_overlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
  Vector2 get_previous_overlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};

#endif