/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"


class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRenderer(Shader &shader);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(32, 32), glm::vec2 dest = glm::vec2(0, 0), glm::vec2 destSize = glm::vec2(16, 16), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void DrawSprites(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), GLuint count = 1);
	void DrawSprites(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(32, 32), glm::vec2 dest = glm::vec2(0, 0), glm::vec2 destSize = glm::vec2(16, 16), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), GLuint count = 1);
	void DrawMap(Texture2D &texture, glm::vec2 position, glm::vec2 boardSize = glm::vec2(10,8));
private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};
#endif