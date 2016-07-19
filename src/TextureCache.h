#pragma once

#include <unordered_map>
#include <string>
#include <GL/glew.h>

class TextureCache
{
public:
    GLuint getTexture(std::string file);
private:
    GLuint createTexture(std::string file);
    std::unordered_map<std::string, GLuint> m_texures;
};
