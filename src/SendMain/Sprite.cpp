#include "Sprite.h"

#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>


Sprite::Sprite(Vertex* vertices, unsigned int numVertices)
{
	static const unsigned int indices[] = {0, 1, 2, 0, 2, 3};
	m_numIndices = sizeof(indices) / sizeof(indices[0]);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> texCoords;
	positions.reserve(numVertices);
	texCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}

	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0]) * numVertices, &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0]) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * m_numIndices, &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

Sprite::~Sprite()
{
	glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Sprite::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}