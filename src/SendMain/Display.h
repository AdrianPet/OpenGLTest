#pragma once
#include <string>
#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <glm/glm.hpp>
#include <iostream>

class Display
{
public:
	Display(int width, int height, const std::string& title);

	void Clear();
	void SwapBuffers();

	virtual ~Display();
protected:
private:

	GLFWwindow* m_window;
};

