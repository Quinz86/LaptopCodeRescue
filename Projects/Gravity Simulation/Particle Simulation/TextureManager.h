#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <unordered_map>

#define DIR "Assets/Textures/"

class TextureManager {
public:
	static void setUp(SDL_Renderer* r);
	static void cleanUp();

	static SDL_Texture* myTextureGet(std::string nam);
private:
	static void myTextureLoad(std::string path);

	static SDL_Renderer* rend;
	static std::unordered_map<std::string, SDL_Texture*> allTextures;
};