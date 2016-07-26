#include "SpriteBatch.h"

#include <cmath>
#include <glm/vec4.hpp>
#include "Sprite.h"
#include "Animation.h"

SpriteBatch::SpriteBatch(int maxSprites)
{
    m_bufferData.resize(ELEMENTS_PER_VERTEX * 6 * maxSprites);
    m_maxVertices = maxSprites * 6;
    glGenBuffers(1, &m_vb);
    glBindBuffer(GL_ARRAY_BUFFER, m_vb);
    //Float bytes * (xy + uv + rgba) * four corners made up by two triangles * maxSprites
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ELEMENTS_PER_VERTEX * 6 * maxSprites, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::begin(GLuint texture)
{
    if (m_isDrawing)
        end();

    m_isDrawing = true;
    m_currentTexture = texture;
    m_vertices = 0;
}

void SpriteBatch::end()
{
    assert(m_isDrawing);

    //Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vb);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * ELEMENTS_PER_VERTEX * m_vertices, m_bufferData.data());

    //Bind diffuse
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_currentTexture);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //Position, uv, color
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, reinterpret_cast<void*>(sizeof(GLfloat) * 2));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * ELEMENTS_PER_VERTEX, reinterpret_cast<void*>(sizeof(GLfloat) * 4));

    glDrawArrays(GL_TRIANGLES, 0, m_vertices);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_isDrawing = false;
    m_currentTexture = 0;
    m_vertices = 0;
    m_index = 0;
}

void SpriteBatch::setColor(float red, float green, float blue, float alpha)
{
    m_r = red;
    m_g = green;
    m_b = blue;
    m_a = alpha;
}

void SpriteBatch::draw(float x, float y, float width, float height, float u1, float v1, float u2, float v2, float rotation, glm::vec2 rotPoint)
{
    if (m_vertices + 6 > m_maxVertices)
    {
        begin(m_currentTexture);
    }

    m_vertices += 6;

    float cosTheta = cos(rotation);
    float sinTheta = sin(rotation);


    //Bottom left
    glm::vec2 p = glm::vec2(x, y);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Bottom right
    p = glm::vec2(x + width, y);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Top left
    p = glm::vec2(x, y + height);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;


    //Second triangle

    //Top left
    p = glm::vec2(x, y + height);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Bottom right
    p = glm::vec2(x + width, y);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Top right
    p = glm::vec2(x + width, y + height);
    calcPoint(rotPoint, p, cosTheta, sinTheta);
    m_bufferData[m_index++] = p.x;
    m_bufferData[m_index++] = p.y;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;
}

void SpriteBatch::drawVertices(const float& x1, const float& y1, const float& x2, const float& y2, const float& u1, const float& v1, const float& u2, const float& v2)
{
    if (m_vertices + 6 > m_maxVertices)
    {
        begin(m_currentTexture);
    }

    m_vertices += 6;

    //Bottom left
    m_bufferData[m_index++] = x1;
    m_bufferData[m_index++] = y1;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Bottom right
    m_bufferData[m_index++] = x2;
    m_bufferData[m_index++] = y1;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Top left
    m_bufferData[m_index++] = x1;
    m_bufferData[m_index++] = y2;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;


    //Second triangle

    //Top left
    m_bufferData[m_index++] = x1;
    m_bufferData[m_index++] = y2;

    m_bufferData[m_index++] = u1;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Bottom right
    m_bufferData[m_index++] = x2;
    m_bufferData[m_index++] = y1;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v1;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;

    //Top right
    m_bufferData[m_index++] = x2;
    m_bufferData[m_index++] = y2;

    m_bufferData[m_index++] = u2;
    m_bufferData[m_index++] = v2;

    m_bufferData[m_index++] = m_r;
    m_bufferData[m_index++] = m_g;
    m_bufferData[m_index++] = m_b;
    m_bufferData[m_index++] = m_a;
}

void SpriteBatch::draw(Sprite& sprite, glm::vec2 pos, float delta)
{
    if (sprite.m_shouldDraw) {
        glm::vec2 rotPoint = pos + sprite.m_rotPointOffset;
        if (sprite.m_pAnim != nullptr) {
            glm::vec4 uv = sprite.m_pAnim->render(delta);
            draw(pos.x, pos.y, sprite.m_width, sprite.m_height, uv.y, uv.x, uv.w, uv.z, sprite.m_rotation, rotPoint);
        } else {
            draw(pos.x, pos.y, sprite.m_width, sprite.m_height, sprite.m_u1, sprite.m_v1, sprite.m_u2, sprite.m_v2, sprite.m_rotation, rotPoint);
        }
    }
}

void SpriteBatch::calcPoint(glm::vec2 rotationPoint, glm::vec2& point, float cos, float sin)
{
    point.x -= rotationPoint.x;
    point.y -= rotationPoint.y;

    float x = point.x * cos - point.y * sin;
    float y = point.x * sin + point.y * cos;

    point.x = x + rotationPoint.x;
    point.y = y + rotationPoint.y;
}

SpriteBatch::~SpriteBatch()
{
    glDeleteBuffers(1, &m_vb);
}
