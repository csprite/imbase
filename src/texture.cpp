#include "imbase/texture.hpp"
#include "glad/glad.h"

using namespace ImBase;

Texture::Texture(int w, int h, const unsigned char* pixels, TScaleFunc _scaleFunc) {
	scaleFunc = _scaleFunc;
	unsigned int TexScaling = 0;
	switch (_scaleFunc) {
		case Nearest: TexScaling = GL_NEAREST; break;
		case Linear: TexScaling = GL_LINEAR; break;
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TexScaling);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TexScaling);

	width = w;
	height = h;

	const unsigned char* data = pixels;

	if (pixels == nullptr) {
		data = new unsigned char[width * height * 4]();
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	if (pixels == nullptr) {
		delete[] data;
		data = nullptr;
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Update(const unsigned char* pixels, unsigned int dX, unsigned int dY, unsigned int dW, unsigned int dH) {
	if (dW == 0) dW = width;
	if (dH == 0) dH = height;

	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
	glTexSubImage2D(
		GL_TEXTURE_2D, 0,
		dX, dY, dW, dH,
		GL_RGBA, GL_UNSIGNED_BYTE,
		&pixels[((dY * width) + dX) * 4]
	);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
	id = 0;
}

