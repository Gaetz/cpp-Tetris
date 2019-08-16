#include <glm/gtc/matrix_transform.hpp>

#include "game.h"
#include "resource_manager.h"
#include "gamestate.h"
#include "../game/gamestate_main.h"

Game::Game() : isRunning(false),
			   windowWidth(0),
			   windowHeight(0)
{
}

Game::~Game()
{
}

void Game::init(int screenWidth, int screenHeight)
{
	windowWidth = screenWidth;
	windowHeight = screenHeight;
	isRunning = true;

	inputManager = std::make_unique<InputManager>();
}

void Game::load()
{
	// Load shaders
	ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
	ResourceManager::loadShader("assets/shaders/rect.vert", "assets/shaders/rect.frag", "", "rect");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use();
	ResourceManager::getShader("sprite").setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);
	ResourceManager::getShader("rect").use();
	ResourceManager::getShader("rect").setMatrix4("projection", projection);
	// Set render-specific controls
	sRenderer = std::make_shared<SpriteRenderer>(ResourceManager::getShader("sprite"));
	gRenderer = std::make_shared<GeometryRenderer>(ResourceManager::getShader("rect"));

	// Game state
	changeState(std::make_unique<GameStateMain>(sRenderer, gRenderer));
}

void Game::handleInputs()
{
	inputManager->prepareForUpdate();
	isRunning = inputManager->pollInputs();
	const InputState& inputState = inputManager->getState();
	gameStates.back()->handleEvent(inputState);
}

void Game::update(unsigned int dt)
{
	gameStates.back()->update(dt);
}

void Game::render()
{
	gameStates.back()->draw();
}

void Game::clean()
{
	ResourceManager::clear();
}

void Game::changeState(std::unique_ptr<GameState> state)
{
	// cleanup the current state
	if (!gameStates.empty())
	{
		gameStates.back()->clean();
		gameStates.pop_back();
	}

	// store and load the new state
	state->setGame(this);
	gameStates.push_back(std::move(state));
	gameStates.back()->load();
}

void Game::pushState(std::unique_ptr<GameState> state)
{
	// pause current state
	if (!gameStates.empty())
	{
		gameStates.back()->pause();
	}

	// store and init the new state
	gameStates.push_back(std::move(state));
	gameStates.back()->load();
}

void Game::popState()
{
	// cleanup the current state
	if (!gameStates.empty())
	{
		gameStates.back()->clean();
		gameStates.pop_back();
	}

	// resume previous state
	if (!gameStates.empty())
	{
		gameStates.back()->resume();
	}
}