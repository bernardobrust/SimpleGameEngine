import <cstdio>;
import <vector>;

// We could also have speeds, but this is just for testing
struct Position { float x, y; };
struct Sprite { unsigned textureId; };

enum EntityType {
    PLAYER,
    ENEMY_MELLE,
    ENEMY_RANGED,
};

// Paralel vectors
struct EntityRegistry {
    std::vector<Position> positions;
    std::vector<Sprite> sprites;
    std::vector<EntityType> types;
};

void update_positions(std::vector<Position>& positions, std::vector<EntityType>& types) {
    for (unsigned i{0}; i < positions.size(); ++i) {
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
        printf("Rendering sprite %d at (%f, %f)\n", sprites[i].textureId, positions[i].x, positions[i].y);
    }
}

void update_entity_position(std::vector<Position>& positions, unsigned entity_id, Position new_pos) {
    // We could have some validation logic here for example
    positions[entity_id] = new_pos;
}

int main() {
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
}