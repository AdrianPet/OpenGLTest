#include <stdio.h>
#include <math.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Display.h"
#include "Shader.h"
#include "Sprite.h"

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG
#include<vector>

int main() {

	Display display(800, 600, "Joc");
	Shader shader("../data/Shader");
	Vertex verts[] = {
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(0, 1))
	};
	Sprite square1(verts, sizeof(verts) / sizeof(verts[0]), "tex.jpg");

	while (display.IsRunning()) {
		display.Clear();

		shader.Bind();
		square1.Draw();
		
		display.Update();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}