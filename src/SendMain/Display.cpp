#include "Display.h"

Display::Display(int width, int height, const std::string& title)
{
	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		std::cout << "ERROR: could not start GLFW3" << std::endl;
		return;
	}

	// Se creeaza fereastra
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		std::cout << "ERROR: could not open window with GLFW3" << std::endl;
		glfwTerminate();
		return;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent(window);

	// Pornit extension handler-ul
	glewInit();

	// Vedem versiunile
	const GLubyte* renderer = glGetString(GL_RENDERER); //renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version string
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported: " << version << std::endl;

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Display::Update()
{
	// facem swap la buffere (Double buffer)
	glfwSwapBuffers(window);

	glfwPollEvents();
	
	if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void Display::Clear()
{
	// stergem ce s-a desenat anterior
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsRunning()
{
	return !glfwWindowShouldClose(window);
}

Display::~Display()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
