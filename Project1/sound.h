#pragma once
#include "gamestate.h"
#include "gameobject.h"


class Sound{
protected:
	std::string asset;
	float volume;
	bool loops;
	int fadetime = -1;
	std::string asset_dir = GameState::getInstance()->getAssetDir();
public:
	void update(float dt);
	void init();
	void draw();

	Sound(std::string asset, float volume, bool loops) :
		asset(asset), volume(volume), loops(loops){

	}

	void SoundOff() {
		asset_dir = "";
	}

	void SoundOn() {
		asset_dir = GameState::getInstance()->getAssetDir();
	}

	std::string getAsset() {
		return asset;
	}

	std::string getAssetDir() {
		return asset_dir;
	}
};
