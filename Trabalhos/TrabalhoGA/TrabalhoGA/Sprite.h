#pragma once

#include <../../shaders/Shader.h>

// GLM
#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite() {}
	void init(int textura, glm::vec3 scala, int nAnims=1, int nFrames = 1); //melhor jeito, com a textura já lida
	//void init(string filename); //caso queira carregar na própria sprite (não recomendável)
	void setDimension(glm::vec3 escala) { this->escala = escala; }
	void setPosition(glm::vec3 pos) { this->pos = pos; }
	void setIdAnim(int idAnim) { this->idAnim = idAnim; }
	void setIdFrame(int idFrame) { this->idFrame = idFrame; }
	void setTexture(GLuint textura) { this->textura = textura;  }

	void setShader(Shader* shader);
	void setTransform();

	void setRotacao(float angle, glm::vec3 axis, bool reset = true);
	void setTranslacao(glm::vec3 displacements, bool reset = true);
	void setDimension(glm::vec3 scaleFactors, bool reset = true);

	void draw();
	void update();
	void atualizarAnimacao();

protected:

	GLuint VAO; //id do buffer de geometria e seus atributos
	GLuint textura; //id da textura
	glm::mat4 model; //matriz de transformação

	//Posicao, escala e angulo
	glm::vec3 pos;
	glm::vec3 escala;
	float angulo;

	//Parametros da animação do sprite
	int idAnim;
	int idFrame;
	int nAnims;
	int nFrames;
	glm::vec2 offsetUV;

	Shader* shader; //nesse caso, ponteiro para o shader do scene manager
};

