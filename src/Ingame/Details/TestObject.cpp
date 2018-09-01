#include <Box2D/Box2D.h>
#include "TestObject.h"

TestObject::TestObject(b2World *world, sf::Vector2f pos) : m_world(world) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    m_body = m_world->CreateBody(&def);
    m_shape.SetAsBox(100, 100);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &m_shape;
    fixtureDef.density = 1;
    m_body->CreateFixture(&fixtureDef);
    m_body->SetTransform(b2Vec2(pos.x, pos.y), 0);
    m_drawShape.setSize(sf::Vector2f(200, 200));
    m_drawShape.setOrigin(5, 5);
    auto po = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(po.x, po.y));
}

void TestObject::update(float delta) {
    auto pos = m_body->GetTransform().p;
    m_drawShape.setPosition(sf::Vector2f(pos.x, pos.y));
    m_drawShape.setRotation((int)(m_body->GetAngle()*180/M_1_PI) % 360);
}

bool TestObject::onEvent(sf::Event &e) {
    return GameObject::onEvent(e);
}

void TestObject::draw(sf::RenderWindow &window) {
    window.draw(m_drawShape);
}

void TestObject::onResize(sf::Event &resizeEvent) {

}
