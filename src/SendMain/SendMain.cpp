#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
#include <math.h>
#define PI 3.14159265359

// functie banala de incarcat continutul unui fisier intr-un buffer
char * LoadFileInMemory(const char *filename)
{
	int size = 0;
	char *buffer = NULL;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	buffer = new char[size + 1];
	if (size != fread(buffer, sizeof(char), size, f))
	{
		delete[] buffer;
	}
	fclose(f);
	buffer[size] = 0;
	return buffer;
}

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


int main() {
	// Initializare (se creeaza contextul)
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	// Se creeaza fereastra
	GLFWwindow* window = glfwCreateWindow(640, 480, "Workshop1", NULL, NULL);
	if (!window) {
		// nu am reusit sa facem fereastra, oprim totul si dam mesaj de eroare
		printf("ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	// Atasam contextul de fereastra
	glfwMakeContextCurrent(window);

	// Pornit extension handler-ul
	glewInit();

	// Vedem versiunile
	const GLubyte* renderer = glGetString(GL_RENDERER); //renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	const char * vertex_shader = LoadFileInMemory("../data/vertexShader.glsl");
	const char * fragment_shader = LoadFileInMemory("../data/pixelShader.glsl");
	const char * fragment_shader2 = LoadFileInMemory("../data/pixelShader2.glsl");

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, &fragment_shader2, NULL);
	glCompileShader(fs2);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
	GLuint shader_programme2 = glCreateProgram();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs);
	glLinkProgram(shader_programme2);

	delete[] vertex_shader;
	delete[] fragment_shader;

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
		-0.1f, 0.6f, 0.0f,
		0.1f, 0.6f, 0.0f,
		-0.1f, 0.4f, 0.0f
	};

	float radius = 0.2f;
	int number = 16;
	float vertex_buffer_circle[600];
	printf("Introduceti numarul de puncte cerc(max ~60):\nnumber=");
	scanf("%d", &number);
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

	while (!glfwWindowShouldClose(window)) {
		//..... Randare................. 
		// stergem ce s-a desenat anterior
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// spunem ce shader vom folosi pentru desenare
		glUseProgram(shader_programme);
		// facem bind la vertex buffer
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		//triunghi
		//  scriem in bufferul din memoria video informatia din bufferul din memoria RAM
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), vertex_buffer_triangle, GL_STATIC_DRAW);
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//patrat
		glBufferData(GL_ARRAY_BUFFER, 18 * sizeof (float), vertex_buffer_square, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//cerc
		glBufferData(GL_ARRAY_BUFFER, 3 * i * sizeof (float), vertex_buffer_circle, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, i);

		//galben
		glUseProgram(shader_programme2);
		//triunghi 2
		glBufferData(GL_ARRAY_BUFFER, 9 * sizeof (float), vertex_buffer_triangle2, GL_STATIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// facem swap la buffere (Double buffer)
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}