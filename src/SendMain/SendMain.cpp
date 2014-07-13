#include <stdio.h>
#include "Display.h"
#include "Shader.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Background.h"
#include "Enemy.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  // _DEBUG

int main()
{
	/*
		DONE:
				-clasa Enemy cu Sprite + miscare
				-generare automata mai multe clase de inamici initial
		TODO:
				-Proiectil pe Space. Miscare proiectil.
				-Rotatie pe Z(?)
				-Matrice ortografica si pentru camera
				-coliziuni de toate
				-Damage HP + kill adversari
		BUG:
				-pozitii inamici coincid
	*/

	Display* display = new Display(800, 600, "Joc");
	Shader* shader = new Shader("../data/Shader");
	Player* player = new Player(display, shader, 0.25f, "../data/Textures/player.png");
	Background* background = new Background(shader, "../data/Textures/Background.png");
	Enemy* enemy = new Enemy(shader, .4, 0);
	Enemy* enemy2 = new Enemy(shader, .4, 1);

	while (display->IsRunning()) {

		display->Clear();
		shader->Bind();

		background->Update();
		background->Draw();

		enemy->Update();
		enemy->Draw();
		enemy2->Update();
		enemy2->Draw();

		player->Update();
		player->Draw();
		
		display->Update();
	}

	delete display;
	delete shader;
	delete player;
	delete background;
	delete enemy;
	delete enemy2;

	_CrtDumpMemoryLeaks();
	
	return 0;
}