
#include <iostream>
#include <cstdio>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <anax/anax.hpp>

#include "Log.h"
#include "WindowSystem.h"
#include "Camera.h"
#include "Shader.h"
#include "TextureCache.h"
#include "SpriteBatch.h"
#include "SpriteRenderer.h"
#include "Position.h"

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

    Shader shader("data/shaders/plain.glsl");
    glUseProgram(shader.getProgram());

    Camera camera(1280, 720);
    windowSys.resizeListeners.push_back(&camera);

    anax::World world;
    anax::Entity entity = world.createEntity();
    entity.addComponent<Position>(1, 2);
    entity.addComponent<Sprite>(310, 256, 0, 0, 1, 1, texCache.getTexture("data/textures/test.png"));
    entity.activate();

    world.addSystem(renderer);

    glClearColor(0, 1, 1, 1);
    glfwSwapInterval(1);
    double lastFrameTime = glfwGetTime();
    double lastFpsPrintTime = glfwGetTime();
    int frameCount = 0;
    while (!glfwWindowShouldClose(windowSys.getWindowPtr())) {
        float delta = (float) (glfwGetTime() - lastFrameTime);
        lastFrameTime = glfwGetTime();
        world.refresh();

        shader.setMatrix(camera.getCombined());
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.renderSprites(&batch, delta);

        // Measure frametime
        frameCount++;
        if ( lastFrameTime - lastFpsPrintTime >= 1.0 ){
            Log(INFO, "%f ms/frame", (1000.0 * (lastFrameTime - lastFpsPrintTime)) / frameCount);
            frameCount = 0;
            lastFpsPrintTime = lastFrameTime;
        }
        windowSys.updateWindow();
    }
}
