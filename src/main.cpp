#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include <array>
#include <string>

#include "GameObject.h"
#include "Animation.h"

struct SDLState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w_width, w_height, s_width, s_height;
    const bool* keys;

    SDLState() : keys(SDL_GetKeyboardState(nullptr)) {
    }
};

constexpr size_t LAYER_IDX_LEVEL = 0;
constexpr size_t LAYER_IDX_CHARACTERS = 1;

constexpr int PLAYER_WIDTH = 78;
constexpr int PLAYER_HEIGHT = 58;
constexpr int MAP_ROWS = 5;
constexpr int MAP_COLS = 50;
constexpr int TILE_SIZE = 32;


struct GameState {
    std::array<std::vector<GameObject>, 2> layers;
    int playerIndex;

    GameState() {
        playerIndex = 0;
    }
};

struct Resources {
    const int ANIM_PLAYER_IDLE = 0;
    const int ANIM_PLAYER_RUN = 1;

    std::vector<Animation*> playerAnims;

    std::vector<SDL_Texture*> textures;
    // character sprites
    SDL_Texture* idleTex,* runTex;
    // tilemap sprites
    SDL_Texture* floorTex;

    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath) {
        SDL_Texture* tex = IMG_LoadTexture(renderer, filePath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        textures.emplace_back(tex);
        return tex;
    }

    void load(SDLState& state) {
        playerAnims.resize(5);
        playerAnims[ANIM_PLAYER_IDLE] = new Animation(11, 1.6f);
        playerAnims[ANIM_PLAYER_RUN] = new Animation(8, 0.8f);

        idleTex = loadTexture(state.renderer, "data/characters/king_idle.png");
        runTex = loadTexture(state.renderer, "data/characters/king_run.png");
        floorTex = loadTexture(state.renderer, "data/tiles/floor.png");
    }

    void unload() {
        for (const Animation* anim: playerAnims) {
            delete(anim);
        }

        for (SDL_Texture* tex: textures) {
            SDL_DestroyTexture(tex);
        }
    }
};

bool initialize(SDLState& state);

void cleanup(SDLState& state);

void drawObject(const SDLState& state, GameState& gameState, const GameObject& gameObject, float deltaTime);

void update(const SDLState& state, GameState& gameState, Resources& resources, GameObject& gameObject,
            const float deltaTime);

void createTiles(const SDLState& state, GameState& gameState, const Resources& resources);

int main(int argc, char* argv[]) {
    SDLState state;
    state.w_width = 1600;
    state.w_height = 900;
    state.s_width = 640;
    state.s_height = 320;

    initialize(state);

    Resources resources;
    resources.load(state);

    GameState gameState;
    createTiles(state, gameState, resources);

    uint64_t prevTime = SDL_GetTicks();

    bool isRunning = true;
    while (isRunning) {
        uint64_t nowTime = SDL_GetTicks();
        float deltaTime = static_cast<float>(nowTime - prevTime) / SDL_MS_PER_SECOND;

        SDL_Event event{0};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    isRunning = false;
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    state.w_width = event.window.data1;
                    state.w_height = event.window.data2;
                    break;
            }
        }

        for (auto& layer: gameState.layers) {
            for (GameObject& go: layer) {
                update(state, gameState, resources, go, deltaTime);

                if (go.currentAnimation != -1) {
                    go.animations[go.currentAnimation]->step(deltaTime);
                }
            }
        }

        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);

        for (auto& layer: gameState.layers) {
            for (const GameObject& go: layer) {
                drawObject(state, gameState, go, deltaTime);
            }
        }

        SDL_RenderPresent(state.renderer);

        prevTime = nowTime;
    }

    resources.unload();
    cleanup(state);
    return 0;
}

bool initialize(SDLState& state) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to initialize SDL3", nullptr);
        return false;
    }

    state.window = SDL_CreateWindow("Honey Engine", state.w_width, state.w_height, SDL_WINDOW_RESIZABLE);
    if (!state.window) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to create window", nullptr);
        cleanup(state);
        return false;
    }

    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Failed to crate renderer", state.window);
        cleanup(state);
        return false;
    }

    SDL_SetRenderLogicalPresentation(state.renderer, state.s_width, state.s_height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return true;
}

void cleanup(SDLState& state) {
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}

void drawObject(const SDLState& state, GameState& gameState, const GameObject& gameObject, float deltaTime) {
    float srcX = gameObject.currentAnimation != -1
                     ? static_cast<float>(gameObject.animations[gameObject.currentAnimation]->getCurrentFrame()) *
                       PLAYER_WIDTH
                     : 0.f;

    SDL_FRect sRect{
        .x = srcX,
        .y = 0,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT
    };

    SDL_FRect dRect{
        .x = gameObject.position.x,
        .y = gameObject.position.y,
        .w = PLAYER_WIDTH,
        .h = PLAYER_HEIGHT
    };

    SDL_FlipMode flipMode = gameObject.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderTextureRotated(state.renderer, gameObject.texture, &sRect, &dRect, 0, nullptr, flipMode);
}

void update(const SDLState& state, GameState& gameState, Resources& resources, GameObject& gameObject,
            const float deltaTime) {
    if (gameObject.type == EObjectType::EOT_Player) {
        float curDirection = 0;
        if (state.keys[SDL_SCANCODE_A]) {
            curDirection -= 1;
        }

        if (state.keys[SDL_SCANCODE_D]) {
            curDirection += 1;
        }

        if (curDirection != 0) gameObject.direction = curDirection;

        switch (gameObject.data.player.state) {
            case EPlayerState::EPS_Idle:
                if (curDirection != 0) {
                    gameObject.data.player.state = EPlayerState::EPS_Run;
                    gameObject.texture = resources.runTex;
                    gameObject.currentAnimation = resources.ANIM_PLAYER_RUN;
                } else {
                    if (gameObject.velocity.x != 0) {
                        const float factor = gameObject.velocity.x > 0 ? -1.5f : 1.5f;
                        float amount = factor * gameObject.acceleration.x * deltaTime;
                        if (std::abs(gameObject.velocity.x) < std::abs(amount)) gameObject.velocity.x = 0.f;
                        else gameObject.velocity.x += amount;
                    }
                }
                break;
            case EPlayerState::EPS_Run:
                if (curDirection == 0) {
                    gameObject.data.player.state = EPlayerState::EPS_Idle;
                    gameObject.texture = resources.idleTex;
                    gameObject.currentAnimation = resources.ANIM_PLAYER_IDLE;
                }
                break;
            case EPlayerState::EPS_Jump:
                break;
            case EPlayerState::EPS_Crouch:
                break;
        }

        gameObject.velocity += curDirection * gameObject.acceleration * deltaTime;
        gameObject.position += gameObject.velocity * deltaTime;
    }
}

/*
 Ground Type
 1 - Ground
 2 - Panel
 3 - Enemy
 4 - Player
 5 - Grass
 6 - Brick
 */
constexpr short TILE_FLOOR = 1;
constexpr short TILE_PLAYER = 4;

void createTiles(const SDLState& state, GameState& gameState, const Resources& resources) {
    std::array<std::array<short, MAP_COLS>, MAP_ROWS> map{};
    map.back().fill(TILE_FLOOR);
    for (int i = 0; i < 2; ++i) {
        map[i].fill(TILE_FLOOR);
    }

    map[0][0] = TILE_PLAYER;

    const auto createObject = [&state](int r, int c, SDL_Texture* tex, const int tex_w, const int tex_h, EObjectType type) {
        GameObject obj;
        obj.type = type;
        obj.position = glm::vec2(c * tex_w, state.s_height - (MAP_ROWS - r) * tex_h);
        obj.texture = tex;
        return obj;
    };

    for (int r = 0; r < MAP_ROWS; ++r) {
        for (int c = 0; c < MAP_COLS; ++c) {
            switch (map[r][c]) {
                case TILE_FLOOR: {
                    GameObject floor = createObject(r, c, resources.floorTex, TILE_SIZE, TILE_SIZE, EObjectType::EOT_Level);
                    gameState.layers[LAYER_IDX_LEVEL].emplace_back(floor);
                    break;
                }
                case TILE_PLAYER: {
                    // Create a new player
                    GameObject player = createObject(r, c, resources.idleTex, PLAYER_WIDTH, PLAYER_HEIGHT, EObjectType::EOT_Player);
                    player.data.player = PlayerData();
                    player.animations = resources.playerAnims;
                    player.currentAnimation = resources.ANIM_PLAYER_IDLE;
                    player.acceleration = glm::vec2(300, 0);
                    player.maxSpeedX = 100.f;
                    gameState.layers[LAYER_IDX_CHARACTERS].emplace_back(player);
                    break;
                }
            }
        }
    }
}
