#pragma once
#include "sgg/graphics.h"
#include "player.h"
#include "gamestate.h"
#include "gameobject.h"
#include "box.h"
#include "myfunctions.h"

class TrajectoryLine: public GameObject {
	
public:
	float m_pos_x  = -1;
	float m_pos_y  = -1;

	float x_current = -1;
	float y_current = -1;
	float temp_theta = -1;
	float temp_v = -1;
	float temp_vx = -1;
	float temp_vy = -1;
	float (*tempTrajectoryFunction)(const float& theta, const float& v, 
		const float& x_new, const float& x_start, const float& y_start, const float& ya, const float& yb) = nullptr;

	Player* m_player;

	Box circles[10];


public:
	void update(float dt);
	void init();
	void draw();
	void createCircles();

	TrajectoryLine() : circles{ 0.2f, 0.19f, 0.18f,0.17f, .16f,.15f, .14f,.13f,.12f, .11f }
	{
		m_player = GameState::getInstance()->getPlayer();

	}
	TrajectoryLine(float mult) :circles{ mult ,mult - 0.01f ,mult - 0.02f, mult - 0.03f, mult - 0.04f 
		,mult - 0.05f, mult - 0.06f, mult - 0.07f ,mult - 0.08f, mult - 0.09f }
	{
		m_player = GameState::getInstance()->getPlayer();

	}

	~TrajectoryLine();
};