#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player
{
public:
	Player();
	~Player();
	Entity *entity;
	GLuint actionPoints;

};
#endif
