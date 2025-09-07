#include "Cube.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

void Cube::init() {
    velocity = glm::vec3(8.0f, 0, 0);
}

// update any animation
void Cube::update_view(float elapsed) {

} 

// update input from Mode
void Cube::update_input(InputSet set) {

} 

// called by Mode, should be in update function
void Cube::update_position(float elapsed) {
    this->transform->position += this->velocity * elapsed;
    // Bounds bound = this->get_bounds();
    // std::cout << "cube max bound = " << glm::to_string(bound.max) << ", min bounds = " << glm::to_string(bound.min) << std::endl;
} 

// called by Mode, should be in update function
void Cube::update_rotation(float elapsed) {
    return GameObject::update_rotation(elapsed);
} 

// on collision
void Cube::on_collision(GameObject other) {
    GameObject::on_collision(other);
    velocity *= -1;
}
