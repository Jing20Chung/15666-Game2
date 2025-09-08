#include "Mode.hpp"

#include "Scene.hpp"

#include "GameObjects/GameObject.hpp"
#include "GameObjects/Cube.hpp"
#include "GameObjects/Wall.hpp"
#include "GameObjects/Eyelid.hpp"
#include "GameObjects/Player.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>
#include <list>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
	Scene::Transform *hip = nullptr;
	Scene::Transform *upper_leg = nullptr;
	Scene::Transform *lower_leg = nullptr;
	glm::quat hip_base_rotation;
	glm::quat upper_leg_base_rotation;
	glm::quat lower_leg_base_rotation;
	float wobble = 0.0f;

	// GameObjects
	Scene::Transform *cube_transform = nullptr;
	Scene::Transform *wall_l_transform = nullptr;
	Scene::Transform *wall_r_transform = nullptr;
	Scene::Transform *eyelid_u_transform = nullptr;
	Scene::Transform *eyelid_d_transform = nullptr;
	Scene::Transform *player_transform = nullptr;

	Cube cube;
	Wall wall_l;
	Wall wall_r;
	Eyelid eyelid_u;
	Eyelid eyelid_d;

	Player player;

	std::vector< GameObject* > gameobjects;
	
	//camera:
	Scene::Camera *camera = nullptr;

};
