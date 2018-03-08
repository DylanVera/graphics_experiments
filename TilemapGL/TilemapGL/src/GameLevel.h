/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Entity.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

/// GameLevel holds all Tiles as part of a tilemap
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
	// Level state
	std::vector<Entity> Bricks;
	// Constructor
	GameLevel() {}
	GameLevel(const GLchar* file);

	// Loads level from file
	void	  Load();
	void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
	
	// Render level
	void      Draw(SpriteRenderer &renderer);
	// Check if the level is completed (all non-solid tiles are destroyed)
	GLboolean IsCompleted();
	GLboolean SolidAt(glm::vec2 pos);
	GLuint WorldToTileIndex(glm::vec2 pos);
	glm::vec2 TileToWorldPos(glm::vec2 pos);
	glm::vec2 GetSpawn();
	

private:
	// Initialize level from tile data
	const GLchar*	filePath;
	glm::vec2 SpawnPoint;
	void      init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};
#endif