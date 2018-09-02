#include "Explosion.h"

Explosion::Explosion(Terrain *terrain, b2World *world, sf::Vector2f pos) {
    m_particleSystem = std::make_unique<SpriteParticleSystem>("/explosion.png", pos, 0.5, 30, 10, 0.1, true);
}

void Explosion::draw(sf::RenderWindow &draw) {
    if(m_particleSystem)
        m_particleSystem->draw(draw);
}

void Explosion::update(float delta) {
    if(m_particleSystem) {
        if(m_particleSystem->finished())
        {
            m_particleSystem = nullptr;
            return;
        }
        m_particleSystem->update(delta);
    }
}

bool Explosion::onEvent(sf::Event &event) {
    if(m_particleSystem)
        return m_particleSystem->onEvent(event);
    return false;
}

bool Explosion::finished() const {
    if(m_particleSystem)
        return m_particleSystem->finished();
    else
        return true;
}
