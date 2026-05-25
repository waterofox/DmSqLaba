#pragma once
#include <foxAndDot-SDK/Core.h>
#include <foxAndDot-SDK/Components/Entity.h>

#include "system/Event_Handler.h"
#include "system/enums.h"

#include "ui/Input_Line.h"

#include <random>
#include <vector>
#include <fstream>

#define CHUNK_SIZE 129

class Application
{
	//components
	Entity chunk;

	Entity interface_back;
	Entity lazy_otline;
	Input_Line A_input;
	Input_Line B_input;
	Input_Line C_input;
	Input_Line D_input;
	Input_Line r_factor_input;

	Label A_B_l;
	Label C_D_l;
	Label r_l;


	Event_Handler event_handler;
	void save_chunk(const int& x, const int& y);
	bool load_chunk(const int& x, const int& y);

	float roughness = 0.6f;
	void generate_chunk(const float& A, const float& B, const float& C, const float& D);
	Sides pre_side = Sides::THIS;

	std::random_device rd;
	std::mt19937* gen = nullptr;

	float get_random_value(float min, float max);	
	sf::Image current_chunk_view;
	std::vector<std::vector<float>> current_mesh;
	
	void init_chunk();
	void init_resources();
	void init_interface();

	int current_x = 0;
	int curretn_y = 0;

	void generate_chunk_by_side(const Sides& side);
	Slot<Sides,Application> generate_chunk_by_side_slot;

public:
	static inline Core the_core;
	static inline Scene app_scene;
	static inline Signal<Sides> generate_signal;
	

	//UI events
	static inline bool is_click;
	static inline bool is_backspace;
	static inline sf::Mouse::Button click;
	static inline sf::Vector2i click_pos;
	static inline char32_t recent_keyboard_input;

	Application();
	
	void run();

	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
};

