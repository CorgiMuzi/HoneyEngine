#pragma once
#include <string>
#include <memory>
#include <SDL3/SDL.h>

struct SDLTextureDeleter {
    void operator()(SDL_Texture* texture) const {
        if (texture) {
            SDL_DestroyTexture(texture);
        }
    }
};

class Resourcemanager;

class Resource {
public:
    explicit Resource(const std::string& filePath) : filePath(filePath), baseTexture(nullptr) {
    }

protected:
    friend class ResourceManager;

    void setTexture(std::shared_ptr<SDL_Texture> texture) { baseTexture = texture; }
    std::string filePath;
    std::shared_ptr<SDL_Texture> baseTexture;

public:
    std::string getFilePath() const { return filePath; }
    std::shared_ptr<SDL_Texture> getBaseTexture() const { return baseTexture; }
};
