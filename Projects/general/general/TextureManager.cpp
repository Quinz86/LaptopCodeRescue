#include "TextureManager.h"

//constructor
TextureManager::TextureManager(SDL_Renderer* rn) {
	r = rn;
	myTextureLoad("DefaultTexture.png");
}
TextureManager::~TextureManager() {
	for (const auto& n : allTextures) { //got this from a page, not sure how it works
		SDL_DestroyTexture(n.second); //second means not the key, the entry
	}
}

//other
void TextureManager::myTextureLoad(std::string path) {
	//std::string dir = "Assets/Textures/";
	SDL_Surface* surf;
	std::string fnal = DIR + path;

	surf = IMG_Load(fnal.c_str());
	SDL_Texture* tex = SDL_CreateTextureFromSurface(r, surf);
	if (!surf || tex == NULL) {
		allTextures[path] = allTextures["DefaultTexture.png"];
	}else{
		allTextures[path] = tex;
	}

	SDL_FreeSurface(surf);
}
SDL_Texture* TextureManager::myTextureGet(std::string nam) {
	try {
		return allTextures.at(nam);
	}catch (std::out_of_range e) {
		myTextureLoad(nam);
		return allTextures.at(nam);
	}

	/*if(allTextures.find(nam) == allTextures.end()){
		//load the chosen name into the unorderered map bc not found
		myTextureLoad(nam);
	}
	return allTextures.at(nam);
	*/
}