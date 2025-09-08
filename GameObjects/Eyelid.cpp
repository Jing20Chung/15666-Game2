#include "Eyelid.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/epsilon.hpp> // For glm::epsilonEqual
#define GLM_ENABLE_EXPERIMENTAL
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <math.h>

Eyelid::Eyelid() {
    start_rot = end_rot = glm::quat(1,1,1,1);
    rot_direction = 1.0f;
    rot_degree = 0.0f;
    blink_speed = .5f;
    t = 0.0f;
}

Eyelid::Eyelid(float rot_degree_) {
    start_rot = end_rot = glm::quat(1,1,1,1);
    rot_direction = 1.0f;
    rot_degree = rot_degree_;
    blink_speed = .5f;
    t = 0.0f;
}

void Eyelid::init() {
    start_rot = transform->rotation;
    end_rot = start_rot * glm::angleAxis(
     glm::radians(rot_degree),
	 glm::vec3(1.0f, 0.0f, 0.0f)
    );
    t = 0.0f;
}

// called by Mode, should be in update function
void Eyelid::update_position(float elapsed) {
} 

// called by Mode, should be in update function
void Eyelid::update_rotation(float elapsed) {
    t += elapsed * rot_direction * blink_speed;
    // Ref: https://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/
    this->transform->rotation = glm::mix(start_rot, end_rot, t);
    
    // Ref: https://docs.gl/sl4/dot
    if (rot_direction == 1 && (glm::abs(glm::dot(this->transform->rotation, end_rot) - 1.0) < C_SLERP_EPSILON)) {
        rot_direction = -1;
    }
    else if (glm::abs(glm::dot(this->transform->rotation, start_rot) - 1.0) < C_SLERP_EPSILON) {
        rot_direction = 1;
    }
}

// on collision
void Eyelid::on_collision(GameObject& other) {
    GameObject::on_collision(other);
}
