#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <../../shaders/Shader.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista1-Exercicio9", nullptr, nullptr);
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
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	Shader shader("../../dependencies/shaders/vertex.vs", "../../dependencies/shaders/fragment.fs");

	//GLuint shaderID = setupShader();
	GLuint VAO = setupGeometry();
	
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);
	
	glUseProgram(shader.ID);
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(5);
		glPointSize(20);

		glBindVertexArray(VAO);
		
		glUniform4f(colorLoc, 1.0f, 0.5f, 0.0f, 1.0f);
		glDrawArrays(GL_LINES, 0, 2);

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_STRIP, 2, 4);

		glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 6, 3);

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 6, 3);

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_STRIP, 9, 4);

		glUniform4f(colorLoc, 0.64f, 0.16f, 0.16f, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 9, 4);

		glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f);
		glDrawArrays(GL_LINE_LOOP, 13, 4);

		glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);
		glDrawArrays(GL_TRIANGLE_FAN, 13, 4);
		
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
		0.00, 0.0, 0.0, //Floor Begin
		0.70, 0.0, 0.0, //Floor End
		0.20, 0.0, 0.0, //Casa 1
		0.20, 0.3, 0.0, //Casa 2
		0.50, 0.3, 0.0, //Casa 3
		0.50, 0.0, 0.0, //Casa 4
		0.20, 0.3, 0.0, //Telhado1
		0.35, 0.5, 0.0, //Telhado2
		0.50, 0.3, 0.0, //Telhado3
		0.30, 0.0, 0.0, //Porta1
		0.30, 0.15, 0.0, //Porta2
		0.4, 0.15, 0.0, //Porta3
		0.4, 0.0, 0.0, //Porta4
		0.25, 0.2, 0.0, //Janela1
		0.25, 0.26, 0.0, //Janela2
		0.31, 0.26, 0.0, //Janela3
		0.31, 0.2, 0.0 //Janela4

	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;
}

