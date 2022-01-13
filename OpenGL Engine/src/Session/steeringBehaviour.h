#pragma once

#include <chrono>
#include <vector>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../External/Matrix.h"

#include "../window.h"
#include "../camera.h"
#include "../opengl.h"
#include "../objects.h"
#include "../defaultSettings.h"
#include "../keyboard.h"
#include "../mouse.h"
#include "../session.h"
#include "../shader.h"
#include "../sprite.h"
#include "../vector.h"

#include "../Modules/pathNode.h"
#include "../Modules/dijkstra.h"
#include "../Modules/aStar.h"
#include "../Modules/pathFinder.h"

#include "../Utilities/timer.h"

struct Fish {

	//acceleration magnitude must be constant

};

class SteeringBehaviour_Demo : public Session {

private:

	Window* const wnd;
	Keyboard* const kbd;
	Mouse* const mse;
	Camera* const camera;

private:

	GLuint backBuffer;

	Sprite* sprite;

	Matrix4 modelMatrix;
	Matrix4 mvpMatrix;

private:

	void controls();

public:

	SteeringBehaviour_Demo(Window* const window, Keyboard* const kbd, Mouse* const mse, Camera* const camera);
	~SteeringBehaviour_Demo();

	void update() override;

};