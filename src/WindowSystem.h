#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WinResizeListener {
    virtual void windowResized(int width, int height) = 0;
};

class WindowSystem {
public:
	~WindowSystem();
	bool init(int width, int height);
	void updateWindow();
	bool shouldClose() { return glfwWindowShouldClose(m_pWin) != 0; }
	GLFWwindow* getWindowPtr() { return m_pWin; }
    std::vector<WinResizeListener*> resizeListeners;
private:
	GLFWwindow* m_pWin;
};

