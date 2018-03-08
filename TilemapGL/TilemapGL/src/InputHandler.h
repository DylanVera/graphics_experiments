#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include "Command.h"
#include "Entity.h"

class InputHandler
{
public:
	InputHandler(Entity *e);
	~InputHandler();
	Command* HandleInput();
	GLboolean Keys[1024];
	// Methods to bind commands...

private:	
	Command* buttonW;
	Command* buttonA;
	Command* buttonS;
	Command* buttonD;
	Command* lastCommand;
};

class MoveCommand : public Command {
public:
	MoveCommand(Entity *e, int dx, int dy) {
		entity = e;
		x = dx;
		y = dy;
		oldX = -dx;
		oldY = -dy;
	}

	~MoveCommand() {
		delete entity;
	}

	virtual void execute() {
		printf("MOVE: %d, %d\n", x, y);
		entity->MoveTo(x, y);
	}

	virtual void undo() {
		printf("UNDO: %d, %d\n", oldX, oldY);
		this->undoMode = false;
		entity->MoveTo(oldX, oldY);
	}
private:
	Entity	*entity;
	int x, y, oldX, oldY;
};
#endif