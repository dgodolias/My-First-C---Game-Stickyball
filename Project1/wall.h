#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include <string>

class Wall :public Box {
	std::string asset;	

public:
	Wall(const std::string& name, const std::string& asset,float x) : asset(asset) {
		m_width = (GameState::getInstance()->getCanvasHeight() + GameState::getInstance()->getCanvasWidth()) * 0.0387f;
		m_height = GameState::getInstance()->getCanvasHeight();
		m_name = name;
		m_pos_y = m_height / 2;
		m_pos_x = x;
	}

	float getWidth() {
		return m_width;
	}

	float getHeight() {
		return m_height;
	}

	void update(float dt) override;
	void init() override;
	void draw() override;
};
