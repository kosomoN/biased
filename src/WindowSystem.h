#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowSystem {
public:
	~WindowSystem();
	bool init(int width, int height);
	void updateWindow();
	bool shouldClose() { return glfwWindowShouldClose(m_pWin) != 0; }
	GLFWwindow* getWindowPtr() { return m_pWin; }
private:
	GLFWwindow* m_pWin;
};
