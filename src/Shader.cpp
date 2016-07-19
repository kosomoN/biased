#include "Shader.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "Log.h"

Shader::Shader(std::string filePath)
{
    loadShader(filePath);
    glUseProgram(program);
    mvpLocation = glGetUniformLocation(program, "mvp");
}

Shader::~Shader()
{
    if (program)
        glDeleteProgram(program);
}

void Shader::setMatrix(const glm::mat4 & matrix)
{
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadShader(std::string filePath)
{
    std::ifstream fileStream(filePath);

    if (!fileStream.is_open())
    {
        Log(ERROR, "Error opening shader file %s", filePath.c_str());
        return;
    }

    std::stringstream contentSStream;
    contentSStream << fileStream.rdbuf();

    fileStream.close();

    std::string content = contentSStream.str();

    int delimiter = content.find("@");

    std::string vertShaderStr = content.substr(0, delimiter);
    std::string fragShaderStr = content.substr(delimiter + 1);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();


    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    GLint success;

    //Vertex shader
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxSize;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxSize);

        std::vector<GLchar> log(maxSize);
        glGetShaderInfoLog(vertShader, maxSize, &maxSize, &log[0]);
        Log(ERROR, "Error linking vertex shader %s", filePath.c_str());
        Log(ERROR, log.data());
        glDeleteShader(vertShader);
        return;
    }

    //Fragment shader
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxSize;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxSize);

        std::vector<GLchar> log(maxSize);
        glGetShaderInfoLog(fragShader, maxSize, &maxSize, &log[0]);
        Log(ERROR, "Error linking fragment shader %s", filePath.c_str());
        Log(ERROR, log.data());
        glDeleteShader(fragShader);
        glDeleteShader(vertShader);
        return;
    }
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxSize);

        std::vector<GLchar> log(maxSize);
        glGetProgramInfoLog(program, maxSize, &maxSize, &log[0]);
        Log(ERROR, "Error linking shader %s", filePath.c_str());
        Log(ERROR, log.data());
        glDeleteShader(vertShader);
        glDeleteShader(fragShader);
        glDeleteProgram(program);
        return;
    }


    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    Log(INFO, "Loaded shader: %s", filePath.c_str());
}
