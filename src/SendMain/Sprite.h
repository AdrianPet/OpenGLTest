#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
};

enum SpriteBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	INDEX_VB
};

class Sprite
{
public:
	Sprite(Vertex* vertices, unsigned int numVertices);

	void Draw();

	virtual ~Sprite();
protected:
private:
	static const unsigned int NUM_BUFFERS = 3;

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
};

