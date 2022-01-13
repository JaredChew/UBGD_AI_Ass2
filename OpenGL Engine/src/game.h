#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "window.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "session.h"

#include "Session/gameOfLife.h"
#include "Session/pathFinding.h"
#include "Session/steeringBehaviour.h"

#define GAME_OF_LIFE 0
#define PATH_FINDING 1
#define STEERING_BEHAVIOUR 2

class Game {

private:

	Window* const wnd;

private:

	Keyboard* kbd;
	Mouse* mse;

	Camera* camera;

	Session *session;

	int sessionState;

public:
	Game(Window* const window);
	~Game();

	void initSessionState();

	void gameLoop();

};