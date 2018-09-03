#pragma once
#include "../GameScene.h"

class WormWorld;

class IngameScene : public GameScene {
public:
    explicit IngameScene(GameWindow& parent);
    WormWorld* getWorld() const;
};
