#pragma once

#include <functional>
#include "Label.h"

class GenericReactiveLabel : public Label {
public:
    GenericReactiveLabel(std::function<void(float, Label&)> cb, sf::Vector2f pos);
    void update(float deltaTime) override;
protected:
    std::function<void(float, Label&)> m_cb;
};