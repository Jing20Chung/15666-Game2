#include "Monster.hpp"

#include "../Scene.hpp"
#include "../Load.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include "../Ray.hpp"

void Monster::init() {
    isOpened = true;
    isSeePlayer = false;
    current_time = 0;
    opened_duration = 5;
    closed_duration = 3;
    next_eyelid_time = isOpened? opened_duration : closed_duration;
}

 // called by Mode
void Monster::update(float elapsed) {
    // control eyelid
    current_time += elapsed;
    if (current_time >= next_eyelid_time) {
        isOpened = !isOpened;
        next_eyelid_time = isOpened? opened_duration : closed_duration;
        current_time = 0;
        eyelid_u->isOpened = isOpened;
        eyelid_d->isOpened = isOpened;
    }

    if (isOpened) return;

    Ray eye_ray(transform->position, player->transform->position - transform->position);
    glm::vec2 time_hit_player;
    glm::vec2 time_hit_others;

    eye_ray.hit(player->get_bounds(), time_hit_player);
    for (auto obj: gameobjects) {
        eye_ray.hit(obj->get_bounds(), time_hit_others);
    }
    
    if (time_hit_others.x >= time_hit_player.x) {
        // std::cout <<"Monster see player!!!!!!!!!!!!!" << std::endl;
        isSeePlayer = true;
    }
}