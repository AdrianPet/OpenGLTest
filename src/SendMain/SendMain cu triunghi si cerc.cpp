#include <stdio.h>
#include <math.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Display.h"
#include "Shader.h"

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG
#include<vector>

void pointAtAngle(float vec[], int i, float r, int u)
{
	float pi = atan(1.0f) * 4;
	float urad = u * pi / 180.0f;
	float x = r * cos(urad);
	float y = r * sin(urad);
	float z = 0.0f;
	vec[3 * i] = x;
	vec[3 * i + 1] = y;
	vec[3 * i + 2] = z;
}

void translateSquare(float* pos, float dx, float dy)
{
	pos[0] += dx; pos[1] += dy;
	pos[3] += dx; pos[4] += dy;
	pos[6] += dx; pos[7] += dy;
	pos[9] += dx; pos[10] += dy;
}

void moveSquare(float* pos)
{
	//centrul patratului
	float xc = (pos[0] + pos[3] + pos[6] + pos[9]) / 4.0f;
	float yc = (pos[1] + pos[4] + pos[7] + pos[10]) / 4.0f;
	
	//centrul de rotatie si raza
	float x = 0.0f;
	float y = 0.0f;
	float radius = 0.5f;

	static int cadran = 1;
	float step = 0.01f;

	switch (cadran)
	{
	case 1:
		if ( radius <= xc + step)
			cadran = 4;
		break;
	case 4:
		if (xc < 0)
			cadran = 3;
		break;
	case 3:
		if (radius <= abs(xc) + abs(step))
			cadran = 2;
		break;
	case 2:
		if (xc > 0)
			cadran = 1;
		break;
	default:
		break;
	}

	if (cadran > 2)
		step = -step;

	//noile coordonate relative la centru
	float xn = xc - x + step;
	float yn = sqrt(pow(radius, 2) - pow(xn, 2));

	if (cadran > 2)
		yn = -yn;

	//deplasamente
	float dx = xn - xc;
	float dy = yn - yc;

	translateSquare(pos, -xc, -yc);
	translateSquare(pos, dx, dy);
	translateSquare(pos, xc, yc);
}

void moveCircle(float* pos, int n, int d)
{
	float speed = 0.01;
	float dx, dy;
	if (d >= 2)
	{
		dx = d == 3 ? speed : -speed;
		dy = 0;
	}
	else
	{
		dx = 0;
		dy = d == 0 ? speed : -speed;
	}
	for (int i = 0; i < n; i++)
	{
		pos[3 * i] += dx;
		pos[3 * i + 1] += dy;
	}
}

int main() {

	Display d(800, 600, "Joc");
	Shader s("../data/Shader");

	std::vector<unsigned int> indices(6);
	indices.push_back(0);
	indices.push_back(1);	
	indices.push_back(2);
	indices.push_back(3);	
	indices.push_back(0);
	indices.push_back(2);

	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// buffer cu vertecsi in RAM 
	float vertex_buffer_triangle[] = {
		0.5f, 0.15f, 0.0f,
		0.6f, -0.05f, 0.0f,
		0.4f, -0.05f, 0.0f
	};

	float vertex_buffer_triangle2[] = {
		-0.5f, 0.15f, 0.0f,
		-0.6f, -0.05f, 0.0f,
		-0.4f, -0.05f, 0.0f
	};

	float vertex_buffer_square[] = {
		0.1f, 0.6f, 0.0f,
		0.1f, 0.4f, 0.0f,
		-0.1f, 0.4f, 0.0f,
		-0.1f, 0.6f, 0.0f
	};

	float radius = 0.2f;
	int number = 16;
	float vertex_buffer_circle[600];
	//printf("Introduceti numarul de puncte cerc(max ~60):\nnumber=");
	//scanf("%d", &number);
	int i = 0; // numar vertecsi total cerc
	int j = 0; // numar vertecsi contur cerc
	float step = 360.0f / (number + 0.0f);
	float u = 0.0f;
	while (j < 2 * number)
	{
		if (i % 3 == 2)
		{
			//fiecare al treilea punct este centrul
			vertex_buffer_circle[3 * i] = vertex_buffer_circle[3 * i + 1] = vertex_buffer_circle[3 * i + 2] = 0.0f;
		}
		else
		{
			if (i % 3 == 0)
			{
				pointAtAngle(vertex_buffer_circle, i, radius, u);
			}
			else
			{
				u += step;
				pointAtAngle(vertex_buffer_circle, i, radius, u);
			}
			j++;
		}
		i++;
	}
	vertex_buffer_circle[3 * i] = vertex_buffer_circle[3 * i + 1] = vertex_buffer_circle[3 * i + 2] = 0.0f;
	i++;

	// Generam un buffer in memoria video si scriem in el punctele din ram
	GLuint vbo = 0;
	glGenBuffers(1, &vbo); // generam un buffer 
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // setam bufferul generat ca bufferul curent 
	
	// De partea aceasta am uitat sa va spun la curs -> Pentru a defini bufferul alocat de opengl ca fiind buffer de in de atribute, stream de vertecsi trebuie sa :
	// 1. Ii spunem OpenGL-ului ca vom avea un slot pentru acest atribut (in cazul nostru 0) , daca mai aveam vreun atribut ar fi trebuit si acela enablat pe alt slot (de exemplu 1)
	// 2. Definit bufferul ca Vertex Attribute Pointer cu glVertexAttribPointer
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	bool running = true;
	while (running) {
		//..... Randare................. 
		d.SwapBuffers();
		s.Bind();

		// facem bind la vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//triunghi
		//  scriem in bufferul din memoria video informatia din bufferul din memoria RAM
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), vertex_buffer_triangle, GL_STATIC_DRAW);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//patrat
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof (float), vertex_buffer_square, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
			);

		//cerc
		glBufferData(GL_ARRAY_BUFFER, 3 * i * sizeof (float), vertex_buffer_circle, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, i);

		//triunghi 2
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), vertex_buffer_triangle2, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwPollEvents();
		/*
		moveSquare(vertex_buffer_square);
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W)) {
			moveCircle(vertex_buffer_circle, i, 0);
		}

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S)) {
			moveCircle(vertex_buffer_circle, i, 1);
		}

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A)) {
			moveCircle(vertex_buffer_circle, i, 2);
		}

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D)) {
			moveCircle(vertex_buffer_circle, i, 3);
		}*/
	}

	_CrtDumpMemoryLeaks();
	glfwTerminate();

	return 0;
}