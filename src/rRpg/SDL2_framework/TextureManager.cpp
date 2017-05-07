#include "TextureManager.h"

static TextureManager* s_pInstance;

TextureManager::TextureManager() : m_textureMap({}) {}

TextureManager::~TextureManager() {
	for (auto it : m_textureMap) {
		if (it.second.texture != 0) {
			SDL_DestroyTexture(it.second.texture);
		}
	}
}

bool TextureManager::addTexture(std::string fileName, std::string id) {
	// a texture with this id already exists
	if (m_textureMap.find(id) != m_textureMap.end()) {
		return false;
	}

	S_Texture texture;
	texture.fileName = fileName;
	texture.loaded = false;
	m_textureMap[id] = texture;
	return true;
}

bool TextureManager::load(std::string id, SDL_Renderer* pRenderer) {
	auto textureIterator = m_textureMap.find(id);
	if (textureIterator == m_textureMap.end() || textureIterator->second.loaded) {
		return false;
	}

	SDL_Surface* pTempSurface = IMG_Load(
		textureIterator->second.fileName.c_str()
	);
	if (pTempSurface == 0) {
		return false;
	}

	textureIterator->second.texture = SDL_CreateTextureFromSurface(
		pRenderer,
		pTempSurface
	);

	SDL_FreeSurface(pTempSurface);
	// everything went ok, add the texture to our list
	if (textureIterator->second.texture != 0) {
		textureIterator->second.loaded = true;
		return true;
	}

	// reaching here means something went wrong
	return false;
}

bool TextureManager::load(
	std::string fileName, std::string id, SDL_Renderer* pRenderer
) {
	return addTexture(fileName, id) && load(id, pRenderer);
}

/**
 * This basically calls drawFrame with 0 and 0 as col and frame.
 */
void TextureManager::draw(
	std::string id,
	int x, int y,
	int width, int height,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip
) {
	drawFrame(id, x, y, width, height, 0, 0, pRenderer, flip);
}

void TextureManager::drawTile(
	std::string id,
	int margin, int spacing,
	int x, int y,
	int width, int height,
	int currentRow, int currentFrame,
	SDL_Renderer *pRenderer,
	SDL_RendererFlip flip
) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(
		pRenderer,
		m_textureMap[id].texture,
		&srcRect,
		&destRect,
		0, 0,
		flip
	);
}

/**
 * Renders a subsection of the texture identified by the provided id.
 */
void TextureManager::drawFrame(
	std::string id,
	int x, int y,
	int width, int height,
	int currentRow, int currentFrame,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip
) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = width;
	destRect.w = width;
	srcRect.h = height;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(
		pRenderer,
		m_textureMap[id].texture,
		&srcRect, &destRect,
		0, 0,
		flip
	);
}

/**
 * Singleton method to get the instance.
 */
TextureManager *TextureManager::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new TextureManager();
	}

	return s_pInstance;
}

void TextureManager::free() {
	delete s_pInstance;
	s_pInstance = 0;
}

void TextureManager::clearFromTextureMap(const char* id) {
	m_textureMap.erase(id);
}
