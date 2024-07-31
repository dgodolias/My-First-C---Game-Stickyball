#pragma once

#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "trajectoryline.h"
#include "level.h"

namespace gp = graphics;

class Player :public Box {
protected:
	friend class TrajectoryLine;
	Level* current_level;

	float x_axis_mouse_when_dragging_start;
	float y_axis_mouse_when_dragging_start;

	float x_axis_mouse_when_dragging_over;
	float y_axis_mouse_when_dragging_over;

	float theta_angle;
	float m_pos_x_start;
	float m_pos_y_start;
	float velocity;

	float offset_x;
	float offset_y;
	
	bool startscore = false;
public:
	float velocitymultiplier = 0.85f;
	int points=0;
	Player(const std::string& name = "") : Box() { readyToCollide(); }
	float getVelocity() { return velocity; }

	void update(float dt) override;
	void init() override;
	void draw() override;
	void readyToCollide();

	~Player();
};
