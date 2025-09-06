#include "Cube.hpp"

#include "../Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// bind some mesh to this GameObject
bool Cube::bind_transform(Scene::Transform* transform) {
    return GameObject::bind_transform(transform);
}

// update any animation
void Cube::update_view(float elapsed) {

} 

// update input from Mode
void Cube::update_input(InputSet set) {

} 

// called by Mode, should be in update function
void Cube::update_position(float elapsed) {
    this->transform->position += glm::vec3(.5f, 0.0, 0.0) * elapsed;
} 

// called by Mode, should be in update function
void Cube::update_rotation(float elapsed) {
    return GameObject::update_rotation(elapsed);
} 