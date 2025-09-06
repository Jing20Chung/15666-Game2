#pragma once

#include "GameObject.hpp"

struct Cube : GameObject {
    virtual bool bind_transform(Scene::Transform* transform) override; // bind some mesh to this GameObject

    virtual void update_view(float elapsed) override; // update any animation
    virtual void update_input(InputSet set) override; // update input from Mode

    virtual void update_position(float elapsed) override; // called by Mode, should be in update function
    virtual void update_rotation(float elapsed) override; // called by Mode, should be in update function
};