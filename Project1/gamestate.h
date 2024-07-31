#pragma once
#include <string>;
#include "sgg/graphics.h"

class GameState {
	std::string m_asset_path = "assets\\";

	float m_canvas_width = 385.f;
	float m_canvas_height = 646.f;
	bool active = 0;

	static GameState* m_unique_instance;
	class Player* m_player = 0;
	class Level* m_current_level = 0;
	class Menu* m_menu = 0;
		
public:
	bool music_on = true;
	float m_global_offset_x = 0.0f;
	float m_global_offset_y = 0.0f;
	bool m_debbuging = false;
	bool start_game = false;
	graphics::Brush br;

	GameState();
	void init();
	void draw();
	void update(float dt);

	static GameState* getInstance();

	void releaseInstance();

	~GameState();

	float getCanvasWidth() { return m_canvas_width; }
	float getCanvasHeight() { return m_canvas_height; }
	bool isActive() { return active; }
	void setActive(bool x) { active = x; }

	Player* getPlayer() { return m_player; }
	Level* getLevel() { return m_current_level; }

	std::string getFullAssetPath(const std::string& asset);
	std::string getAssetDir();
	
};