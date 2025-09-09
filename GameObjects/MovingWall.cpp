#include "MovingWall.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void MovingWall::init() {
    Wall::init();
    velocity = glm::vec3(8.0f, 0, 0);
}

void MovingWall::update(float elapsed) {
    update_position(elapsed);
}

// called by Mode, should be in update function
void MovingWall::update_position(float elapsed) {
    this->transform->position += this->velocity * elapsed;
} 

// on collision
void MovingWall::on_collision(GameObject& other) {
    if (other.tag != "Player") {
        velocity *= -1;
    }
}
