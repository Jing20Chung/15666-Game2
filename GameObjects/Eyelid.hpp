#pragma once

#include "GameObject.hpp"
#include "../Load.hpp"
#include <glm/glm.hpp>

struct Eyelid : GameObject {
    Eyelid();
    Eyelid(float rot_degree_);
    virtual void init() override; // init funciton
    
    virtual void update_position(float elapsed) override; // called by Mode, should be in update function
    virtual void update_rotation(float elapsed) override; // called by Mode, should be in update function

    virtual void on_collision(GameObject& other) override; // on collision

    const float C_SLERP_EPSILON = 0.0001f;
    glm::quat start_rot;
    glm::quat end_rot;
    int rot_direction;
    float rot_degree;
    float blink_speed;
    float t;
};