#pragma once

#include <vector>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>

class Animation {
public:
	Animation(int col, int row, float speed, glm::vec2 size, glm::vec2 rotPoint = glm::vec2(0.5));

	glm::vec4& render(float delta);
	// Loops the animations n times
	void setPlayLimit(int n);
	void resetLoops();

	std::vector<glm::vec4> UVs;
	bool isDone = false;
	glm::vec2 m_size;
	glm::vec2 m_rotPointOffset;
private:
	void calcUVs(int col, int row);
	float m_frame = -1;
	float m_speed = 0;
	int m_loops = 0;
	int m_loopLimit = 0;
	glm::vec4 m_uv = glm::vec4(0, 0, 0, 0);

};

