#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	width = w;
	height = h;

	this->iniFileReader = new IniFileReader();
	iniFileReader->init("../config/game.ini");

	playerHeight = std::stof(iniFileReader->getValueByKey("playerHeight"));
	playerWidth = std::stof(iniFileReader->getValueByKey("playerWidth"));
	maxPoints = std::stoi(iniFileReader->getValueByKey("maxPoints"));
	
	hitSoundPath = iniFileReader->getValueByKey("hitAudioPath");

	audioManager = AudioManager::getInstance();
	audioManager->init();

	gameHasEnded = false;
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	string gameName = iniFileReader->getValueByKey("gameName");
	window = glfwCreateWindow(width, height, gameName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program
	shader = addShader("../../dependencies/shaders/vertex.vs", "../../dependencies/shaders/fragment.fs");

	//setup the scene -- LEMBRANDO QUE A DESCRIÇÃO DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURAÇÃO
	setupScene();

	resized = true; //para entrar no setup da câmera na 1a vez

}

Shader* SceneManager::addShader(string vFilename, string fFilename)
{
	return new Shader (vFilename.c_str(), fFilename.c_str());
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE]) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (gameHasEnded) {
		if (keys[GLFW_KEY_SPACE]) {
			restart();
		}
	}
	else 
	{
		if (keys[GLFW_KEY_W]) {
			movePlayerAUp();
		}
		else if (keys[GLFW_KEY_S]) {
			movePlayerADown();
		}

		if (keys[GLFW_KEY_UP]) {
			movePlayerBUp();
		}
		else if (keys[GLFW_KEY_DOWN]) {
			movePlayerBDown();
		}

		moveBall();
	}

	
}

void SceneManager::render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized)
	{
		setupCamera2D();
		resized = false;
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
		objects[i]->draw();
	}
	

}

void SceneManager::run()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		update();

		render();

		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	audioManager->cleanup();
	glfwTerminate();
}


void SceneManager::setupScene()
{
	createOrtho();
	createBackground();
	createBall();
	createPlayerA();
	createPlayerB();
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D()
{
	float zNear = -1.0, zFar = 1.0;

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	GLint projLoc = glGetUniformLocation(shader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void SceneManager::createOrtho()
{
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax
}

void SceneManager::createBall()
{
	ballXmoveRate = 5.0;
	ballYmoveRate = 5.0;

	ballPosition = glm::vec3(ortho2D[1] / 2, ortho2D[3] / 2, 0.0f);
	ballRadius = 15.0;
	glm::vec3 ballSize = glm::vec3(ballRadius * 2, ballRadius * 2, 0.0f);

	string ballTexturePath = iniFileReader->getValueByKey("ballTexturePath");
	GLuint textureID = TextureLoader::loadTexture(ballTexturePath);

	Sprite* obj = new Sprite;
	obj->init(textureID, glm::vec3(1.0f, 1.0f, 0.0f), 1, 1);
	obj->setShader(shader);
	obj->setTranslacao(ballPosition);
	obj->setDimension(ballSize, false);

	objects.push_back(obj);
}

void SceneManager::createPlayerA()
{
	playerAPosition = glm::vec3(ortho2D[0] + 100.0f, ortho2D[3] / 2, 0.0f);
	string playerAtexturePath = iniFileReader->getValueByKey("playerAtexturePath");
	GLuint textureID = TextureLoader::loadTexture(playerAtexturePath);

	Sprite* obj = new Sprite;
	obj->init(textureID, glm::vec3(1.0f, 1.0f, 0.0f), 1, 1);
	obj->setShader(shader);
	obj->setTranslacao(playerAPosition);
	obj->setDimension(glm::vec3(playerWidth, playerHeight, 0.0f), false);

	objects.push_back(obj);
}

void SceneManager::createPlayerB()
{
	playerBPosition = glm::vec3(ortho2D[1] - 100.0f, ortho2D[3] / 2, 0.0f);
	string playerBtexturePath = iniFileReader->getValueByKey("playerBtexturePath");
	GLuint textureID = TextureLoader::loadTexture(playerBtexturePath);

	Sprite* obj = new Sprite;
	obj->init(textureID, glm::vec3(1.0f, 1.0f, 0.0f), 1, 1);
	obj->setShader(shader);
	obj->setTranslacao(playerBPosition);
	obj->setDimension(glm::vec3(playerWidth, playerHeight, 0.0f), false);

	objects.push_back(obj);
}

void SceneManager::createBackground()
{
	string backgroundTexturePath = iniFileReader->getValueByKey("backgroundTexturePath");
	GLuint textureID = TextureLoader::loadTexture(backgroundTexturePath);

	Sprite* obj = new Sprite;
	obj->init(textureID, glm::vec3(1.0f, 1.0f, 0.0f), 1, 1);
	obj->setShader(shader);
	obj->setTranslacao(glm::vec3(ortho2D[1] / 2, ortho2D[3] / 2, 0.0f));
	obj->setDimension(glm::vec3(ortho2D[1], ortho2D[3], 0.0f), false);

	objects.push_back(obj);
}

void SceneManager::moveBall()
{
	if (ballPosition.x < ballRadius) {
		ballXmoveRate = -ballXmoveRate;
		ballPosition = glm::vec3(ortho2D[1] / 2, ortho2D[3] / 2, 0.0f);
		playerBpoints++;
		displayScore();
	}

	if (ballPosition.x > ortho2D[1] - ballRadius) {
		ballXmoveRate = -ballXmoveRate;
		ballPosition = glm::vec3(ortho2D[1] / 2, ortho2D[3] / 2, 0.0f);
		playerApoints++;
		displayScore();
	}

	if (ballPosition.y < ballRadius + 20.0 || ballPosition.y > ortho2D[3] - ballRadius - 20.0f) 
	{
		ballYmoveRate = -ballYmoveRate;
	}

	if (ballPosition.x - ballRadius <= playerAPosition.x + playerWidth/2
		&& ballPosition.x - ballRadius >= playerAPosition.x
		&& ballPosition.y <= playerAPosition.y + playerHeight/2
		&& ballPosition.y >= playerAPosition.y - playerHeight/2)
	{
		ballXmoveRate = -ballXmoveRate;
		playHitSound();
	}

	if (ballPosition.x + ballRadius >= playerBPosition.x - playerWidth/2
		&& ballPosition.x + ballRadius <= playerBPosition.x
		&& ballPosition.y <= playerBPosition.y + playerHeight/2
		&& ballPosition.y >= playerBPosition.y - playerHeight/2)
	{
		ballXmoveRate = -ballXmoveRate;
		playHitSound();
	}

	if (playerApoints == maxPoints || playerBpoints == maxPoints)
	{
		endGame();
	}
	else 
	{
		ballPosition.x += ballXmoveRate;
		ballPosition.y += ballYmoveRate;
		objects[1]->setTranslacao(ballPosition, false);
	}
}

void SceneManager::movePlayerAUp()
{
	if (playerAPosition.y < ortho2D[3] - 75.0f - 15.0f) {
		playerAPosition.y += 5.0f;
	}

	objects[2]->setPosition(playerAPosition);
}

void SceneManager::movePlayerADown()
{
	if (playerAPosition.y > ortho2D[0] + 75.0f + 15.0f) {
		playerAPosition.y -= 5.0f;
	}

	objects[2]->setPosition(playerAPosition);
}

void SceneManager::movePlayerBUp()
{
	if (playerBPosition.y < ortho2D[3] - 75.0f - 15.0f) {
		playerBPosition.y += 5.0f;
	}

	objects[3]->setPosition(playerBPosition);
}

void SceneManager::movePlayerBDown()
{
	if (playerBPosition.y > ortho2D[0] + 75.0f + 15.0f) {
		playerBPosition.y -= 5.0f;
	}

	objects[3]->setPosition(playerBPosition);
}

void SceneManager::endGame()
{
	gameHasEnded = true;

	if (playerApoints == 10) 
	{
		printf("Player A wins!\n");
	}
	else if (playerBpoints == 10) 
	{
		printf("Player B wins!\n");
	}

	printf("Press SPACE to play again\n");
	printf("Press ESC to exit\n");
}

void SceneManager::restart()
{
	playerApoints = 0;
	playerBpoints = 0;
	restartObjects();
	gameHasEnded = false;
}

void SceneManager::restartObjects()
{
	ballPosition = glm::vec3(ortho2D[1] / 2, ortho2D[3] / 2, 0.0f);
	playerAPosition = glm::vec3(ortho2D[0] + 100.0f, ortho2D[3] / 2, 0.0f);
	playerBPosition = glm::vec3(ortho2D[1] - 100.0f, ortho2D[3] / 2, 0.0f);

	
	objects[1]->setPosition(ballPosition);
	objects[2]->setPosition(playerAPosition);
	objects[3]->setPosition(playerBPosition);
}

void SceneManager::displayScore()
{
	printf("Player A: %d\n", playerApoints);
	printf("Player B: %d\n\n", playerBpoints);
}

void SceneManager::playHitSound() {
	audioManager->play_audio(hitSoundPath.c_str());
}