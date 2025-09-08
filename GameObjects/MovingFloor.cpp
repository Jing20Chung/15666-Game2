#include "MovingFloor.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void MovingFloor::init() {
    Floor::init();
    velocity = glm::vec3(8.0f, 0, 0);
}

// called by Mode, should be in update function
void MovingFloor::update_position(float elapsed) {
    this->transform->position += this->velocity * elapsed;
} 

// called by Mode, should be in update function
void MovingFloor::update_rotation(float elapsed) {
    return GameObject::update_rotation(elapsed);
} 

// on collision
void MovingFloor::on_collision(GameObject& other) {
    // GameObject::on_collision(other);
    if (other.tag != "Player") {
        velocity *= -1;
    }
}
