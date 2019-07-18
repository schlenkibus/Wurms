#pragma once
#include "GameScene.h"
#include "Tools/QuadTree.h"
#include <SFML/Graphics/RenderWindow.hpp>

class DebugScene : public GameScene {
public:
    DebugScene(GameWindow &parent);
};
