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
};

constexpr size_t LAYER_IDX_LEVEL = 0;
constexpr size_t LAYER_IDX_CHARACTERS = 1;

struct GameState {
    std::array<std::vector<GameObject>, 2> layers;
    int playerIndex;

    GameState()
    {
        playerIndex = 0;
    }
};

struct Resources {
    const int ANIM_PLAYER_IDLE = 0;

    std::vector<Animation*> playerAnims;

    std::vector<SDL_Texture*> textures;
    SDL_Texture* idleTex;

    SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filePath)
    {
        SDL_Texture* tex = IMG_LoadTexture(renderer, filePath.c_str());
        SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
        textures.emplace_back(tex);
        return tex;
    }

    void load(SDLState& state)
    {
        playerAnims.resize(11);
        playerAnims[ANIM_PLAYER_IDLE] = new Animation(11, 1.6f);

        idleTex = loadTexture(state.renderer, "data/king_idle.png");
    }

    void unload()
    {
        for (const Animation* anim : playerAnims) {
            delete(anim);
        }

        for (SDL_Texture* tex : textures) {
            SDL_DestroyTexture(tex);
        }
    }
};

bool initialize(SDLState& state);
void cleanup(SDLState& state);
void drawObject(const SDLState& state, GameState& gameState, const GameObject& gameObject, float deltaTime);

int main(int argc, char* argv[]) {
    SDLState state;
    state.w_width = 1600;
    state.w_height = 900;
    state.s_width = 640;
    state.s_height = 320;

    initialize(state);

    Resources res;
    res.load(state);

    GameState gameState;
    GameObject playerGO;
    playerGO.type = ObjectType::EOT_Player;
    playerGO.texture = res.idleTex;
    playerGO.animations = res.playerAnims;
    playerGO.currentAnimation = res.ANIM_PLAYER_IDLE;

    gameState.layers[LAYER_IDX_CHARACTERS].emplace_back(playerGO);

    const bool* keys = SDL_GetKeyboardState(nullptr);
    uint64_t prevTime = SDL_GetTicks();

    bool isRunning = true;
    while (isRunning) {
        uint64_t nowTime = SDL_GetTicks();
        float deltaTime = (nowTime - prevTime) / 1000.f;

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

        for (auto& layer : gameState.layers) {
            for (const GameObject& go : layer) {
                if (go.currentAnimation != -1) {
                    go.animations[go.currentAnimation]->step(deltaTime);
                }
            }
        }

        SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
        SDL_RenderClear(state.renderer);

        for (auto& layer : gameState.layers) {
            for (const GameObject& go : layer) {
                drawObject(state, gameState, go, deltaTime);
            }
        }

        SDL_RenderPresent(state.renderer);

        prevTime = nowTime;
    }

    res.unload();
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

void drawObject(const SDLState& state, GameState& gameState, const GameObject& gameObject, float deltaTime)
{
    const float spriteX = 78;
    const float spriteY = 58;

    float srcX = gameObject.currentAnimation != -1 ?
        static_cast<float>(gameObject.animations[gameObject.currentAnimation]->getCurrentFrame()) * spriteX : 0.f;

    SDL_FRect sRect{
        .x = srcX,
        .y = 0,
        .w = spriteX,
        .h = spriteY
    };

    SDL_FRect dRect{
        .x = gameObject.position.x,
        .y = gameObject.position.y,
        .w = spriteX,
        .h = spriteY
    };

    SDL_FlipMode flipMode = gameObject.direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderTextureRotated(state.renderer, gameObject.texture, &sRect, &dRect, 0, nullptr, flipMode);
}