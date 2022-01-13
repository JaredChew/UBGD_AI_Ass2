#pragma once

#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3

#include <chrono>

#include <GLFW/glfw3.h>

class Mouse {

private:

	GLFWwindow* const wnd;

	std::chrono::steady_clock::time_point tick;
	std::chrono::steady_clock::time_point tock;

	std::chrono::nanoseconds deltaTime;

	static double mousePosX;
	static double mousePosY;

	static double posOffsetX;
	static double posOffsetY;

	int holdButton;
	int lastButton;

	float holdDurationUpdate;

private:

	static void onMouseMove(GLFWwindow* wnd, double x, double y);

public:
	Mouse(GLFWwindow* wnd);
	~Mouse();

	void update();

	bool isPressed(const int &button);
	bool isPressedOnce(const int& button);
	bool isHold(const int &button);

	double getPosX();
	double getPosY();

	double getOffsetPosX();
	double getOffsetPosY();

};