/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Entity.h"

Entity::Entity()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) { }

Entity::Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) { }

void Entity::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void Entity::MoveTo(GLint x, GLint y) {
	//move to new position (tile or world pos?)
	this->Position = glm::vec2(this->Position.x + (x * 64), this->Position.y + (y * 64));//(x * this->Size.x), this->Position.y + (y * this->Size.y));
}

GLboolean Entity::Check(GLint x, GLint y) {
	if(!Game::Levels[Game::currentLevel]->SolidAt(glm::vec2(this->Position.x + (x * 64), this->Position.y + (y * 64)))) {
		this->MoveTo(x, y);
	}
	return GL_FALSE;
}