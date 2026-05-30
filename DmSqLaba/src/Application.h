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
	
	Entity chunk;
	Entity sub_chunk;

	//------------------------------------------------------------
		Event_Handler event_handler;
		void init_keys();

		void generate_chunk_by_side(const Sides& side);
		Slot<Sides, Application> generate_chunk_by_side_slot;

		void init_chunk();
		void init_resources();
		void init_interface();
	//------------------------------------------------------------
		std::random_device rd;
		std::mt19937* gen = nullptr;

		float get_random_value(float min, float max);
	//------------------------------------------------------------
		sf::Image chunk_view;
		sf::Image sub_chunk_view;
		
		std::vector<std::vector<float>> current_mesh;
		
		float roughness = 0.8f;

		int current_x = 0;
		int curretn_y = 0;
	//------------------------------------------------------------
		void generate_chunk(const float& A, const float& B, const float& C, const float& D);
		void save_chunk(const int& x, const int& y);
		bool load_chunk(const int& x, const int& y);

public:
	static inline Core the_core;
	static inline Scene app_scene;
	static inline Signal<Sides> generate_signal;

	static inline bool animated_transition = false;
	static inline Sides transition_destination;
	

	//UI events
	static inline bool is_click;
	static inline sf::Mouse::Button click;
	static inline sf::Vector2i click_pos;
	static inline char32_t recent_keyboard_input;

	static inline std::unordered_map<sf::Keyboard::Scancode, bool> key_status;

	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	void run();
};

