#pragma once

#include <glm/glm.hpp>

class Camera {
public:
	Camera(float width, float height);

	void resize(float width, float height);
	void setPosition(const glm::vec2& pos);
	const glm::vec3& getPosition() { return m_pos; }
	const glm::vec2& getSize() { return m_size; }
	const glm::mat4& getCombined() { return m_combined; }
	const glm::mat4& getProjection() { return m_projection; }
private:
	glm::vec2 m_size;
	glm::vec3 m_pos;
	glm::mat4 m_projection, m_translation, m_combined;
};

