#include "game.h"

Game::Game(Window* const wnd) : wnd(wnd) {

	//Init Opengl state
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	// The Type Of Depth Testing To Do

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	kbd = new Keyboard(wnd->getWindow());
	mse = new Mouse(wnd->getWindow());

	//Init camera
	camera = new Camera(kbd, 0.0f, 1.0f, 5.5f, 0.0f, 0.0f, 0.0f, 3.0f);

	camera->gProjectionMatrix = Matrix4::perspective(60.0f, wnd->getWindowRatio(), 0.5f, 400.0f);
	//camera->gProjectionMatrix = Matrix4::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.5f, 30.0f); //left, right, bottom, top, near, far

	session = nullptr;

	sessionState = PATH_FINDING;

	initSessionState();

}

Game::~Game() {

	delete session;
	session = nullptr;

	delete camera;
	camera = nullptr;

	delete mse;
	mse = nullptr;

	delete kbd;
	kbd = nullptr;

}

void Game::initSessionState() {

	if (session != nullptr) {
		delete session;
		session = nullptr;
	}

	switch (sessionState) {

		case GAME_OF_LIFE:
			session = new GameOfLife_Demo(wnd, kbd, mse, camera);
			break;

		case PATH_FINDING:
			session = new PathFinding_Demo(wnd, kbd, mse, camera);
			break;

		case STEERING_BEHAVIOUR:
			session = new SteeringBehaviour_Demo(wnd, kbd, mse, camera);
			break;

	}

}

void Game::gameLoop() {

	mse->update();
	kbd->update();

	camera->update();

	session->update();

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}