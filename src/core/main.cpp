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
  Position *pos = ds::dyn_arr::get_mut(positions, entity_id);
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
  EntityRegistry registry;
  registry.positions = ds::dyn_arr::init<Position> ();
  ds::dyn_arr::push (registry.positions, { 0.0f, 0.0f });
  ds::dyn_arr::push (registry.positions, { 1.5f, 2.0f });
  ds::dyn_arr::push (registry.positions, { 2.0f, 3.0f });

  registry.sprites = ds::dyn_arr::init<Sprite> ();
  ds::dyn_arr::push (registry.sprites, { 1 });
  ds::dyn_arr::push (registry.sprites, { 2 });
  ds::dyn_arr::push (registry.sprites, { 3 });

  registry.types = ds::dyn_arr::init<EntityType> ();
  ds::dyn_arr::push (registry.types, PLAYER);
  ds::dyn_arr::push (registry.types, ENEMY_MELLE);
  ds::dyn_arr::push (registry.types, ENEMY_RANGED);

  update_entity_position (registry.positions, 0, { 10.0f, 12.0f });

  // Test insert and remove, if it's right this whole block does nothing
  // ----------------------------------------------
  ds::dyn_arr::insert (registry.positions, { 5.0f, 5.0f }, 1);
  ds::dyn_arr::insert (registry.sprites, { 4 }, 1);
  ds::dyn_arr::insert (registry.types, ENEMY_RANGED, 1);

  ds::dyn_arr::insert (registry.positions, { 5.0f, 5.0f }, 1);
  ds::dyn_arr::insert (registry.sprites, { 4 }, 1);
  ds::dyn_arr::insert (registry.types, ENEMY_RANGED, 1);

  ds::dyn_arr::insert (registry.positions, { 5.0f, 5.0f }, 1);
  ds::dyn_arr::insert (registry.sprites, { 4 }, 1);
  ds::dyn_arr::insert (registry.types, ENEMY_RANGED, 1);

  ds::dyn_arr::remove (registry.positions, 1);
  ds::dyn_arr::remove (registry.sprites, 1);
  ds::dyn_arr::remove (registry.types, 1);

  ds::dyn_arr::remove (registry.positions, 1);
  ds::dyn_arr::remove (registry.sprites, 1);
  ds::dyn_arr::remove (registry.types, 1);

  // Descalate so metadata shows Avaliable = 4
  ds::dyn_arr::remove (registry.positions, 1, true);
  ds::dyn_arr::remove (registry.sprites, 1, true);
  ds::dyn_arr::remove (registry.types, 1, true);
  // ----------------------------------------------

  unsigned count = 3;
  while (count--)
    {
      update_positions (registry.positions, registry.types);
      render_sprites (registry.positions, registry.sprites);

      std::cout << "\n";
    }

  ds::dyn_arr::print_data (registry.types);
  ds::dyn_arr::print_metadata (registry.types);
}