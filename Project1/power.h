#pragma once
#include "box.h"

class Power : public Box {
	int spawnTime = -1;
	float initial_width = this->getWidth();
	float initial_height = this->getHeight();

	float initial_player_velocity = -1;
	float initial_nails_velocity = -1;
public:
	bool justcollided = false;
	Power() : Box() { }

	void setSpawnTime(int x) {
		spawnTime = x;
	}

	void update(float dt) override;
	void init() override;
	void draw() override;
};