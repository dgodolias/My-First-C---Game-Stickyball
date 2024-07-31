#pragma once

#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include <list>
#include <vector>
#include "util.h"
#include "random_XY_axis.h"
#include "gamestate.h"
#include "wall.h"
#include "power.h"
#include "nail.h"
#include "sound.h"


namespace gp = graphics;

class Level : public Box {
public:

	float m_center_x = 5.0f;
	float m_center_y = 5.0f;
	std::string name;
	friend class Player;
	//bool startscore = false;

	std::vector<Sound*> m_sounds;
	std::vector<GameObject*> m_noncollidable_objects;
	std::vector<GameObject*> m_collidable_objects;

	Level(std::string name = "level1") :Box() {}

	void update(float dt) ;
	
	void init() ;
	void draw() ;

	~Level();
};