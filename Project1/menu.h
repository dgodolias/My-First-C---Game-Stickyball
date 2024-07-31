#pragma once
#include "gameobject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "random_XY_axis.h"
#include "sound.h"

class Menu : Box {
	
public:
	std::vector<Sound*> vector_m_sounds;
	static Menu* m_unique_instance;

	Menu();
	void init() override;
	void draw() override;
	void update(float dt) override;

	static Menu* getMenu();

	void releaseInstance();

	~Menu();
};