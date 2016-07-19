
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Log.h"
#include "WindowSystem.h"
#include "Camera.h"
#include "Shader.h"
#include "TextureCache.h"
#include "SpriteBatch.h"
#include "SpriteRenderer.h"

int main()
{
    WindowSystem windowSys;
    if (!windowSys.init(1280, 720)) {
        Log(ERROR, "Error creating window.");
        return 1;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    TextureCache texCache;
    SpriteBatch batch(128);
    SpriteRenderer renderer;
    renderer.addSprite(310, 256, 0, 0, 1, 1, texCache.getTexture("data/textures/test.png"));

    Shader shader("data/shaders/plain.glsl");
    glUseProgram(shader.getProgram());

    Camera camera(1280, 720);

    glClearColor(0, 1, 1, 1);
    glfwSwapInterval(0);
    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while(!glfwWindowShouldClose(windowSys.getWindowPtr())) {
        shader.setMatrix(camera.getCombined());
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderSprites(&batch);

        // Measure frametime
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){
            Log(INFO, "%f ms/frame", (1000.0 * (currentTime - lastTime)) / nbFrames);
            nbFrames = 0;
            lastTime = currentTime;
        }
        windowSys.updateWindow();
    }
}
