#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <cmath>
#include <SFML/Graphics/VertexArray.hpp>
#include <random>
#include "../../GameObject.h"

class ParticleSystemImpl : public sf::Drawable, public sf::Transformable
{
public:

    explicit ParticleSystemImpl(unsigned int count);
    void setEmitter(sf::Vector2f position);
    void update(sf::Time elapsed);
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> m_rotation_distribution;
    std::uniform_int_distribution<int> m_speed_distribution;
    std::uniform_int_distribution<int> m_lifetime_distribution;

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};

class ParticleSystem : public GameObject {
public:
    ParticleSystem();
    void draw(sf::RenderWindow& window) override;
    void update(float delta) override;
    bool onEvent(sf::Event& e) override;
private:
    void onResize(sf::Event& resizeEvent) override;
    ParticleSystemImpl m_system;
};