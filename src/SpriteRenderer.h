#pragma once

#include <string>
#include <vector>

#include "SpriteBatch.h"
#include "Sprite.h"

class SpriteRenderer
{
public:
    SpriteRenderer() {};
    ~SpriteRenderer();

    void renderSprites(SpriteBatch* sb);
    void removeSprite(Sprite* pSprite);
    Sprite* addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture);
    Sprite* addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture, bool end);
private:
    std::vector<Sprite*> m_sprites;

};
