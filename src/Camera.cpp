#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float width, float height)
{
	resize(width, height);
}

void Camera::resize(float width, float height)
{
	m_size.x = width;
	m_size.y = height;

	m_projection = glm::ortho(-width / 2.f, width / 2.f, -height / 2.f, height / 2.f);
	m_combined = m_projection * m_translation;
}

void Camera::setPosition(const glm::vec2& pos)
{
	m_pos = glm::vec3(pos.x, pos.y, 0);
	m_translation = glm::translate(glm::mat4(1.0f), -m_pos);
	m_combined = m_projection * m_translation;
}
