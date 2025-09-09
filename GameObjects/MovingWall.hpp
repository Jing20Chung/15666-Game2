#pragma once

#include "Wall.hpp"
#include "../Load.hpp"

struct MovingWall : Wall{
    virtual void init() override; // init funciton
    virtual void update(float elapsed) override; // called by Mode, should be in update function
    virtual void on_collision(GameObject& other) override; // on collision
    
    void update_position(float elapsed); // Should be in update function
};
