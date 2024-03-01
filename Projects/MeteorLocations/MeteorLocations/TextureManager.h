#pragma once
#define TEXDIR "Assets/Textures/"

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <unordered_map>

class TextureManager {
public:
	static void setUp(SDL_Renderer* rn);
	static void cleanUp();

	static void myTextureLoad(std::string path);
	static SDL_Texture* myTextureGet(std::string nam);
private:
	static SDL_Renderer* r;
	static std::unordered_map<std::string, SDL_Texture*> allTextures;
};