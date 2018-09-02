#include "SpriteParticleSystem.h"

SpriteParticleSystem::SpriteParticleSystem(const std::string &textureName, sf::Vector2f pos, float textureScale,
                                           float initialVelocity, float endVelocity, float lifeTimeInSeconds,
                                           bool oneShot)
                                           :
                                           m_textureName(textureName),
                                           m_emitterPos(pos),
                                           m_textureScale(textureScale),
                                           m_initVelo(initialVelocity),
                                           m_endVelo(endVelocity),
                                           m_lifeTime(lifeTimeInSeconds),
                                           oneShot(oneShot),
                                           m_rotation_distribution(0, 360),
                                           m_speed_distribution(0, 100) {
    for(int i = 0; i < 15; i++) {
        m_particles.emplace_back(std::make_unique<Particle>(m_textureName, sf::Vector2f(), sf::seconds(m_lifeTime)));
        m_particles.back()->sprite.setScale(m_textureScale, m_textureScale);
        resetParticle(i);
    }

}

void SpriteParticleSystem::resetParticle(std::size_t index) {
    float angle = (m_rotation_distribution(generator) % 360) * 3.14f / 180.f;
    float speed = (m_speed_distribution(generator) % (int)(m_initVelo + 1));
    m_particles[index]->velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index]->lifetime = sf::seconds(m_lifeTime);
    m_particles[index]->sprite.setPosition(m_emitterPos);
}

float interpolate(float y1, float y2, float x1, float x2, float xIn)
{
    return (xIn - x1) / (x2 - x1) * (y2 - y1) + y1;
}

void SpriteParticleSystem::update(float delta) {
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        auto& p = m_particles[i];
        p->lifetime -= sf::seconds(delta);

        if (p->lifetime <= sf::Time::Zero && !oneShot)
            resetParticle(i);
        else if(p->lifetime <= sf::Time::Zero && oneShot)
            removeParticle(i);

        auto speed = interpolate(m_initVelo, m_endVelo, 0, m_lifeTime, p->lifetime.asSeconds());
        m_particles[i]->sprite.move(p->velocity * delta * speed);
    }
}

void SpriteParticleSystem::draw(sf::RenderWindow &window) {
    for(auto &p: m_particles) {
        window.draw(p->sprite);
    }
}

bool SpriteParticleSystem::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void SpriteParticleSystem::removeParticle(size_t i) {
    auto& p = m_particles[i];
    p->velocity.x = 0;
    p->velocity.y = 0;
    p->sprite.setColor(sf::Color::Transparent);
    p->done = true;
}

bool SpriteParticleSystem::finished() const {
    for(auto& p: m_particles) {
        if(!p->done)
            return false;
    }
    return true;
}
