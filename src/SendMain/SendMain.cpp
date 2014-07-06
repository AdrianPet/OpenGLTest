#include <stdio.h>
#include <math.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Display.h"
#include "Shader.h"
#include "Sprite.h"
#include"Texture.h"

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG
#include<vector>

int main() {

	Display d(800, 600, "Joc");
	Shader sh("../data/Shader");
	Vertex verts[] = {
		Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1, 1)),
		Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0)),
		Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0, 0)),
		Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(0, 1))
	};
	Sprite sq(verts, sizeof(verts) / sizeof(verts[0]));
	Texture t("tex.jpg");

	bool running = true;
	while (running) {
		d.SwapBuffers();
		sh.Bind();
		t.Bind();
		sq.Draw();
	}

	_CrtDumpMemoryLeaks();

	return 0;
}