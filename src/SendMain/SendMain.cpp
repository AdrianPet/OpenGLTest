#include <stdio.h>
#include "Display.h"
#include "Shader.h"
#include "SpriteManager.h"
#include "Player.h"
#include "Background.h"
#include "EnemyManager.h"

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
				-Not yet
	*/

	Display* display = new Display(800, 600, "Joc");
	Shader* shader = new Shader("../data/Shader");
	Player* player = new Player(display, shader, "../data/Textures/player.png");
	Background* background = new Background(shader, "../data/Textures/Background.png");
	EnemyManager* enemyManager = new EnemyManager(shader, 20);

	while (display->IsRunning()) {

		display->Clear();
		shader->Bind();

		background->Update();
		background->Draw();

		enemyManager->UpdateDraw();

		player->Update();
		player->Draw();
		
		display->Update();
	}

	delete display;
	delete shader;
	delete player;
	delete background;
	delete enemyManager;

	_CrtDumpMemoryLeaks();
	return 0;
}