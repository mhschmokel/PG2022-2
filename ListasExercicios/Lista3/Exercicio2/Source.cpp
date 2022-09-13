#include <iostream>
#include <string>
#include <assert.h>


using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>

#include <../../shaders/Shader.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

int * getRandomColor();
GLfloat * getColor(int index);

const GLuint WIDTH = 800, HEIGHT = 600;

const int columns = 6;
const int rows = 6;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista3 - Exercicio2", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	
	Shader shader("../../dependencies/shaders/vertex_lista3.vs", "../../dependencies/shaders/fragment.fs");

	//GLuint shaderID = setupShader();
	GLuint VAO = setupGeometry();

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);
	projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(projection));

	int totalSquares = columns * rows;
	int colors[columns * rows] = { };

	srand((unsigned)time(NULL));

	for (int i = 0; i < totalSquares; i++) {
		colors[i] = (int)(rand() % (6)) + 1;
	}

	while (!glfwWindowShouldClose(window))
	{
		int currentColorIdx = 0;
		glfwPollEvents();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(3);
		glPointSize(5);

		glBindVertexArray(VAO);

		glfwGetFramebufferSize(window, &width, &height);

		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {

				glm::mat4 model = glm::mat4(1);
				model = glm::translate(model, glm::vec3(i * (WIDTH / columns), j * (HEIGHT / rows), 0.0f));
				model = glm::scale(model, glm::vec3(WIDTH / columns, HEIGHT / rows, 0.0));
				shader.setMat4("model", glm::value_ptr(model));

				switch (colors[currentColorIdx]) {
				case 1: //blue
					glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
					break;
				case 2: //orange
					glUniform4f(colorLoc, 1.0f, 0.5f, 0.0f, 1.0f);
					break;
				case 3: //green
					glUniform4f(colorLoc, 0.0f, 1.0f, 0.0f, 1.0f);
					break;
				case 4: //yellow
					glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
					break;
				case 5: //purple
					glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
					break;
				case 6: //cyann
					glUniform4f(colorLoc, 0.0f, 1.0f, 1.0f, 1.0f);
					break;
				default: //black
					glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
					break;
				}
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

				glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
				glDrawArrays(GL_POINTS, 0, 6);

				currentColorIdx++;
			}
		}

		glViewport(0, 0, width, height);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int setupGeometry()
{
	GLfloat vertices[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	

	return EBO;
}

int * getRandomColor() {
	int totalSquares = columns * rows;
	int colors[columns * rows] = { };

	srand((unsigned)time(NULL));

	for (int i = 0; i < totalSquares; i++) {
		colors[i] = (int) (rand() % (6)) + 1;
	}

	return colors;
}

GLfloat * getColor(int index) {
	GLfloat blue[] = { 0.0f, 0.0f, 1.0f };
	GLfloat orange[] = { 1.0f, 0.5f, 0.0f };
	GLfloat green[] = { 0.0f, 1.0f, 0.0f };
	GLfloat yellow[] = { 1.0f, 1.0f, 0.0f };
	GLfloat purple[] = { 1.0f, 0.0f, 1.0f };
	GLfloat cyann[] = { 0.0f, 1.0f, 1.0f };

	switch (index) {
	case 1:
		return blue;
	case 2:
		return yellow;
	case 3:
		return green;
	case 4:
		return orange;
	case 5:
		return purple;
	case 6:
		return cyann;
	default:
		return cyann;
	}
}