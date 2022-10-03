#pragma once

#include <string>
#include <iostream>
#include <assert.h>
#include "stb_image.h"
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class TextureLoader
{
	public:
		static GLuint loadTexture(std::string texturePath);
};

