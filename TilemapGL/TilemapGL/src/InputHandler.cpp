#include "InputHandler.h"

InputHandler::InputHandler(Entity *e) {
	buttonW = new MoveCommand(e, 0, -1);
	buttonA = new MoveCommand(e, -1, 0);
	buttonS = new MoveCommand(e, 0, 1);
	buttonD = new MoveCommand(e, 1, 0);
}


InputHandler::~InputHandler() {
}

Command* InputHandler::HandleInput() {
	glfwPollEvents();

	if (this->Keys[GLFW_KEY_W]) { 
		lastCommand = buttonW; 
		return buttonW; 
	}
	if (this->Keys[GLFW_KEY_A]) {
		lastCommand = buttonA;
		return buttonA;
	}
	if (this->Keys[GLFW_KEY_S]) {
		lastCommand = buttonS;
		return buttonS;
	}
	if (this->Keys[GLFW_KEY_D]) {
		lastCommand = buttonD;
		return buttonD;
	}

	if (this->Keys[GLFW_KEY_LEFT_CONTROL] && this->Keys[GLFW_KEY_Z]) {
		lastCommand->undoMode = true;
		return lastCommand;
	}
	// Nothing pressed, so do nothing.
	return NULL;
}