#pragma once

#include <vector>

#include <glad/glad.h>

#include "External/bitmap.h"

#include "logger.h"

namespace OpenGL {

	//static void error_callback(int error, const char* description);

	bool initProgramObject_Shader(GLuint &programID, const GLuint& fragmentShader, const GLuint& vertexShade);

	void initTexture(GLuint& textureID, const GLsizei& size, const GLint& resolutionWidth, const GLint& resolutionHeight);

	bool checkIsFramebufferReady();

	GLuint loadShader(GLenum type, const char* shaderSrc);
	GLuint loadShaderFromFile(GLenum shaderType, std::string path);

	void loadTexture(const char* path, GLuint textureID);
	void loadTexture(const char* path, GLuint textureID, const GLint& resolutionWidth, const GLint& resolutionHeight, const GLuint& size);

	void loadTexture(CBitmap &bitmap, GLuint textureID);
	void loadTexture(CBitmap& bitmap, GLuint textureID, const GLint& resolutionWidth, const GLint& resolutionHeight, const GLuint& size);

	void loadCubemapTexture(std::vector<std::string> facesPath, GLuint textureID);

	void editTexel(const GLuint& texture, const int& xOffset, const int& yOffset, const uint8_t& r, const uint8_t& g, const uint8_t& b);

}