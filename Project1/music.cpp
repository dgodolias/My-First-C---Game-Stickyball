#include "music.h"
#include "sgg/graphics.h"
#include "gamestate.h"


Music* Music::getMusic()
{
	if (m_music_instance == nullptr) {
		m_music_instance = new Music("background_music.mp3", 0.1, true);
	}
	return m_music_instance;
}

void Music::update(float dt)
{
	if (GameState::getInstance()->music_on) {
		graphics::playMusic(asset, volume, loops, fadetime);
	}
	else {
		graphics::stopMusic();
	}
}

void Music::init()
{
	if (GameState::getInstance()->music_on) {
		graphics::playMusic(asset, volume, loops, fadetime);
	}
	
}

void Music::draw()
{
}
Music::~Music()
{
	delete m_music_instance;
}
Music* Music::m_music_instance = nullptr;
