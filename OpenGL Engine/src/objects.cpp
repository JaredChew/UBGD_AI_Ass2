#include "objects.h"

void Objects::drawSquare(GLuint texture) {

	static GLfloat vVertices[] = {

		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f

	};

	static GLfloat vColors[] = {

		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f

	};

	static GLfloat vTexCoords[] = {

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f

	};

	glBindTexture(GL_TEXTURE_2D, texture);

	static GLuint vao_Square;
	if (vao_Square == 0) { glGenVertexArrays(1, &vao_Square); }
	glBindVertexArray(vao_Square);

	static unsigned int verticesBuffer_Square;
	if (verticesBuffer_Square == 0) { glGenBuffers(1, &verticesBuffer_Square); }
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer_Square);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices) + sizeof(vColors) + sizeof(vTexCoords), vVertices, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vVertices), vVertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vVertices), sizeof(vColors), vColors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vVertices) + sizeof(vColors), sizeof(vTexCoords), vTexCoords);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (void*)sizeof(vVertices));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, (void*)(sizeof(vVertices) + sizeof(vColors)));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Objects::drawSkyBox(GLuint texture) {

	static float skyboxVertices[] = {

		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f

	};

	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	static GLuint vao_Cube;
	if (vao_Cube == 0) { glGenVertexArrays(1, &vao_Cube); }
	glBindVertexArray(vao_Cube);

	static unsigned int verticesBuffer_Cube;
	if (verticesBuffer_Cube == 0) { glGenBuffers(1, &verticesBuffer_Cube); }
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer_Cube);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, skyboxVertices);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}