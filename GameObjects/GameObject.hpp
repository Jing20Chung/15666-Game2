#pragma once

#include "../GL.hpp"
#include "../Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

struct GameObject {
    struct InputSet {
        bool up, down, left, right;

        // default constructor
        InputSet() {
            up = down = left = right = false;
        }

        // construct with values
        InputSet(bool up_, bool down_, bool left_, bool right_): up(up_), down(down_), left(left_), right(right_) {}
    };

    GameObject();
    ~GameObject();

    Scene::Transform* transform; // current binded transform
    glm::vec3 position; // current position
    glm::quat rotation; // current rotation
    InputSet currentInput; // input of this frame
    
    virtual bool bind_transform(Scene::Transform* transform); // bind some mesh to this GameObject

    virtual void update_view(float elapsed); // update any animation
    virtual void update_input(InputSet set); // update input from Mode

    virtual void update_position(float elapsed); // called by Mode, should be in update function
    virtual void update_rotation(float elapsed); // called by Mode, should be in update function
};