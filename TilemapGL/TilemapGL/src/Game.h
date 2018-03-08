/*******************************************************************
** Some tilemap bullshit.
**
** again.
******************************************************************/
#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "GameLevel.h"
#include "InputHandler.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLuint                 Width, Height;
	InputHandler		   *input;
	GLboolean			   playerTurn;
	GLfloat				   turnTimer = 0;
	GLfloat				   turnDelay = 30;
	GameLevel			   *Levels[2];
	GLuint				   currentLevel;

	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();

	// Initialize game state (load all shaders/textures/levels)
	void Init();

	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void ResetLevel();

private:
	//GLboolean playerTurn = true;
	void LoadLevel(const GLuint level);
};
#endif