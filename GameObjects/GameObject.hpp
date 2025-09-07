#pragma once

#include "../GL.hpp"
#include "../Scene.hpp"
#include "../Mesh.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string.h>

struct Bounds {
    Bounds(){}
    Bounds(glm::vec3 max_, glm::vec3 min_): max(max_), min(min_){}
    glm::vec3 max;
    glm::vec3 min;
};

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

    glm::vec3 size;

    glm::vec3 position; // current position
    glm::quat rotation; // current rotation
    
    glm::vec3 velocity; // current velocity

    InputSet currentInput; // input of this frame
    
    virtual bool bind_mesh(Load< MeshBuffer > meshbuffer, Scene::Transform* transform, Bounds bounds); // bind transform and bounds according to mesh

    virtual void update_view(float elapsed); // update any animation
    virtual void update_input(InputSet set); // update input from Mode

    virtual void update_position(float elapsed); // called by Mode, should be in update function
    virtual void update_rotation(float elapsed); // called by Mode, should be in update function

    Bounds get_bounds(); // get current bounds

    static bool check_collision(GameObject& obj_a, GameObject& obj_b);
};