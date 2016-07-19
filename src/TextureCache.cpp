#include "TextureCache.h"

#include "Log.h"
#include "lodepng.h"

GLuint TextureCache::createTexture(std::string file)
{
	GLuint texture;

	unsigned int width, height;
	std::vector<unsigned char> image;

	unsigned int error = lodepng::decode(image, width, height, file.c_str());

	if (error) {
		Log(ERROR, "Could not load texture: %s", file.c_str());
		return 0;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_texures[file] = texture;

	return texture;
}

GLuint TextureCache::getTexture(std::string file)
{
	if (m_texures.find(file) == m_texures.end())
		return createTexture(file);

	return m_texures[file];
}
