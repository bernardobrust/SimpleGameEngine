import <iostream>;

import dyn_arr;

// For testing only now
using namespace engine::ds::dyn_arr;

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
  DynArr<Position> *positions;
  DynArr<Sprite> *sprites;
  DynArr<EntityType> *types;
};

void
update_positions (DynArr<Position> *positions, DynArr<EntityType> *types)
{
  for (size_t i{ 0 }; i < length (positions); ++i)
    {
      EntityType type = get (types, i);
      Position pos = get (positions, i);
      switch (type)
        {
        case PLAYER:
          pos.x += 1.0f;
          pos.y += 1.0f;
          break;
        case ENEMY_MELLE:
          pos.x += 0.5f;
          pos.y += 0.3f;
          break;
        case ENEMY_RANGED:
          pos.x -= 0.3f;
          pos.y -= 0.2f;
          break;
        }
    }
}

void
render_sprites (DynArr<Position> *positions, DynArr<Sprite> *sprites)
{
  for (size_t i{ 0 }; i < length (positions); ++i)
    {
      std::cout << "Rendering sprite " << get (sprites, i).texture_id
                << " at (" << get (positions, i).x << ", "
                << get (positions, i).y << ")\n";
    }
}

void
update_entity_position (DynArr<Position> *positions, unsigned entity_id,
                        Position new_pos)
{
  // We could have some validation logic here for example
  positions->data[entity_id] = new_pos;
}

[[nodiscard]] EntityData
get_entity (const EntityRegistry *entities, unsigned id)
{
  EntityData e;
  e.position = get (entities->positions, id);
  e.sprite = get (entities->sprites, id);
  e.type = get (entities->types, id);
  return e;
}

int
main ()
{
  EntityRegistry registry;
  registry.positions = init<Position> ();
  push (registry.positions, { 0.0f, 0.0f });
  push (registry.positions, { 1.5f, 2.0f });
  push (registry.positions, { 2.0f, 3.0f });

  registry.sprites = init<Sprite> ();
  push (registry.sprites, { 1 });
  push (registry.sprites, { 2 });
  push (registry.sprites, { 3 });

  registry.types = init<EntityType> ();
  push (registry.types, PLAYER);
  push (registry.types, ENEMY_MELLE);
  push (registry.types, ENEMY_RANGED);

  update_entity_position (registry.positions, 0, { 10.0f, 12.0f });

  unsigned count = 3;
  while (count--)
    {
      update_positions (registry.positions, registry.types);
      render_sprites (registry.positions, registry.sprites);

      std::cout << "\n";
    }

  EntityData e = get_entity (&registry, 1);
  printf ("Pos = (%f, %f), Sprite id = %d, Type id = %d", e.position.x,
          e.position.y, e.sprite.texture_id, e.type);

  /*
    // Testing init
    DynArr<int> *xs = init<int> ();

    // Testing push
    push (xs, 5);
    print_metadata (xs);
    print_data (xs);

    push (xs, 10);
    print_metadata (xs);
    print_data (xs);

    push (xs, 1);
    push (xs, 2);
    push (xs, 3);
    push (xs, 4);
    print_metadata (xs);
    print_data (xs);

    // Testing scaling by less than 2
    push (xs, 1, 1.5f);
    push (xs, 2, 1.5f);
    push (xs, 3, 1.5f);
    push (xs, 4, 1.5f);
    print_metadata (xs);
    print_data (xs);

    // Try poping with resize
    unsigned count = 7;
    while (count--)
      {
        pop (xs, true);
      }
    print_metadata (xs);
    print_data (xs);

    pop (xs, true);
    print_metadata (xs);
    print_data (xs);
    */
}