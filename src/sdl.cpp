//sdl.cpp

#include <iostream>
#include "primer.h"
#include "sdl.h"
#include <SDL2/SDL.h>

std::string getResourcePath(const std::string &subDir = ""){

/* Define path separator for current machine */

#ifdef _WIN32
	const char PATH_SEP = '\\';
#else 
	const char PATH_SEP = '/';
#endif
	static std::string baseRes;
	if(baseRes.empty())
	{
		char *basePath = SDL_GetBasePath();
		if(basePath)
		{
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}

		size_t pos = baseRes.rfind("source");
		baseRes = baseRes.substr(0, pos) + "resources" + PATH_SEP;
	}

	return subDir.empty() ? baseRes : baseRes + PATH_SEP;
}

/* Log an SDL error with some error message to the output stream of our choice
   @param outputStream The output stream to write the message to
   @param message The error message to write, format will be message error: SDL_GetError()
*/

void logSDLError(std::ostream &outputStream, const std::string &message){
	outputStream << message << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer){
	//Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//If the loading went ok, convert to texture and return the texture
	if(loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if(texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

/*
	Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
	the texture's width and height
	@param texture The source texture we want to draw
	@param renderer The renderer we want to draw to
	@param x The x coordinate to draw to
	@param y The y coordinate to draw to
*/

void renderTexture(SDL_Texture *texture, SDL_Renderer *renderer, int x, int y){
	//Setup the destination rectangle to be at position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, texture, NULL, &dst);
}
