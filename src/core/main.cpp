import <iostream>;

import dyn_arr;
import platform;

using namespace engine;

// We could also have speeds, but this is just for testing
struct Position
{
  float x, y;
};
struct Sprite
{
  unsigned texture_id;
};

enum EntityType
{
  PLAYER,
  ENEMY_MELLE,
  ENEMY_RANGED,
};

struct EntityData
{
  Position position;
  Sprite sprite;
  EntityType type;
};

// Paralel vectors
struct EntityRegistry
{
  ds::dyn_arr::DynArr<Position> *positions;
  ds::dyn_arr::DynArr<Sprite> *sprites;
  ds::dyn_arr::DynArr<EntityType> *types;
};

void
update_positions (ds::dyn_arr::DynArr<Position> *positions,
                  ds::dyn_arr::DynArr<EntityType> *types)
{
  for (size_t i{ 0 }; i < length (positions); ++i)
    {
      EntityType type = ds::dyn_arr::get (types, i);
      Position *pos = ds::dyn_arr::get_mut (positions, i);
      switch (type)
        {
        case PLAYER:
          pos->x += 1.0f;
          pos->y += 1.0f;
          break;
        case ENEMY_MELLE:
          pos->x += 0.5f;
          pos->y += 0.3f;
          break;
        case ENEMY_RANGED:
          pos->x -= 0.3f;
          pos->y -= 0.2f;
          break;
        }
    }
}

void
render_sprites (ds::dyn_arr::DynArr<Position> *positions,
                ds::dyn_arr::DynArr<Sprite> *sprites)
{
  for (size_t i{ 0 }; i < length (positions); ++i)
    {
      std::cout << "Rendering sprite "
                << ds::dyn_arr::get (sprites, i).texture_id << " at ("
                << ds::dyn_arr::get (positions, i).x << ", "
                << ds::dyn_arr::get (positions, i).y << ")\n";
    }
}

void
update_entity_position (ds::dyn_arr::DynArr<Position> *positions,
                        unsigned entity_id, Position new_pos)
{
  // We could have some validation logic here for example
  Position *pos = ds::dyn_arr::get_mut (positions, entity_id);
  *pos = new_pos;
}

EntityData
get_entity (const EntityRegistry *entities, unsigned id)
{
  EntityData e;
  e.position = ds::dyn_arr::get (entities->positions, id);
  e.sprite = ds::dyn_arr::get (entities->sprites, id);
  e.type = ds::dyn_arr::get (entities->types, id);
  return e;
}

int
main ()
{
  platform::PlatformState platform_state;
  platform::init (&platform_state, "Hello!", 0, 0, 480, 360);

  while (platform::update (&platform_state))
    {
      // std::cout << "running\n";
    }

  platform::shutdown (&platform_state);
}