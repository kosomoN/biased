#include "SpriteRenderer.h"

#include <algorithm>
#include "TextureCache.h"

SpriteRenderer::~SpriteRenderer()
{
    for (Sprite* s : m_sprites)
        delete s;

    m_sprites.clear();
}

void SpriteRenderer::renderSprites(SpriteBatch* sb)
{
    if (m_sprites.size() > 0) {
        sb->begin(m_sprites.front()->m_texture);

        for (auto s : m_sprites) {
//            if (s->m_texture != sb->getCurrentTexture())
                sb->begin(s->m_texture);

            sb->draw(s);
        }

        sb->end();
    }
}

void SpriteRenderer::removeSprite(Sprite * pSprite)
{
    m_sprites.erase(std::remove(m_sprites.begin(), m_sprites.end(), pSprite));
    delete pSprite;
}

Sprite* SpriteRenderer::addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture)
{
    return addSprite(width, height, u1, v1, u2, v2, texture, true);
}

//TODO Make better layering
Sprite* SpriteRenderer::addSprite(float width, float height, float u1, float v1, float u2, float v2, GLuint texture, bool end)
{
    auto pSprite = new Sprite(width, height, u1, v1, u2, v2, texture);
    if (end)
        m_sprites.push_back(pSprite);
    else
        m_sprites.insert(m_sprites.begin(), pSprite);
    return pSprite;
}

