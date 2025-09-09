#pragma once

#include "GameObject.hpp"
#include "../Load.hpp"

struct Player : GameObject {
    virtual void init() override; // init funciton
    virtual void update_input(SDL_Event const &evt) override; // update input from Mode
    virtual void update(float elapsed) override; // called by Mode, should be in update function
    virtual void on_collision(GameObject& other) override; // on collision

    struct InputSet {
        bool left, right, up, down, space;
        InputSet() {
            left = right = up = down = space = false;
        }
    } input;

    void update_position(float elapsed); // Should be in update function
    void update_rotation(float elapsed); // Should be in update function

    bool isDead = false;
};