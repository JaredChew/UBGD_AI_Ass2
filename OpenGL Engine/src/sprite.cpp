#include "sprite.h"

Sprite::Sprite(Camera* camera, const char* directory, const int& spriteWidth, const int& spriteHeight, const int& sheetRow, const int& sheetCol, const int& animationFrameRate) : camera(camera) {

	glGenFramebuffers(1, &backBuffer);

	CBitmap bitmap(directory);

	textureWidth = bitmap.GetWidth();
	textureHeight = bitmap.GetHeight();
	
	OpenGL::initTexture(texture, 1, textureWidth, textureHeight);
	OpenGL::initTexture(textureProcessed, 1, textureWidth, textureHeight);

	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;

	this->sheetRow = sheetRow;
	this->sheetCol = sheetCol;

	totalAnimationFrames = 0;
	this->animationFrameRate = animationFrameRate;
	
	if (animationFrameRate) {
		totalAnimationFrames = sheetRow + sheetCol;
		animatedSprite = true;
	}

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;
	totalFramesPassed = 0;

	animationOneShot = false;

	deltaTime = std::chrono::nanoseconds(0);
	deltaTime_s = std::chrono::duration<double>(0.0);

	tick = std::chrono::high_resolution_clock::now();

	OpenGL::loadTexture(bitmap, texture);

	GLuint vertexShader = OpenGL::loadShaderFromFile(GL_VERTEX_SHADER, "../Shaders/default.vert");
	GLuint fragmentShader = OpenGL::loadShaderFromFile(GL_FRAGMENT_SHADER, "../Shaders/default.frag");

	if (!OpenGL::initProgramObject_Shader(animationShaderProgram, fragmentShader, vertexShader)) {
		Logger::getInstance()->warningLog("Failed to init animation shader program");
	}

}

Sprite::~Sprite() {

	glDeleteTextures(1, &texture);

	glDeleteProgram(animationShaderProgram);

}

void Sprite::blendColourAndTexture() {

	glBindFramebuffer(GL_FRAMEBUFFER, backBuffer);

	if (OpenGL::checkIsFramebufferReady()) {

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureProcessed, 0);

		Shader::blendColour(Matrix4::identity(), texture, colourBlend.x, colourBlend.y, colourBlend.z, colourBlend.w);

	}

}

void Sprite::setAnimationOneShot(const bool & animationOneShot) {

	this->animationOneShot = animationOneShot;

	animationRow = 0;
	animationCol = 0;

	animationFrame = 0;

}

void Sprite::setColourBlend(const Vector4& colourBlend) {
	this->colourBlend = colourBlend;
}

void Sprite::renderSprite(const Matrix4& mvpMatrix) {
	Shader::defaultDraw(mvpMatrix, textureProcessed);
}

void Sprite::renderSprite(const Vector3& translate, const Vector4& rotate, const Vector2& scale) {

	blendColourAndTexture();

	modelMatrix = Matrix4::translate(translate) * Matrix4::rotate(rotate.w, Vector3(rotate.x, rotate.y, rotate.z)) * Matrix4::scale(Vector3(scale.x, scale.y, 0.0f));

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (OpenGL::checkIsFramebufferReady()) {

		//glBindTexture(GL_TEXTURE_2D, 0);

		Shader::defaultDraw(modelMatrix * camera->gProjectionMatrix * camera->gViewMatrix, textureProcessed);

	}

}

void Sprite::renderSprite(const Matrix4& mvpMatrix, const int& row, const int& col) {

	glViewport(0, 0, spriteWidth, spriteHeight);

	Shader::cutFrameCell(mvpMatrix, textureProcessed, textureWidth, textureHeight, row, col);

}

void Sprite::renderAnimation(const Matrix4& mvpMatrix) {

	if (!animatedSprite) { return; }

	if (animationOneShot && animationFrame >= totalAnimationFrames) { return; }

	tock = std::chrono::high_resolution_clock::now();

	deltaTime += std::chrono::duration_cast<std::chrono::nanoseconds>(tock - tick);
	//deltaTime_s += tock - tick;

	if (totalFramesPassed >= animationFrameRate && deltaTime.count() < 1000000000) {

		glViewport(0, 0, spriteWidth, spriteHeight);

		Shader::cutFrameCell(mvpMatrix, texture, textureWidth, textureHeight, animationRow, animationCol);

		++animationFrame;
		++animationRow;

		if (animationRow >= sheetRow) {
			++animationCol;
			animationRow = 0;
		}

		deltaTime = std::chrono::nanoseconds(0);

	}

	if(deltaTime.count() >= 1000000000) { deltaTime = std::chrono::nanoseconds(0); }

	tick = tock;

	if (!animationOneShot && animationFrame >= totalAnimationFrames) { animationFrame = 0; }

	++totalFramesPassed;

}

void Sprite::setAnimationFrameRate(const int &animationFrameRate) {
	this->animationFrameRate = animationFrameRate;
}

int Sprite::getAnimationFrameRate() { return animationFrameRate; }

int Sprite::getAnimationFrame() { return animationFrame; }

bool Sprite::isAnimatedSprite() { return animatedSprite; }