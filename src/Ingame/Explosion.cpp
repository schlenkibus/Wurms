#include "Explosion.h"
#include "../Tools/MathTools.h"
#include "WorldObjects/Terrain.h"
#include <Box2D/Box2D.h>

Explosion::Explosion(Terrain *terrain, b2World *world, sf::Vector2f pos, float radius) : m_position(pos), m_radius(radius) {
    m_particleSystem = std::make_unique<SpriteParticleSystem>("/explosion.png", pos, 0.5, 30, 10, 0.2, true);
    auto bodysInRange = getBodysInRadius(pos, world, radius);
    for(auto& body: bodysInRange) {
        body->ApplyLinearImpulse(createForceInDirection(body, 3000.f), body->GetTransform().p, true);
    }
    terrain->applyExplosion(this);
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



std::vector<b2Body*> Explosion::getBodysInRadius(sf::Vector2f position, b2World *pWorld, float radius) {
    auto curr = pWorld->GetBodyList();

    std::vector<b2Body*> ret;
    while(curr != nullptr) {
        auto pos = curr->GetTransform().p;
        if(MathTools::distance(pos.x, pos.y, position.x, position.y) <= radius)
            ret.emplace_back(curr);

        curr = curr->GetNext();
    }
    return ret;
}

b2Vec2 Explosion::createForceInDirection(b2Body *body, float strength) const {
    auto bodyPos = body->GetTransform().p;
    auto explosionPos = m_position;

    b2Vec2 ret(bodyPos.x - explosionPos.x, bodyPos.y - explosionPos.y);
    ret *= strength;
    return ret;
}

float Explosion::getRadius() {
    return m_radius;
}

sf::Vector2f Explosion::getPosition() {
    return m_position;
}
