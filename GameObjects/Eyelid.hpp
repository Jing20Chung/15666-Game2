#pragma once

#include "GameObject.hpp"
#include "../Load.hpp"
#include <glm/glm.hpp>

struct Eyelid : GameObject {
    Eyelid();
    Eyelid(float rot_degree_);
    virtual void init() override; // init funciton
    virtual void update(float elapsed) override; // called by Mode
    virtual void on_collision(GameObject& other) override; // on collision

    void update_rotation(float elapsed); // Should be in update function

    const float C_SLERP_EPSILON = 0.0001f;
    glm::quat start_rot;
    glm::quat end_rot;
    bool isOpened;
    int rot_direction;
    float rot_degree;
    float blink_speed;
    float rot_t;
};