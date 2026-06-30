import <cstdio>;

// Temporary
import <vector>;

import dyn_arr;

// We could also have speeds, but this is just for testing
struct Position { float x, y; };
struct Sprite { unsigned texture_id; };

enum EntityType {
    PLAYER,
    ENEMY_MELLE,
    ENEMY_RANGED,
};

struct EntityData {
    Position position;
    Sprite sprite;
    EntityType type;
};

// Paralel vectors
struct EntityRegistry {
    std::vector<Position> positions;
    std::vector<Sprite> sprites;
    std::vector<EntityType> types;
};

void update_positions(std::vector<Position>& positions, std::vector<EntityType>& types) {
    for (size_t i{0}; i < positions.size(); ++i) {
        EntityType type = types[i];
        Position* pos = &positions[i];
        switch (type) {
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

void render_sprites(const std::vector<Position>& positions, const std::vector<Sprite>& sprites) {
    for (size_t i{0}; i < positions.size(); ++i) {
        printf("Rendering sprite %d at (%f, %f)\n", sprites[i].texture_id, positions[i].x, positions[i].y);
    }
}

void update_entity_position(std::vector<Position>& positions, unsigned entity_id, Position new_pos) {
    // We could have some validation logic here for example
    positions[entity_id] = new_pos;
}

[[nodiscard]] EntityData get_entity(const EntityRegistry& entities, unsigned id) {
    EntityData e;
    e.position = entities.positions[id];
    e.sprite = entities.sprites[id];
    e.type = entities.types[id];
    return e;
}

using namespace engine::ds;
int main() {
    // Testing init
    dyn_arr::DynArr<int>* xs = dyn_arr::init<int>();
    printf("xs allocated at: %p, intialized with size: %d, using %d\n", xs, xs->sza, xs->used);

    EntityRegistry registry;
    registry.positions = {{0.0f, 0.0f}, {4.0f, 5.0f}, {3.5f, 2.0f}};
    registry.sprites = {{1}, {2}, {3}};
    registry.types = {PLAYER, ENEMY_MELLE, ENEMY_RANGED};

    update_entity_position(registry.positions, 0, {10.0f, 12.0f});

    unsigned count = 3;
    while (count--) {
        update_positions(registry.positions, registry.types);
        render_sprites(registry.positions, registry.sprites);

        printf("\n");
    }

    EntityData e = get_entity(registry, 1);
    printf("Pos = (%f, %f), Sprite id = %d, Type id = %d", e.position.x, e.position.y, e.sprite.texture_id, e.type);
}