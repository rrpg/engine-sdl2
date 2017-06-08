#include "Game.h"
#include "NoJoystickState.h"
#include "ServiceProvider.h"
#include <iostream>
#include <errno.h>

static Game* s_pInstance;

Game::Game() {
}

/**
 * Game destructor, cleans the InputHandler, the resources, the state machine
 * and stops the SDL.
 */
Game::~Game() {
	InputHandler::Instance()->clean();
	InputHandler::free();
	_cleanResources();
	TextureManager::free();
	_cleanGameMachine();
	ServiceProvider::clean();
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

/**
 * Classic singleton method to get the Game instance.
 */
Game *Game::Instance() {
	if (s_pInstance == 0) {
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::setBinaryPath(std::string binaryPath) {
	m_sBinaryPath = binaryPath;
}

std::string Game::getBinaryPath() {
	return m_sBinaryPath;
}

/**
 * Deletes the game instance.
 */
void Game::freeGame() {
	delete s_pInstance;
	s_pInstance = 0;
}

/**
 * Initialises the SDL, loads the resources and initialises the State machine.
 * Then sets te m_bRunning flag to true.
 */
bool Game::init(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool l_bReturn = false;
	if (_initSDL(title, x, y, w, h, fullScreen)
		&& _loadResources()
		&& _initServiceProvider()
	) {
		m_iScreenWidth = w;
		m_iScreenHeight = h;
		_initGameMachine();
		l_bReturn = true;
		m_bRunning = true;
	}

	return l_bReturn;
}

/**
 * Classic SDL initialisation.
 */
bool Game::_initSDL(
	const char* title,
	const int x,
	const int y,
	const int w,
	const int h,
	const bool fullScreen
) {
	bool l_bReturn = true;
	Uint32 flags = 0;

	if (fullScreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL Init failed\n";
		l_bReturn = false;
	}
	else {
		// if succeeded create our window
		m_window = SDL_CreateWindow(title, x, y, w, h, flags);
		// if the window creation succeeded create our renderer
		if (m_window == 0) {
			std::cout << "Window creation failed\n";
			l_bReturn = false;
		}
		else {
			m_renderer = SDL_CreateRenderer(m_window, -1, 0);
			if (m_renderer == 0) {
				std::cout << "Renderer creation failed\n";
				l_bReturn = false;
			}
		}
	}

	return l_bReturn;
}

/**
 * Loads each resource. Returns false if a resource is failed to be loaded (for
 * example if the file does not exist or is not readable).
 */
bool Game::_loadResources() {
	const char errorPattern[] = "An error occured while loading the file %s";

	bool ret = true;
	std::cout << "Load resources \n";
	for (unsigned long i = 0; i < m_iNbFiles; ++i) {
		char* errorMessage = (char*) calloc(
			strlen(errorPattern) + m_vResourceFiles[i].second.length(), sizeof(char)
		);
		std::cout << "Load resource " << m_vResourceFiles[i].second << "\n";
		bool textureLoaded = TextureManager::Instance()->load(
			m_vResourceFiles[i].second,
			m_vResourceFiles[i].first,
			m_renderer
		);

		if (!textureLoaded) {
			sprintf(errorMessage, errorPattern, m_vResourceFiles[i].second.c_str());
			std::cout << errorMessage << "\n";
			std::cout << strerror(errno) << "\n";
			ret = false;
		}
		else {
			std::cout << "Resource " << m_vResourceFiles[i].second << " loaded\n";
		}
		free(errorMessage);
	}

	return ret;
}

/**
 * Initialises the State machine and sets the MainMenu state as initial state.
 */
void Game::_initGameMachine() {
	m_gameStateMachine = new GameStateMachine();
}

/**
 * Update the input handler, if the update returns false, the game stops
 * running.
 */
InputUpdateResult Game::handleEvents() {

	InputUpdateResult result = InputHandler::Instance()->update();
	if (result == QUIT) {
		m_bRunning = false;
	}

	return result;
}

/**
 * Method to be called at each game loop, if no joystick is detected, the state
 * NoJoystickState is pushed, until a joystick is plugged.
 * The state machines updates its current state.
 */
void Game::update() {
	// @TODO force or not the joystick from config value
	if (m_bNeedsJoystick && !InputHandler::Instance()->joysticksInitialised()) {
		m_gameStateMachine->pushState(new NoJoystickState());
	}

	m_gameStateMachine->update();
}

/**
 * Method to be called at each game loop. Renders the current state.
 */
void Game::render() {
	// set to black
	// This function expects Red, Green, Blue and
	// Alpha as color values
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	// clear the window to black
	SDL_RenderClear(m_renderer);

	m_gameStateMachine->render();
	// show the window
	SDL_RenderPresent(m_renderer);
}

void Game::_cleanGameMachine() {
	m_gameStateMachine->clean();
	delete m_gameStateMachine;
	m_gameStateMachine = NULL;
}

/**
 * Clean every resources.
 */
void Game::_cleanResources() {
	std::cout << "Clean resources\n";
	for (unsigned long i = 0; i < m_iNbFiles; ++i) {
		std::cout << "Clean resource " << m_vResourceFiles[i].second << "\n";
		TextureManager::Instance()->clearFromTextureMap(m_vResourceFiles[i].first.c_str());
	}
}

bool Game::isRunning() {
	return m_bRunning;
}

SDL_Renderer* Game::getRenderer() {
	return m_renderer;
}

/**
 * Set running to false, which then will stop the game loop.
 */
void Game::quit() {
	m_bRunning = false;
}

GameStateMachine* Game::getStateMachine() {
	return m_gameStateMachine;
}

int Game::getScreenWidth() {
	return m_iScreenWidth;
}

int Game::getScreenHeight() {
	return m_iScreenHeight;
}

bool Game::_initServiceProvider() {
	bool ret = true;
	std::string mappingFile = m_sBinaryPath + "/../configs/playercontrolsmapping.txt";
	int userActionsParsed = ServiceProvider::setUserActions(mappingFile.c_str());
	if (userActionsParsed != 0) {
		std::cerr << "The parsing of the user actions failed, returned "
			<< userActionsParsed << std::endl;
		ret = false;
	}

	return ret;
}

void Game::addResource(std::string resourceName, std::string resourcePath) {
	m_vResourceFiles.push_back(std::make_pair(resourceName, resourcePath));
	m_iNbFiles = m_vResourceFiles.size();
}
