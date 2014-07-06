#include "Display.h"


Display::Display(int width, int height, const std::string& title)
{
	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return;
	}

	// Se creeaza fereastra
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!m_window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf("ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent(m_window);

	// Pornit extension handler-ul
	glewInit();

	// Vedem versiunile
	const GLubyte* renderer = glGetString(GL_RENDERER); //renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
}

void Display::SwapBuffers()
{
	// facem swap la buffere (Double buffer)
	glfwSwapBuffers(m_window);
}

void Display::Clear()
{
	// stergem ce s-a desenat anterior
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Display::~Display()
{
	glfwDestroyWindow(m_window);
}
