#include "Animation.h"

#include <math.h>

Animation::Animation(int col, int row, float speed, glm::vec2 size, glm::vec2 rotPoint) :
    m_size(size),
    m_rotPointOffset(rotPoint),
    m_speed(speed)
{
    calcUVs(col, row);
}

glm::vec4& Animation::render(float delta)
{
    if (m_loops < m_loopLimit || m_loopLimit == -1) {
        m_uv = UVs[m_frame];

        m_frame += delta * m_speed;

        if (floor(m_frame) >= UVs.size()) {
            m_frame = 0.0f;
            m_loops++;
        }
        return m_uv;
    }

    isDone = true;

    return m_uv;
}

void Animation::setPlayLimit(int n)
{
    m_loopLimit = n;
    m_loops = 0;
    isDone = false;
}

void Animation::resetLoops()
{
    m_loops = 0;
    isDone = false;
}

void Animation::calcUVs(int cols, int rows)
{
    float u1 = 0, v1 = 0, u2 = 0, v2 = 0;
    float texWidth = (1.f / cols);
    float texHeight = (1.f / rows);
    for (int i = 0; i < rows; i++) {
        u1 = i*texHeight + texHeight;
        u2 = i*texHeight;
        for (int j = 0; j < cols; j++) {
            v2 = j*texWidth + texWidth;
            v1 = j*texWidth;
            UVs.push_back(glm::vec4(u1, v1, u2, v2));
        }
    }
}
