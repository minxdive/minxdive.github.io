#include <cmath>
#include "physics.h"

Vector2 Physics::get_overlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  if (!a->get_component<Bounding_box_component>().has || !b->get_component<Bounding_box_component>().has) {
    return Vector2{0.0f,0.0f};
  }
  auto& a_tran = a->get_component<Transform_component>();
  auto& b_tran = b->get_component<Transform_component>();
  auto& a_bounds = a->get_component<Bounding_box_component>();
  auto& b_bounds = b->get_component<Bounding_box_component>();
  Vector2 delta = {abs(a_tran.position.x - b_tran.position.x), abs(a_tran.position.y - b_tran.position.y)};
  Vector2 overlap = { (a_bounds.half_size.x + b_bounds.half_size.x) - delta.x , (a_bounds.half_size.y + b_bounds.half_size.y) - delta.y };
  return overlap;
}

Vector2 Physics::get_previous_overlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
  if (!a->get_component<Bounding_box_component>().has || !b->get_component<Bounding_box_component>().has) {
    return Vector2{0.0f,0.0f};
  }
  auto& a_tran = a->get_component<Transform_component>();
  auto& b_tran = b->get_component<Transform_component>();
  auto& a_bounds = a->get_component<Bounding_box_component>();
  auto& b_bounds = b->get_component<Bounding_box_component>();
  Vector2 delta = {abs(a_tran.prev_pos.x - b_tran.prev_pos.x), abs(a_tran.prev_pos.y - b_tran.prev_pos.y)};
  Vector2 prev_overlap = { (a_bounds.half_size.x + b_bounds.half_size.x) - delta.x , (a_bounds.half_size.y + b_bounds.half_size.y) - delta.y };
  return prev_overlap;
}