#pragma once

#include <SDL2/SDL.h>
#include <asmodean.h>

#include <string>
#include <cstring>
#include <iostream>
#include <map>
#include <utility>

#include <hgdecoder.hpp>

#define IMAGE_PATH "image/"
#define IMAGE_EXT ".hg3"
#define IMAGE_SIGNATURE "HG-3"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

#define Z_INDEX_MAX 10

enum class IMAGE_TYPE
{
    IMAGE_EG,
    IMAGE_BG,
    IMAGE_CG,
};

typedef struct
{
    int xShift;
    int yShift;
    std::vector<std::string> names;
} ImageData;

typedef std::pair<SDL_Texture *, Stdinfo> TextureData;

class ImageManager
{

public:
    ImageManager();

    void setImage(IMAGE_TYPE, int, std::string, int, int);

    void clearAllImage(IMAGE_TYPE);

    void clearZIndex(IMAGE_TYPE, int);

private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    ImageData currSprites[Z_INDEX_MAX];
    ImageData currBgs[Z_INDEX_MAX];
    ImageData currEgs[Z_INDEX_MAX];

    std::map<std::string, TextureData> textureDataCache;

    SDL_Texture *getTextureFromFrame(HGDecoder::Frame);

    void renderTexture(SDL_Texture *, int, int);

    void processImage(byte *, size_t, std::string);

    void displayImage(ImageData);

    void displayAll();
};
