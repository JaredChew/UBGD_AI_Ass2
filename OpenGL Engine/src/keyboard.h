#pragma once

#include <chrono>

#include <GLFW/glfw3.h>

#define KEY_RELEASE 0
#define KEY_PRESS 1

#define SET_1_KEYS_START 32
#define SET_2_KEYS_START 161

#define SET_1_KEYS_END 96
#define SET_2_KEYS_END 348

#define SET_1_KEYS SET_1_KEYS_END - SET_1_KEYS_START
#define SET_2_KEYS SET_2_KEYS_END - SET_2_KEYS_START

class Keyboard {

private:

	GLFWwindow* const wnd;

	std::chrono::steady_clock::time_point tick;
	std::chrono::steady_clock::time_point tock;

	std::chrono::nanoseconds deltaTime;

	bool keyPressStatus_set1[SET_1_KEYS];
	bool keyPressStatus_set2[SET_2_KEYS];

private:

	bool isValidKey(const char& key);

	void setKeyPressStatus(const char& key, const bool& isPressed);
	bool getKeyPressStatus(const char& key);

public:
	Keyboard(GLFWwindow* const wnd);
	~Keyboard();

	bool isPressed(const char &key);
	bool isPressedOnce(const char& key);
	bool isKeyReleased(const char& key);
	bool isHold(const char &key);

	void update();

};