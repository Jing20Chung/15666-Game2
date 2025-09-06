#include "GameObject.hpp"
#include "../Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(){
    this->transform = nullptr;
};
GameObject::~GameObject(){};

bool GameObject::bind_transform(Scene::Transform* transform) {
    this->transform = transform;
    return true;
}
// // update any animation
void GameObject::update_view(float elapsed) { }

// update input from Mode
void GameObject::update_input(InputSet set) {
    currentInput = set;
}

// called by Mode, should be in update function
void GameObject::update_position(float elapsed) { }

// called by Mode, should be in update function 
void GameObject::update_rotation(float elapsed) { }