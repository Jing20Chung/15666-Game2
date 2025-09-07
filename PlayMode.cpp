#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>
// from https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <random>
#include <algorithm>

GLuint hexapod_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("hexapod.pnct"));
	hexapod_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > hexapod_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("hexapod.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = hexapod_meshes->lookup(mesh_name);
		if (mesh.count != 0)
			scene.mesh_name_lookup[transform->name] = mesh_name;

		// std::cout << "scene.mesh_name_lookup.size() = " << scene.mesh_name_lookup.size() << std::endl;

		scene.drawables.emplace_back(transform);

		// std::cout << "Mesh name: " << mesh_name << ", mesh max.x = " << mesh.max.x << std::endl;
		// Scene::Transform* current = transform;
		// while (current != nullptr) {
		// 	std::cout << "current transform name: " << current->name << std::endl;
		// 	current = current->parent;
		// }

		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = hexapod_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

PlayMode::PlayMode() : scene(*hexapod_scene) {
	//get pointers to leg for convenience:
	for (auto &transform : scene.transforms) {
		if (transform.name == "Cube") cube_transform = &transform;
		if (transform.name == "Wall_left") wall_l_transform = &transform;
		if (transform.name == "Wall_right") wall_r_transform = &transform;
		// else if (transform.name == "UpperLeg.FL") upper_leg = &transform;
		// else if (transform.name == "LowerLeg.FL") lower_leg = &transform;
	}

	if (cube_transform == nullptr) throw std::runtime_error("Cube not found.");
	if (wall_l_transform == nullptr) throw std::runtime_error("Wall not found.");
	if (wall_r_transform == nullptr) throw std::runtime_error("Wall not found.");
	// if (hip == nullptr) throw std::runtime_error("Hip not found.");
	// if (upper_leg == nullptr) throw std::runtime_error("Upper leg not found.");
	// if (lower_leg == nullptr) throw std::runtime_error("Lower leg not found.");

	// hip_base_rotation = hip->rotation;
	// upper_leg_base_rotation = upper_leg->rotation;
	// lower_leg_base_rotation = lower_leg->rotation;

	// initial bounds for GameObject's size -> collision detect
	std::map< Scene::Transform*, int > transform_level_map;
	int max_level = 0;
	for (auto& transform : scene.transforms) {
		transform_level_map[&transform] = 0;
	}
	for (auto& transform : scene.transforms) {
		int level = 0;
		Scene::Transform* current = &transform;
		while (current != nullptr) {
			max_level = std::max(level, max_level);
			transform_level_map[current] = std::max(transform_level_map[current], level);
			level++;
			current = current->parent;
		}
	}

	// std::cout << "max level is " << max_level << std::endl;

	std::vector< std::vector< Scene::Transform* > > transform_levels(max_level + 1);
	std::map< std::string, Bounds > bounds_map;
	// std::map< std::string, glm::vec3 > bounds_min;
	for (auto& pair : transform_level_map) {
		// std::cout << "pair first = " << pair.first << ", pair second = " << pair.second << std::endl;
		transform_levels[pair.second].push_back(pair.first);
		// Debug
		if (scene.mesh_name_lookup.find(pair.first->name) != scene.mesh_name_lookup.end()) {
			std::cout << "name: " << pair.first->name << ", level: " << pair.second; //<< std::endl;
		 	std::cout<< " Mesh max: " << glm::to_string(hexapod_meshes->lookup(scene.mesh_name_lookup[pair.first->name]).max) << std::endl;
		 	std::cout<< " Mesh min: " << glm::to_string(hexapod_meshes->lookup(scene.mesh_name_lookup[pair.first->name]).min) << std::endl;
		}
		if (scene.mesh_name_lookup.find(pair.first->name) != scene.mesh_name_lookup.end()) {
			bounds_map[pair.first->name].max = hexapod_meshes->lookup(scene.mesh_name_lookup[pair.first->name]).max;
			bounds_map[pair.first->name].min = hexapod_meshes->lookup(scene.mesh_name_lookup[pair.first->name]).min;

			// std::cout << "origin name: " << pair.first->name << ", bounds_max = " << glm::to_string(bounds_map[pair.first->name].max) << ", bounds_min = " << glm::to_string(bounds_map[pair.first->name].min) << std::endl;
		}
	}
	
	// std::cout << "transform level size = " << transform_levels.size() << std::endl;
	// for (int i = 0; i < transform_levels.size(); i++) {
	// 	std::cout << "current level size is " << transform_levels[i].size() << std::endl;
	// }

	// // Start from bottom level (leaf)
	for (auto& level: transform_levels) {
		// process all transforms in this level
		for (auto& transform: level) {
			Scene::Transform* current = transform;
			while (current->parent != nullptr) {
				// std::cout << current->name <<" Update parent: " << current->parent->name << std::endl;
				bounds_map[current->parent->name].max.x = glm::max(bounds_map[current->parent->name].max.x, bounds_map[current->name].max.x);
				bounds_map[current->parent->name].max.y = glm::max(bounds_map[current->parent->name].max.y, bounds_map[current->name].max.y);
				bounds_map[current->parent->name].max.z = glm::max(bounds_map[current->parent->name].max.z, bounds_map[current->name].max.z);

				bounds_map[current->parent->name].min.x = glm::min(bounds_map[current->parent->name].min.x, bounds_map[current->name].min.x);
				bounds_map[current->parent->name].min.y = glm::min(bounds_map[current->parent->name].min.y, bounds_map[current->name].min.y);
				bounds_map[current->parent->name].min.z = glm::min(bounds_map[current->parent->name].min.z, bounds_map[current->name].min.z);

				current = current->parent;
			}
		}
	}

	// for (auto& pair: bounds_map) {
	// 	std::cout << "name: " << pair.first << ", bounds_max = " << glm::to_string(pair.second.max) << ", bounds_min = " << glm::to_string(pair.second.min) << std::endl;
	// }
	gameobjects.emplace_back(&cube);
	gameobjects.emplace_back(&wall_l);
	gameobjects.emplace_back(&wall_r);
	// bind hip to cube
	cube.bind_mesh(hexapod_meshes, cube_transform, bounds_map[cube_transform->name]);
	cube.velocity = glm::vec3(8.0, 0, 0);

	wall_l.bind_mesh(hexapod_meshes, wall_l_transform, bounds_map[wall_l_transform->name]);
	wall_r.bind_mesh(hexapod_meshes, wall_r_transform, bounds_map[wall_r_transform->name]);

	

	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_EVENT_KEY_DOWN) {
		if (evt.key.key == SDLK_ESCAPE) {
			SDL_SetWindowRelativeMouseMode(Mode::window, false);
			return true;
		} else if (evt.key.key == SDLK_A) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_D) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_W) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.key == SDLK_S) {
			down.downs += 1;
			down.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_EVENT_KEY_UP) {
		if (evt.key.key == SDLK_A) {
			left.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_D) {
			right.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_W) {
			up.pressed = false;
			return true;
		} else if (evt.key.key == SDLK_S) {
			down.pressed = false;
			return true;
		}
	} else if (evt.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		if (SDL_GetWindowRelativeMouseMode(Mode::window) == false) {
			SDL_SetWindowRelativeMouseMode(Mode::window, true);
			return true;
		}
	} else if (evt.type == SDL_EVENT_MOUSE_MOTION) {
		if (SDL_GetWindowRelativeMouseMode(Mode::window) == true) {
			glm::vec2 motion = glm::vec2(
				evt.motion.xrel / float(window_size.y),
				-evt.motion.yrel / float(window_size.y)
			);
			camera->transform->rotation = glm::normalize(
				camera->transform->rotation
				* glm::angleAxis(-motion.x * camera->fovy, glm::vec3(0.0f, 1.0f, 0.0f))
				* glm::angleAxis(motion.y * camera->fovy, glm::vec3(1.0f, 0.0f, 0.0f))
			);
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {
	//slowly rotates through [0,1):
	// wobble += elapsed / 10.0f;
	// wobble -= std::floor(wobble);

	// hip->rotation = hip_base_rotation * glm::angleAxis(
	// 	glm::radians(5.0f * std::sin(wobble * 2.0f * float(M_PI))),
	// 	glm::vec3(0.0f, 1.0f, 0.0f)
	// );
	// upper_leg->rotation = upper_leg_base_rotation * glm::angleAxis(
	// 	glm::radians(7.0f * std::sin(wobble * 2.0f * 2.0f * float(M_PI))),
	// 	glm::vec3(0.0f, 0.0f, 1.0f)
	// );
	// lower_leg->rotation = lower_leg_base_rotation * glm::angleAxis(
	// 	glm::radians(10.0f * std::sin(wobble * 3.0f * 2.0f * float(M_PI))),
	// 	glm::vec3(0.0f, 0.0f, 1.0f)
	// );

	// update gameobjects
	for (auto& obj : gameobjects) {
		obj->update_view(elapsed);
		obj->update_rotation(elapsed);
		obj->update_position(elapsed);
	}

	// check collision
	for (int i = 0; i < gameobjects.size(); i++) {
		for (int j = i + 1; j < gameobjects.size(); j++) {
			if (GameObject::check_collision(*gameobjects[i], *gameobjects[j])) {
				gameobjects[i]->on_collision(*gameobjects[j]);
				gameobjects[j]->on_collision(*gameobjects[i]);
			}
		}
	}

	//move camera:
	{
		//combine inputs into a move:
		constexpr float PlayerSpeed = 30.0f;
		glm::vec2 move = glm::vec2(0.0f);
		if (left.pressed && !right.pressed) move.x =-1.0f;
		if (!left.pressed && right.pressed) move.x = 1.0f;
		if (down.pressed && !up.pressed) move.y =-1.0f;
		if (!down.pressed && up.pressed) move.y = 1.0f;

		//make it so that moving diagonally doesn't go faster:
		if (move != glm::vec2(0.0f)) move = glm::normalize(move) * PlayerSpeed * elapsed;

		glm::mat4x3 frame = camera->transform->make_parent_from_local();
		glm::vec3 frame_right = frame[0];
		//glm::vec3 up = frame[1];
		glm::vec3 frame_forward = -frame[2];

		camera->transform->position += move.x * frame_right + move.y * frame_forward;
	}

	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	GL_ERRORS(); //print any errors produced by this setup code

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		constexpr float H = 0.09f;
		lines.draw_text("Mouse motion rotates camera; WASD moves; escape ungrabs mouse",
			glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text("Mouse motion rotates camera; WASD moves; escape ungrabs mouse",
			glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
	}
}
