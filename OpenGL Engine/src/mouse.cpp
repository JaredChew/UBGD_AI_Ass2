#include "mouse.h"

 double Mouse::mousePosX;
 double Mouse::mousePosY;

 double Mouse::posOffsetX;
 double Mouse::posOffsetY;

Mouse::Mouse(GLFWwindow* wnd) : wnd(wnd) {

	tick = std::chrono::high_resolution_clock::now();

	deltaTime = std::chrono::milliseconds(0);

	mousePosX = -1.0;
	mousePosY = -1.0;

	posOffsetX = 0.0;
	posOffsetY = 0.0;

	holdDurationUpdate = 500000000;

	holdButton = NULL;
	lastButton = NULL;

	glfwSetCursorPosCallback(wnd, onMouseMove);
	glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

Mouse::~Mouse() { }

void Mouse::onMouseMove(GLFWwindow* wnd, double x, double y) {

	if (mousePosX == -1 && mousePosY == -1)  {

		mousePosX = x;
		mousePosY = y;

		return;

	}

	posOffsetX = x - mousePosX;
	posOffsetY = y - mousePosY;

	mousePosX = x;
	mousePosY = y;

}

bool Mouse::isPressed(const int &button) {

	return glfwGetMouseButton(wnd, button);

}

bool Mouse::isPressedOnce(const int& button) {

	if (lastButton == button) { return false; }

	lastButton = button;

	return glfwGetKey(wnd, button);

}

bool Mouse::isHold(const int& button) {

	if (isPressed(button)) {

		if (deltaTime.count() >= holdDurationUpdate) {

			deltaTime = std::chrono::nanoseconds(0);

			return true;

		}


		holdButton = button;

	}

	return false;

}

void Mouse::update() {

	if (isPressed(holdButton) && deltaTime.count() > 0) { deltaTime += std::chrono::duration_cast<std::chrono::nanoseconds>(tock - tick); }
	else { deltaTime = std::chrono::nanoseconds(0); }

	tock = tick;
	tick = std::chrono::high_resolution_clock::now();

}

double Mouse::getPosX() { return mousePosX; }

double Mouse::getPosY() { return mousePosY; }

double Mouse::getOffsetPosX() { return posOffsetX; }

double Mouse::getOffsetPosY() { return posOffsetY; }