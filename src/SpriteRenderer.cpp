#include "SpriteRenderer.h"

#include <algorithm>
#include <anax/anax.hpp>
#include "TextureCache.h"

SpriteRenderer::~SpriteRenderer()
{
    for (Sprite* s : m_sprites)
        delete s;

    m_sprites.clear();
}

void SpriteRenderer::renderSprites(SpriteBatch* sb, float delta)
{
    auto entities = getEntities();
    for (anax::Entity& e : entities) {
        Position& pos = e.getComponent<Position>();
        Sprite& sprite = e.getComponent<Sprite>();
        if (sprite.m_texture != sb->getCurrentTexture())
            sb->begin(sprite.m_texture);

        sb->draw(sprite, pos.vec, delta);
    }

    if (!entities.empty())
        sb->end();
}

void SpriteRenderer::removeSprite(Sprite* pSprite)
{
    m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), pSprite));
    delete pSprite;
}

Sprite* SpriteRenderer::addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture)
{
    return addSprite(width, height, u1, v1, u2, v2, texture, true);
}

//TODO Make better layering
Sprite* SpriteRenderer::addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture, bool last)
{
    Sprite* pSprite = new Sprite(width, height, u1, v1, u2, v2, texture);
    if (last)
        m_sprites.push_back(pSprite);
    else
        m_sprites.insert(m_sprites.begin(), pSprite);
    return pSprite;
}

