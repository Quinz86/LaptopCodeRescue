#pragma once
#define DIR "Assets/Textures/"

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <unordered_map>

class TextureManager {
public:
	TextureManager(SDL_Renderer* rn);
	~TextureManager();

	void myTextureLoad(std::string path);
	SDL_Texture* myTextureGet(std::string nam);
private:
	SDL_Renderer* r;
	std::unordered_map<std::string, SDL_Texture*> allTextures;
};