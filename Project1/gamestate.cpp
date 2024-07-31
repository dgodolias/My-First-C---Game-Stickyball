#include "gamestate.h"
#include "level.h"
#include "player.h"
#include "sgg/graphics.h"
#include "util.h"
#include "menu.h"


GameState::GameState(){}

void GameState::init()
{

	m_current_level = new Level();
	m_current_level->init();

	m_player = new Player("Player");
	m_player->init();

	m_menu = new Menu();
	m_menu->vector_m_sounds = m_current_level->m_sounds;
	m_menu->init();

	graphics::preloadBitmaps(getAssetDir());

	start_game = 0;
	active = 0;
	
	graphics::setFont(GameState::getInstance()->getFullAssetPath("ReallyAwesome.ttf"));
}

void GameState::draw()
{
	m_current_level->draw();
	m_player->draw();
	m_menu->draw();
}

void GameState::update(float dt)
{
	m_menu->update(dt);
	if (isActive()) {
		m_current_level->update(dt);
		m_player->update(dt);
	}

	m_debbuging = graphics::getKeyState(graphics::SCANCODE_0);
}


GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

void GameState::releaseInstance()
{
	if (m_unique_instance != nullptr) {
		delete m_unique_instance;
		m_unique_instance = nullptr;
	}
}

GameState::~GameState()
{
	if (m_player) {
		delete m_player;
	}
	if (m_current_level) {
		delete m_current_level;
	}

}

std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

GameState* GameState::m_unique_instance = nullptr;
