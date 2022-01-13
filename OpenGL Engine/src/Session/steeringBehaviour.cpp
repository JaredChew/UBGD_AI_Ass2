#include "SteeringBehaviour.h"

SteeringBehaviour_Demo::SteeringBehaviour_Demo(Window* const wnd, Keyboard* const kbd, Mouse* const mse, Camera* const camera) : wnd(wnd), kbd(kbd), mse(mse), camera(camera) {

	//Init frame buffer
	glGenFramebuffers(1, &backBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	sprite = new Sprite(camera, "../Media/fish.bmp");

}

SteeringBehaviour_Demo::~SteeringBehaviour_Demo() {

	delete sprite;
	sprite = nullptr;

	glUseProgram(0);

	glDeleteFramebuffers(1, &backBuffer);

}


void SteeringBehaviour_Demo::controls() {

	if (mse->isPressed(MOUSE_BUTTON_LEFT)) {

		//

	}

}


void SteeringBehaviour_Demo::update() {

	sprite->setColourBlend(Vector4(0.2f, 0.7f, 0.3f, 0.5f));

	//fish.modelMatrix = Matrix4::translate(position);

	//modelMatrix = Matrix4::translate(Vector3(1.0, 1.0, 0.0f)) * Matrix4::scale(Vector3(1.0, 1.0, 0.0f));

	mvpMatrix = camera->gProjectionMatrix * camera->gViewMatrix * modelMatrix;

	glViewport(0, 0, wnd->getWidth(), wnd->getHeight());

	sprite->renderSprite(Vector3(1.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 30.0f), Vector2(0.3f, 1.2f));

	controls();

}