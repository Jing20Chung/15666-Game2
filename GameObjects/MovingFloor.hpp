#pragma once

#include "Floor.hpp"
#include "../Load.hpp"

struct MovingFloor : Floor {
    virtual void init() override; // init funciton
    
    virtual void update_position(float elapsed) override; // called by Mode, should be in update function
    virtual void update_rotation(float elapsed) override; // called by Mode, should be in update function

    virtual void on_collision(GameObject& other) override; // on collision
};