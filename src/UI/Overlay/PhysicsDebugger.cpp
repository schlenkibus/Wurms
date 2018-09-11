#include "PhysicsDebugger.h"
#include "../../Application.h"
#include "../../Ingame/IngameScene.h"
#include "../../Ingame/WormWorld.h"
#include <Box2D/Box2D.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

PhysicsDebugger::PhysicsDebugger(b2World *world) : m_world(world) {

}

void PhysicsDebugger::draw(sf::RenderWindow &window) {

    auto body = m_world->GetBodyList();
    while(body != nullptr) {

        auto shape = body->GetFixtureList()->GetShape();

        if(shape->m_type == b2Shape::e_polygon) {
            if(m_PolyRender)
                drawPoly((b2PolygonShape *) shape, body, window);
        }
        if (shape->m_type == b2Shape::e_chain){
            if(m_terrainRender)
                drawAllPoints((b2ChainShape *) shape, body, window);
        }

        body = body->GetNext();
    }

    if(m_expiringPointsActive) {
        for(auto &db: m_expiringPoints) {
            window.draw(db.first);
        }
    }
}

void PhysicsDebugger::drawAllPoints(b2ChainShape *pShape, b2Body* body, sf::RenderWindow &renderWindow) {
    sf::RectangleShape shape(sf::Vector2f(2,2));
    shape.setFillColor(sf::Color::Red);

    for(int i = 0; i < pShape->m_count; i++) {
        auto pos = pShape->m_vertices[i];
        auto worldPos = body->GetWorldPoint(pos);
        shape.setPosition(worldPos.x, worldPos.y);
        renderWindow.draw(shape);
    }
}

void PhysicsDebugger::drawPoly(b2PolygonShape *pShape, b2Body* body, sf::RenderWindow &renderWindow) {
    sf::RectangleShape shape(sf::Vector2f(2,2));
    shape.setFillColor(sf::Color::Green);

    for(int i = 0; i < pShape->m_count; i++) {
        auto pos = pShape->m_vertices[i];
        auto worldPos = body->GetWorldPoint(pos);
        shape.setPosition(worldPos.x, worldPos.y);
        renderWindow.draw(shape);
    }
}

void PhysicsDebugger::update(float delta) {
    for(auto& trace: m_expiringPoints) {
        trace.second -= sf::seconds(delta);
    }

    std::remove_if(m_expiringPoints.begin(), m_expiringPoints.end(), [](const std::pair<sf::CircleShape, sf::Time>& pt){
        return pt.second <= sf::Time::Zero;
    });
}

void PhysicsDebugger::onResize(sf::Event &resizeEvent) {

}

bool PhysicsDebugger::onEvent(sf::Event &e) {
    if(e.type == sf::Event::KeyReleased) {
        if(e.key.code == sf::Keyboard::T) {
            m_terrainRender = !m_terrainRender;
            return true;
        } else if(e.key.code == sf::Keyboard::Z) {
            m_PolyRender = !m_PolyRender;
            return true;
        } else if(e.key.code == sf::Keyboard::U) {
            m_expiringPoints.clear();
        } else if(e.key.code == sf::Keyboard::R) {
            m_expiringPointsActive = !m_expiringPointsActive;
        }
    }
    return false;
}

const PhysicsDebugger *PhysicsDebugger::getDebugger() {
    auto scene = Application::get().getWindow().getScene();
    if(auto ingameScene = dynamic_cast<IngameScene*>(scene)) {
        if(auto* world = ingameScene->getWorld()) {
            return world->getDebugger();
        }
    }
    return nullptr;
}

void PhysicsDebugger::addExpiringPoint(const sf::Vector2<float> position, sf::Time time) const {
    m_expiringPoints.emplace_back(std::make_pair(sf::CircleShape(2), time));
    m_expiringPoints.back().first.setPosition(position);
}

