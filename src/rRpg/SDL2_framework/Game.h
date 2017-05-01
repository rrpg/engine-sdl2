#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <vector>
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include <string>

class Game {
	private:
	/**
	 * Path to the game binary
	 */
	std::string m_sBinaryPath = "";

	/**
	 * flag to know if the game is running
	 */
	bool m_bRunning = false;

	/**
	 * flag to know if the game needs a joystick to be played
	 */
	bool m_bNeedsJoystick = false;

	/**
	 * The game's window
	 */
	SDL_Window* m_window = 0;

	/**
	 * The game's renderer. Used to render graphics in the window
	 */
	SDL_Renderer* m_renderer = 0;

	/**
	 * List of files to use as graphic resources, each file is a pair composed
	 * of a resource name and of the file path.
	 */
	std::vector<std::pair<std::string, std::string>> m_vResourceFiles = {};

	/**
	 * Number of resources used by the game
	 */
	unsigned long m_iNbFiles = 0;

	GameStateMachine* m_gameStateMachine = 0;

	/**
	 * Dimensions of the screen
	 */
	int m_iScreenWidth = 0;
	int m_iScreenHeight = 0;

	/**
	 * The game is a singleton, so its constructor and destructor are private
	 */
	Game();
	~Game();

	/**
	 * Method to initialise the SDL. It takes in arguments the window's title,
	 * its position and dimensions, and a boolean to create it full screen or
	 * not.
	 */
	bool _initSDL(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		const bool fullScreen
	);

	/**
	 * Method to load the game's resources.
	 */
	bool _loadResources();

	/**
	 * Method to free the game's resources.
	 */
	void _cleanResources();

	/**
	 * Method to initialise the state machine.
	 */
	void _initGameMachine();

	/**
	 * Method to free the state machine.
	 */
	void _cleanGameMachine();

	/**
	 * Method to free the user actions.
	 */
	void _cleanUserActions();

	/**
	 * Set the mapping of actions of the user
	 */
	bool _initServiceProvider();


	public:
	/**
	 * Because of the singleton, the following construct and operator are
	 * removed.
	 */
	Game(Game const&) = delete;
	void operator=(Game const&) = delete;

	/**
	 * Method to get the game instance.
	 */
	static Game* Instance();

	/**
	 * Method to set the path to the game binary
	 */
	void setBinaryPath(std::string binaryPath);

	/**
	 * Method to set the path to the game binary
	 */
	std::string getBinaryPath();

	/**
	 * Method used to clean the memory used by the game before quitting the
	 * game.
	 */
	static void freeGame();

	/**
	 * First method to be called when starting the game
	 * Initialises the game environment. It takes in arguments the
	 * window's title, its position and dimensions, and a boolean to create it
	 * full screen or not.
	 *
	 * Returns true if the game is correctly initialised.
	 */
	bool init(
		const char* title,
		const int x,
		const int y,
		const int w,
		const int h,
		bool fullScreen
	);

	/**
	 * Method called to handle the events captured by the game during each
	 * loop.
	 */
	InputUpdateResult handleEvents();

	/**
	 * Method to update the game during each game loop.
	 */
	void update();

	/**
	 * Method to render the game during each game loop.
	 */
	void render();

	/**
	 * Method to clean the game before quitting.
	 */
	void clean();

	/**
	 * Returns true if the game is running, false otherwise.
	 */
	bool isRunning();

	/**
	 * Method to get the game's renderer. Called by any graphics having to be
	 * rendered.
	 */
	SDL_Renderer* getRenderer();

	/**
	 * Method to quit the game.
	 */
	void quit();

	/**
	 * Getter for the state machine.
	 */
	GameStateMachine* getStateMachine();

	/**
	 * Getters for the screen dimensions
	 */
	int getScreenWidth();
	int getScreenHeight();

	void addResource(std::string resourceName, std::string resourcePath);
};

#endif /* defined(__Game__) */
