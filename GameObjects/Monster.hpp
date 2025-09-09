#pragma once

#include "GameObject.hpp"
#include "Eyelid.hpp"
#include "Player.hpp"
#include "../Load.hpp"
#include <vector>

struct Monster : GameObject{
    virtual void init() override;
    virtual void update(float elapsed) override; // called by Mode, should be in update function
	std::vector< GameObject* > gameobjects;
    Player* player;
    Eyelid *eyelid_u, *eyelid_d;
    bool isOpened, isSeePlayer;
    float current_time;
    float opened_duration;
    float closed_duration;
    float next_eyelid_time;
};
