#pragma once
#include "menu.h"
#include "sgg/scancodes.h"
#include "util.h"
#include "sgg/graphics.h"
#include <iostream>
#include "music.h"
#include "sound.h"
#include "gamestate.h"
#include <map>

bool prevKeyStateIsM = 1;
Box pressmtostart(GameState::getInstance()->getCanvasWidth() / 2, GameState::getInstance()->getCanvasHeight() / 4,
	320.f,320.f);

Box ButtonMusic(GameState::getInstance()->getCanvasWidth() / 2, GameState::getInstance()->getCanvasHeight() / 2,
	200.f, 61.4f);
graphics::Brush music_onoff_text;

Box ButtonSoundEffects(GameState::getInstance()->getCanvasWidth() / 2, GameState::getInstance()->getCanvasHeight() / 2 + 80.f,
	200.f, 61.4f);
graphics::Brush soundeffects_onoff_text;

graphics::Brush m_brush_circle[21];

int increaser = -1;
float pressmtostart_size = 1;
float opacity_updator[21];
float sizes[3] = { 15.f, 30.f, 45.f };
float click_pos_x;
float click_pos_y;
std::map<int, std::pair<float, float>> circlePositions;

void initCircles() {
	circlePositions[0] = std::make_pair(63, 412);
	circlePositions[1] = std::make_pair(121, 493);
	circlePositions[2] = std::make_pair(70, 50);
	circlePositions[3] = std::make_pair(99, 512);
	circlePositions[4] = std::make_pair(217, 467);
	circlePositions[5] = std::make_pair(305,455);
	circlePositions[6] = std::make_pair(287, 590);
	circlePositions[7] = std::make_pair(300, 480);
	circlePositions[8] = std::make_pair(170, 270);
	circlePositions[9] = std::make_pair(70, 300);
	circlePositions[11] = std::make_pair(330, 350);
	circlePositions[12] = std::make_pair(300, 260);
	circlePositions[13] = std::make_pair(54, 221);
	circlePositions[14] = std::make_pair(321, 219);
	circlePositions[15] = std::make_pair(50, 610);
	circlePositions[16] = std::make_pair(32, 78);
	circlePositions[17] = std::make_pair(155, 27);
	circlePositions[18] = std::make_pair(210, 102);
	circlePositions[19] = std::make_pair(298, 72);
	circlePositions[20] = std::make_pair(125, 65);

	for (int i = 0; i < 21; i++) {
		opacity_updator[i] = -0.003f;
	}
	pressmtostart_size = 1.f;
}

Menu::Menu() : Box()
{
	this->GameObject::setActive(true);
	m_width = GameState::getInstance()->getCanvasWidth();
	m_height = GameState::getInstance()->getCanvasHeight();
	m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;
	m_pos_y = GameState::getInstance()->getCanvasHeight() /2.0f;

}

void Menu::init()
{
	m_brush_box.fill_opacity = 0.5f;

	initCircles();
	pressmtostart.m_brush_box.texture = GameState::getInstance()->getFullAssetPath("pressmtostart.png");
	pressmtostart.m_brush_box.outline_opacity = 0.0f;

	ButtonMusic.m_brush_box.texture = GameState::getInstance()->getFullAssetPath("button.png");
	ButtonMusic.m_brush_box.outline_opacity = 0.0f;
	ButtonMusic.m_brush_box.fill_opacity = 0.9f;
	music_onoff_text.outline_opacity = 0.0f;
	music_onoff_text.fill_opacity = 1.0f;

	ButtonSoundEffects.m_brush_box.texture = GameState::getInstance()->getFullAssetPath("button.png");
	ButtonSoundEffects.m_brush_box.outline_opacity = 0.0f;
	ButtonSoundEffects.m_brush_box.fill_opacity = 0.9f;
	soundeffects_onoff_text.outline_opacity = 0.0f;
	soundeffects_onoff_text.fill_opacity = 1.0f;
	
	for (int i = 0; i < 21; i++) {
		m_brush_circle[i].fill_opacity = i/21.f;
		m_brush_circle[i].outline_opacity = 0.0f;
		SETCOLOR(m_brush_circle[i].fill_color, generateRandomNumber(0.0f,1.0f), 
			generateRandomNumber(0.0f, 1.0f), generateRandomNumber(0.0f, 1.0f));
		m_brush_circle[i].texture = GameState::getInstance()->getFullAssetPath("white_circle.png");
	}

	SETCOLOR(music_onoff_text.fill_color, 1.0f, 1.0f, 1.0f);
	
}

void Menu::draw()
{
	//std::cout << "ACTIVE:"<<this->GameObject::isActive()<<std::endl;
	if (this->GameObject::isActive()) {
		//whole menu
		m_brush_box.fill_opacity = 0.5f;
		graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, m_brush_box);
		//

		//pressmtostart label
		graphics::drawRect(pressmtostart.getPosx(), pressmtostart.getPosy(),
			pressmtostart.getWidth() * pressmtostart_size, pressmtostart.getHeight() * pressmtostart_size, pressmtostart.m_brush_box);
		//

		//music button
		graphics::drawRect(ButtonMusic.getPosx(), ButtonMusic.getPosy(),
			ButtonMusic.getWidth(), ButtonMusic.getHeight(), ButtonMusic.m_brush_box);

		graphics::drawText(140.0f, 327.5f, 22.0f, "Music On/Off", music_onoff_text);
		//

		//sound effects button
		graphics::drawRect(ButtonSoundEffects.getPosx(), ButtonSoundEffects.getPosy(),
			ButtonSoundEffects.getWidth(), ButtonSoundEffects.getHeight(), ButtonSoundEffects.m_brush_box);

		graphics::drawText(105.0f, 407.5f, 22.0f, "Sound Effects On/Off", soundeffects_onoff_text);
		//


		int i = 0;
		for (const auto& entry : circlePositions) {
			
			graphics::drawRect(entry.second.first, entry.second.second,sizes[i % 4], sizes[i % 4],m_brush_circle[i]);
			i++;
		}
	}
}

void Menu::update(float dt)
{
	if ((graphics::getKeyState(graphics::SCANCODE_M) && !prevKeyStateIsM)) {
		prevKeyStateIsM = 1;
		//std::cout << "CODE:" << graphics::getKeyState(graphics::SCANCODE_M) << std::endl;
		this->GameObject::setActive(!this->GameObject::isActive());

		GameState::getInstance()->setActive(!GameState::getInstance()->isActive());
	}
	if (!graphics::getKeyState(graphics::SCANCODE_M) && prevKeyStateIsM) prevKeyStateIsM = 0;

	graphics::MouseState mouse;
	graphics::getMouseState(mouse);

	if (mouse.button_left_pressed && this->GameObject::isActive()) {

		click_pos_x = mouse.cur_pos_x;
		click_pos_y = mouse.cur_pos_y;
		if (click_pos_y >= ButtonMusic.getPosy()-30.0f && click_pos_y <= ButtonMusic.getPosy()+30.0f &&
			click_pos_x<=ButtonMusic.getPosx()+85.0f && click_pos_x >= ButtonMusic.getPosx() - 85.0f) {

			GameState::getInstance()->music_on = !GameState::getInstance()->music_on;
			if (GameState::getInstance()->music_on == 0) {
				graphics::stopMusic();
			}
			else {
				Music::getMusic()->init();
			}
		}

		if (click_pos_y >= ButtonSoundEffects.getPosy() - 30.0f && click_pos_y <= ButtonSoundEffects.getPosy() + 30.0f &&
			click_pos_x <= ButtonSoundEffects.getPosx() + 85.0f && click_pos_x >= ButtonMusic.getPosx() - 85.0f) {

			for (Sound* sound : vector_m_sounds) {
				if (sound->getAssetDir() == "") { sound->SoundOn(); }
				else {sound->SoundOff();}
			}
		}
	}
	for (int i = 0; i < 21; i++) {
		if (m_brush_circle[i].fill_opacity < 0 || m_brush_circle[i].fill_opacity > 1) opacity_updator[i] *= -1;
		if (m_brush_circle[i].fill_opacity < 0) SETCOLOR(m_brush_circle[i].fill_color, generateRandomNumber(0.0f, 1.0f),
			generateRandomNumber(0.0f, 1.0f), generateRandomNumber(0.0f, 1.0f));
		m_brush_circle[i].fill_opacity += opacity_updator[i];
	}

	if (pressmtostart_size <= 0.8f) {
		increaser = 1;
	}
	else if (pressmtostart_size >= 1.0) {
		increaser = -1;
	}
	pressmtostart_size += increaser * 0.0015f;

}

Menu* Menu::getMenu()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new Menu();
	}
	return m_unique_instance;
}

void Menu::releaseInstance()
{
	if (m_unique_instance != nullptr) {
		delete m_unique_instance;
		m_unique_instance = nullptr;
	}
}

Menu::~Menu()
{
	Menu::releaseInstance();
}

Menu* Menu::m_unique_instance = nullptr;
