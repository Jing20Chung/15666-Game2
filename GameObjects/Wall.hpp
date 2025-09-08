#pragma once

#include "GameObject.hpp"
#include "../Load.hpp"

struct Wall : GameObject{
    virtual void update_position(float elapsed) override; // called by Mode, should be in update function
    virtual void update_rotation(float elapsed) override; // called by Mode, should be in update function
};
