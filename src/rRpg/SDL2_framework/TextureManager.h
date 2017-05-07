#ifndef __TextureManager__
#define __TextureManager__

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct S_Texture {
	SDL_Texture* texture = 0;
	std::string fileName = "";
	bool loaded = false;
};

class TextureManager {
	private:
	/**
	 * All the textures are stored in this map.
	 */
	std::unordered_map<std::string, S_Texture> m_textureMap;

	/**
	 * Private constructor for singleton
	 */
	TextureManager();
	~TextureManager();

	public:
	/**
	 * Deleted for singleton
	 */
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

	/**
	 * Adds a texture to be loaded later on.
	 */
	bool addTexture(std::string fileName, std::string id);
	bool load(std::string id, SDL_Renderer* pRenderer);

	/**
	 * Method to load a texture, takes in arguments the file name, the texture
	 * id and the renderer to use to render the texture.
	 */
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	/**
	 * Draws a whole texture.
	 * A flip flag can be provided as last argument, to flip horizontally or
	 * vertically the texture.
	 */
	void draw(
		std::string id,
		int x, int y,
		int width, int height,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE
	);

	/**
	 * Draws a tile from a tileset.
	 */
	void drawTile(
		std::string id,
		int margin, int spacing,
		int x, int y,
		int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE
	);

	/**
	 * Draws a frame from a texture. A framed texture is considered as a grid,
	 * a currentRow and currentFrame integers are expected to find which frame
	 * of the texture to draw.
	 * A flip flag can be provided as last argument, to flip horizontally or
	 * vertically the texture.
	 */
	void drawFrame(
		std::string id,
		int x, int y,
		int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE
	);

	static TextureManager* Instance();
	static void free();

	/**
	 * Delete off the memory a texture identified by the provided id.
	 */
	void clearFromTextureMap(const char* id);
};

#endif /* defined(__TextureManager__) */
