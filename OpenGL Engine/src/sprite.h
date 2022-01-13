#pragma once

#include <glad/glad.h>

#include "External/bitmap.h"
#include "External/Matrix.h"

#include "logger.h"
#include "openGL.h"
#include "objects.h"
#include "shader.h"
#include "camera.h"

class Sprite {

private:

	Camera* const camera;

private:

	GLuint texture;
	GLuint textureProcessed;

	GLuint backBuffer;

	GLuint animationShaderProgram;

	Matrix4 modelMatrix;

	Vector4 colourBlend;

	int textureWidth;
	int textureHeight;

	int spriteWidth;
	int spriteHeight;

	int sheetRow;
	int sheetCol;

	int totalAnimationFrames;
	int animationFrameRate;

	int animationRow;
	int animationCol;

	int animationFrame;
	int totalFramesPassed;

	bool animatedSprite;
	bool animationOneShot;

	std::chrono::steady_clock::time_point tick;
	std::chrono::steady_clock::time_point tock;

	std::chrono::nanoseconds deltaTime;
	std::chrono::duration<double> deltaTime_s;

private:

	void blendColourAndTexture();

public:

	Sprite(Camera* camera, const char* directory, const int& spriteWidth = 0, const int& spriteHeight = 0, const int& sheetRow = 0, const int& sheetCol = 0, const int& animationFrameRate = 0);
	~Sprite();

	void setAnimationOneShot(const bool& animationOneShot);

	void setColourBlend(const Vector4& colourBlend);

	void renderSprite(const Matrix4& mvpMatrix);
	void renderSprite(const Vector3& translate, const Vector4& rotate, const Vector2& scale);

	void renderSprite(const Matrix4& mvpMatrix, const int& frameRow, const int& frameCol);
	void renderSprite(const Vector3& translate, const Vector4& rotate, const Vector2& scale, const int& frameRow, const int& frameCol);

	void renderAnimation(const Matrix4& mvpMatrix);

	void setAnimationFrameRate(const int &animationFrameRate);

	int getAnimationFrameRate();
	int getAnimationFrame();

	bool isAnimatedSprite();

};

/*

Sprite::Sprite(const char *directory) {

	CBitmap bitmap(directory);

	textureWidth = bitmap.GetWidth();
	textureHeight = bitmap.GetHeight();

	spriteWidth = textureWidth;
	spriteHeight = textureHeight;

	sheetRow = 0;
	sheetCol = 0;

	totalAnimationFrames = 0;
	animationFrameRate = 0;

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;
	totalFramesPassed = 0;

	animatedSprite = false;
	animationOneShot = false;

	init(bitmap);

}

Sprite::Sprite(const char* directory, const int &spriteWidth, const int& spriteHeight, const int & sheetRow, const int & sheetCol) {

	CBitmap bitmap(directory);

	textureWidth = bitmap.GetWidth();
	textureHeight = bitmap.GetHeight();

	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;

	this->sheetRow = sheetRow;
	this->sheetCol = sheetCol;

	totalAnimationFrames = 0;
	animationFrameRate = 0;

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;
	totalFramesPassed = 0;

	animatedSprite = false;
	animationOneShot = false;

	init(bitmap);

}

*/