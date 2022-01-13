#include "keyboard.h"

Keyboard::Keyboard(GLFWwindow* const wnd) : wnd(wnd) {

	tick = std::chrono::high_resolution_clock::now();

	deltaTime = std::chrono::nanoseconds(0);

}

Keyboard::~Keyboard() { }

bool Keyboard::isValidKey(const char& key) {

	if (key < SET_1_KEYS_START) { return false; }
	if (key > SET_2_KEYS_END) { return false; }
	if (key > SET_1_KEYS_END && key < SET_2_KEYS_START) { return false; }

	return true;

}

void Keyboard::setKeyPressStatus(const char& key, const bool& isPressed) {

	if (key < SET_1_KEYS_END) { keyPressStatus_set1[SET_1_KEYS_END - key] = isPressed; }
	else { keyPressStatus_set2[SET_2_KEYS_END - key] = isPressed; }

}

bool Keyboard::getKeyPressStatus(const char& key) {

	if (key < SET_1_KEYS_END) { return keyPressStatus_set1[SET_1_KEYS_END - key]; }
	else { return keyPressStatus_set2[SET_2_KEYS_END - key]; }

	return false;

}

bool Keyboard::isPressed(const char& key) {

	if (!isValidKey(key)) { return false; }

	return glfwGetKey(wnd, key);

}

bool Keyboard::isPressedOnce(const char& key) {

	if (!isValidKey(key)) { return false; }

	if (glfwGetKey(wnd, key) == GLFW_RELEASE || getKeyPressStatus(key)) { return false; }

	setKeyPressStatus(key, true);

	return true;

}

bool Keyboard::isKeyReleased(const char& key) {

	if (!isValidKey(key)) { return false; }

	if (glfwGetKey(wnd, key) == GLFW_PRESS || !getKeyPressStatus(key)) { return false; }

	setKeyPressStatus(key, false);

	return true;

}

bool Keyboard::isHold(const char& key) {

	if (!isValidKey(key)) { return false; }

	if (glfwGetKey(wnd, key) == GLFW_RELEASE || !getKeyPressStatus(key)) { return false; }

	setKeyPressStatus(key, true);

	return true;

}

void Keyboard::update() {

	tick = std::chrono::high_resolution_clock::now();

	if (deltaTime.count() >= 500000000) {

		for (int i = 0; i < SET_1_KEYS; ++i) {

			if (keyPressStatus_set1[i] && !glfwGetKey(wnd, i + SET_1_KEYS_START)) {
				keyPressStatus_set1[i] = false;
			}

		}

		for (int i = 0; i < SET_2_KEYS; ++i) {

			if (keyPressStatus_set2[i] && !glfwGetKey(wnd, i + SET_2_KEYS_START)) {
				keyPressStatus_set2[i] = false;
			}

		}

		deltaTime = std::chrono::nanoseconds(0);

	}

	tock = tick;

}