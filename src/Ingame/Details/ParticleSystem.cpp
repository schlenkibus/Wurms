#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : m_system(200) {
    m_system.setPosition( 500, 300);
}

void ParticleSystem::draw(sf::RenderWindow &window) {
    window.draw(m_system);
}

void ParticleSystem::update(float delta) {
    m_system.update(sf::seconds(delta));
}

bool ParticleSystem::onEvent(sf::Event &e) {
    return false;
}

//IMPL

ParticleSystemImpl::ParticleSystemImpl(unsigned int count) :
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(0.2)),
        m_emitter(0, 0),
        m_rotation_distribution(1, 360),
        m_speed_distribution(40, 100),
        m_lifetime_distribution(1, 100)
{
}

void ParticleSystemImpl::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

void ParticleSystemImpl::resetParticle(std::size_t index)
{
    float angle = (m_rotation_distribution(generator) % 360) * 3.14f / 180.f;
    float speed = (m_speed_distribution(generator) % 50) + 50.f;
    m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds(m_lifetime_distribution(generator) + 1000);
    m_vertices[index].position = m_emitter;
}

void ParticleSystemImpl::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        // update the particle lifetime
        Particle& p = m_particles[i];
        p.lifetime -= elapsed;

        // if the particle is dead, respawn it
        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        // update the position of the corresponding vertex
        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        // update the alpha (transparency) of the particle according to its lifetime
        float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystemImpl::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = nullptr;
    target.draw(m_vertices, states);
}
