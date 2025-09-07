#include "GameObject.hpp"
#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(){
    this->transform = nullptr;
};
GameObject::~GameObject(){};

// bind transform and bounds according to mesh
bool GameObject::bind_mesh(Load< MeshBuffer > meshbuffer, Scene::Transform* transform, Bounds bounds) {
    assert(transform);
    this->transform = transform;
    this->size.x = bounds.max.x - bounds.min.x;
    this->size.y = bounds.max.y - bounds.min.y;
    this->size.z = bounds.max.z - bounds.min.z;
    std::cout << "name: " << transform->name << ", size = " << glm::to_string(this->size) << ", bounds max = " << glm::to_string(this->get_bounds().max) << ", bounds min = " << glm::to_string(this->get_bounds().min)  << std::endl;
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

// get current bounds
Bounds GameObject::get_bounds() {
    glm::vec3 world_pos = transform->make_world_from_local()[3];
    glm::vec3 bound_max(world_pos.x + size.x/2, world_pos.y + size.y/2, world_pos.z + size.z/2);
    glm::vec3 bound_min(world_pos.x - size.x/2, world_pos.y - size.y/2, world_pos.z - size.z/2);
    return Bounds(bound_max, bound_min);
}
