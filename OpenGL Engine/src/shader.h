#pragma once

#include <glad/glad.h>

#include "External/Matrix.h"

#include "openGL.h"
#include "objects.h"

namespace Shader {

	void defaultDraw(const Matrix4& mvpMatrix, const GLuint& texture);

	void initTextureColour(const Matrix4& mvpMatrix, const GLuint& texture, const float& r, const float& g, const float& b);
	void editTexel(const Matrix4& mvpMatrix, const GLuint& texture, const float colourRGB[3], const float position2D[2], const float dimensionXY[2]);
	void cutFrameCell(const Matrix4& mvpMatrix, const GLuint& texture, const int& textureWidth, const int& textureHeight, const int& frameRow, const int& frameCol);

	void filterLightPass(const Matrix4& mvpMatrix, const GLuint& texture);
	void blendTexture(const Matrix4& mvpMatrix, const int& blendType, const GLuint& toBlend, const GLuint& texture);
	void blur(const Matrix4& mvpMatrix, const int& direction, const GLuint& texture, const float& blurRadius, const float& totalWeight, const int& textureWidth, const int& textureHeight);
	void blendColour(const Matrix4& mvpMatrix, const GLuint& texture, const int& r, const int& g, const int& b, const int& a);

	void drawSkyBox(const Matrix4& mvpMatrix, const GLuint& texture);

}