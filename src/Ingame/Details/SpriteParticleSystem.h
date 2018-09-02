#pragma once

#include <random>
#include <SFML/Graphics.hpp>
#include "../../GameObject.h"
#include "../../Tools/ResourceManager.h"

class SpriteParticleSystem : public GameObject {
public:
    SpriteParticleSystem(const std::string& textureName, sf::Vector2f pos, float textureScale = 1.f, float initialVelocity = 10.f, float endVelocity = 10.f, float lifeTimeInSeconds = 1.f, bool oneShot = true);
    void update(float delta) override;
    void draw(sf::RenderWindow& window) override;
    bool onEvent(sf::Event& e) override;
    bool finished() const;
protected:
    const std::string m_textureName;
    sf::Vector2f m_emitterPos;
    float m_textureScale;
    float m_initVelo;
    float m_endVelo;
    float m_lifeTime;
    bool oneShot;

    class Particle
    {
    public:
        Particle(const std::string& tex, sf::Vector2f velocity, sf::Time time) : velocity(velocity), lifetime(time),
        sprite(ResourceManager::get().getTexture(tex)) {

        }
        sf::Sprite sprite;
        sf::Vector2f velocity;
        sf::Time lifetime;
        bool done = false;
    };

    void resetParticle(std::size_t index);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> m_rotation_distribution;
    std::uniform_int_distribution<int> m_speed_distribution;

    std::vector<std::unique_ptr<Particle>> m_particles;

    void removeParticle(size_t i);
};
