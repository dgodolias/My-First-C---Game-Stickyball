#pragma once
#include "gameobject.h"
#include "gamestate.h"

class Music : public GameObject {
protected:
	std::string asset;
	float volume;
	bool loops;
	int fadetime;
	friend class Level;
public:
	static Music* m_music_instance;
	static Music* getMusic();
	void update(float dt);
	void init();
	void draw();

	Music(std::string file, float volume, bool loops, int fadetime = 0) : GameObject(),
		asset(GameState::getInstance()->getFullAssetPath(file)), volume(volume), loops(loops), fadetime(fadetime) {
		this->setActive(true);
	}

	~Music();
};