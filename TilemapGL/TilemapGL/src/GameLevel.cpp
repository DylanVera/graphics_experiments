/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "GameLevel.h"

#include <fstream>
#include <sstream>

GameLevel::GameLevel(const GLchar* file) {
	this->filePath = file;
}

void GameLevel::Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight)
{
	// Clear old data
	this->Bricks.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Load()
{
	// Clear old data
	this->Bricks.clear();
	// Load from file
	GLuint tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(this->filePath);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{

			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
			{
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			this->init(tileData, tileData[0].size() * 64, tileData.size() * 64);
	}
}

void GameLevel::Draw(SpriteRenderer &renderer)
{
	for (Entity &tile : this->Bricks)
		if (!tile.Destroyed)
			tile.Draw(renderer);
}

GLboolean GameLevel::IsCompleted()
{
	for (Entity &tile : this->Bricks)
		if (!tile.IsSolid && !tile.Destroyed)
			return GL_FALSE;
	return GL_TRUE;
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight)
{
	// Calculate dimensions
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width), unit_height = levelHeight / height;
	glm::vec2 size(unit_width, unit_height);
	glm::vec2 offset((800 - levelWidth) / 2, (600 - levelHeight) / 2);
	glm::vec3 color = glm::vec3(1.0f);

	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y) {
		for (GLuint x = 0; x < width; ++x) {
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 1)  {	// Solid
				glm::vec2 pos(unit_width * x, unit_height * y);
				
				Entity obj(pos + offset, size, ResourceManager::GetTexture("floor_tile"), color);
				obj.IsSolid = GL_TRUE;

				this->Bricks.push_back(obj);
			}
			else {
				glm::vec2 pos(unit_width * x, unit_height * y);

				if (tileData[y][x] == 2)
					this->SpawnPoint = pos + offset;
				
				this->Bricks.push_back(Entity(pos + offset, size, ResourceManager::GetTexture("floor_tile"), color));
			}
		}
	}
}

glm::vec2 GameLevel::GetSpawn() {
	return this->SpawnPoint;
}


GLboolean GameLevel::SolidAt(glm::vec2 pos) {
	//world pos to tile index
	//chek solid flag at index
	GLuint index = WorldToTileIndex(pos);
	return this->Bricks.at(index).IsSolid;
}

GLuint GameLevel::WorldToTileIndex(glm::vec2 pos) {
	for (Entity& obj : this->Bricks) {
		
	}
	return 0;
}

glm::vec2 GameLevel::TileToWorldPos(glm::vec2 pos) {
	return glm::vec2(0);
}