#pragma once

#include <GLFW/glfw3.h>

#include "External/Matrix.h"

#include "keyboard.h"

class Camera {

private:

	Keyboard* const kbd;

	float cameraYaw;
	float cameraPitch;
	float cameraDistance;

	float cameraSide;
	float cameraScroll;
	float cameraDepth;

	float cameraSpeed;

public:

	Matrix4 gProjectionMatrix;
	Matrix4 gViewMatrix;

public:

	Camera(Keyboard *const kbd, const float& cameraYaw, const float& cameraPitch, const float& cameraDistance, const float& cameraSide, const float& cameraScroll, const float& cameraDepth, const float& cameraSpeed);
	~Camera();

	Matrix4 getViewMatrixWithoutTranslate(void);

	void update();

};