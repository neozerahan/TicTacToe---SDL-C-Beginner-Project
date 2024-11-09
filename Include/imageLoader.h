#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_image.h"

int LoadSpriteSheetTexture(SDL_Texture **texture, SDL_Renderer *screenRenderer, const char * filePath);

#endif
