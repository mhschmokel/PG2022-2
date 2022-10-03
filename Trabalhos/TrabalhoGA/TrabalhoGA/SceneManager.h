#pragma once

#include <../../shaders/Shader.h>
#include "Sprite.h" 
#include "TextureLoader.h"
#include "IniFileReader.h"
#include "AudioManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM
#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>

#include <vector>

using namespace std;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	
	//GLFW callbacks - PRECISAM SER EST�TICAS
	//Para isso, as vari�veis que modificamos dentro deles
	//tamb�m precisam ser e est�o no in�cio do SceneManager.cpp
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void resize(GLFWwindow* window, int width, int height);

	//M�todos pricipais
	void initialize(GLuint width, GLuint height);
	void run();
	void finish();

	//M�todos chamados no run (ciclo)
	void update();
	void render();

	//M�todos para configura��o e carregamento dos elementos da cena
	void initializeGraphics();
	Shader* addShader(string vFilename, string fFilename);
	void setupScene(); //antigo setupGeometry
	void setupCamera2D();

private:
	
	//Janela GLFW (por enquanto, assumimos apenas 1 inst�ncia)
	GLFWwindow *window;

	//Programa de shader (por enquanto, assumimos apenas 1 inst�ncia)
	Shader *shader;

	//C�mera 2D - Matriz de proje��o (ortogr�fica) com os limites em x,y
	glm::vec4 ortho2D; //xmin, xmax, ymin, ymax
	glm::mat4 projection;

	//Nossos objetos (sprites) da cena
	vector <Sprite*> objects;

	IniFileReader* iniFileReader;
	AudioManager* audioManager;
	string hitSoundPath;

	float ballRadius;
	float ballXmoveRate;
	float ballYmoveRate;

	glm::vec3 ballPosition;

	glm::vec3 playerAPosition;
	glm::vec3 playerBPosition;

	float playerHeight;
	float playerWidth;

	int maxPoints;
	int playerApoints;
	int playerBpoints;

	bool gameHasEnded;

	void createOrtho();
	void createBall();
	void createPlayerA();
	void createPlayerB();
	void createBackground();

	void moveBall();
	void movePlayerAUp();
	void movePlayerADown();
	void movePlayerBUp();
	void movePlayerBDown();

	void endGame();
	void restart();
	void restartObjects();

	void displayScore();

	void playHitSound();

};