#pragma once

#include <string>
#include <vector>
#include <anax/anax.hpp>

#include "SpriteBatch.h"
#include "Sprite.h"
#include "Position.h"

class SpriteRenderer : public anax::System<anax::Requires<Sprite, Position>> {
public:
    ~SpriteRenderer();

    void renderSprites(SpriteBatch* sb, float delta);
    void removeSprite(Sprite* pSprite);
    Sprite* addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture);
    Sprite* addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture, bool last);
private:
    std::vector<Sprite*> m_sprites;

};
