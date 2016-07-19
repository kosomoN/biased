#include "WindowSystem.h"

#include "Log.h"

WindowSystem::~WindowSystem()
{
	glfwTerminate();
}

void glfw_error_callback(int error, const char* description)
{
    Log(ERROR, "GLFW Error: %s", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (gSys->pInput)
	//	gSys->pInput->key_callback(window, key, scancode, action, mods);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool WindowSystem::init(int width, int height)
{
    glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit()) {
        Log(ERROR, "Failed to initialize GLFW.");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	m_pWin = glfwCreateWindow(width, height, "survival", NULL, NULL);
	if (!m_pWin) {
        Log(ERROR, "Failed to create GLFW window.");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_pWin);
	glfwSetKeyCallback(m_pWin, key_callback);
	glfwSetFramebufferSizeCallback(m_pWin, framebuffer_size_callback);

    glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		Log(ERROR, "GLEW Error: %s", glewGetErrorString(err));
        return false;
	}
    Log(INFO, "Using GLEW %s", glewGetString(GLEW_VERSION));

	// Enable alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

void WindowSystem::updateWindow()
{
	glfwSwapBuffers(m_pWin);
	glfwPollEvents();
}
