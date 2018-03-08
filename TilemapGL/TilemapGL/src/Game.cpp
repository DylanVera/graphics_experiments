/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Entity.h"

// Game-related State data
SpriteRenderer  *Renderer;
Entity			*Player;


			
Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	currentLevel = 0;
	// Load shaders
	ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection); 

	// Load textures
	ResourceManager::LoadTexture("textures/RageBaby.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("textures/8x.png", GL_TRUE, "tiles");
	//ResourceManager::LoadTexture("textures/wall.png", GL_TRUE, "wall_tile");
	ResourceManager::LoadTexture("textures/floor.png", GL_TRUE, "floor_tile");
	ResourceManager::LoadTexture("textures/block.png", GL_TRUE, "block");

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	Levels[0] = new GameLevel("levels/one.lvl");
	LoadLevel(currentLevel);

	//Entities
	Player = new Entity(Levels[currentLevel]->GetSpawn(), glm::vec2(64, 64), ResourceManager::GetTexture("face"));
	input = new InputHandler(Player);
}

//TODO: event queue
void Game::Update(GLfloat dt)
{
	if (!playerTurn && turnTimer > turnDelay) {
		playerTurn = true;
	}

	turnTimer++;
}

void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_ACTIVE)
	{
		Command *command = input->HandleInput();
		if (command && playerTurn) {
			if (command->undoMode) {
				command->undoMode = false;
				command->undo();			
			}
			else {
				command->execute();
			}			
			playerTurn = false;
			turnTimer = 0;
		}
	}
}

void Game::Render()
{
	Levels[currentLevel]->Draw(*Renderer);
	Player->Draw(*Renderer);
	//Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Game::ResetLevel() {
	//load current level
}

void Game::LoadLevel(const GLuint level) {
	currentLevel = level;
	Levels[currentLevel]->Load();
}