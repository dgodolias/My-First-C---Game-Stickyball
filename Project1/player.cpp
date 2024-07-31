#pragma once
#include "player.h"
#include "sgg/graphics.h"
#include "gamestate.h"
#include "xyaxisplayer.h"
#include <iostream>
#include "level.h"
#include "wall.h"
#include <functional>
#include <vector>
#include "nail.h"
#include "util.h"
#include "music.h"
#include "sound.h"
#include "power.h"

TrajectoryLine trline;

Sound* PcollisionSoundEffect;
Sound* PspikesSoundEffect;

void Player:: readyToCollide() {
	theta_angle = -2;
	velocity = 0;

	x_axis_mouse_when_dragging_start = -1;
	y_axis_mouse_when_dragging_start = -1;

	x_axis_mouse_when_dragging_over = -1;
	y_axis_mouse_when_dragging_over = -1;

	m_pos_x_start = m_pos_x;
	m_pos_y_start = m_pos_y;
}

Player::~Player()
{
	delete current_level;
}


void Player::update(float dt)
{
	/*
	std::cout << "x:" << m_pos_x << std::endl;
	std::cout << "y:" << m_pos_y << std::endl; */

	current_level = GameState::getInstance()->getLevel();

	offset_x = m_pos_x - current_level->getPosx();
	offset_y = m_pos_y - current_level->getPosy();


	gp::MouseState mouse;
	gp::getMouseState(mouse);

	if (mouse.button_left_pressed && theta_angle == -2) {
		
		x_axis_mouse_when_dragging_start = mouse.cur_pos_x;
		y_axis_mouse_when_dragging_start = mouse.cur_pos_y;
		
		trline.setActive(true);
	}

	if (mouse.button_left_released && x_axis_mouse_when_dragging_start != -1) {

		x_axis_mouse_when_dragging_over = mouse.cur_pos_x;
		y_axis_mouse_when_dragging_over = mouse.cur_pos_y;
		
		trline.setActive(false);
	}


	if (x_axis_mouse_when_dragging_start == x_axis_mouse_when_dragging_over &&
		y_axis_mouse_when_dragging_start == y_axis_mouse_when_dragging_over) {
		readyToCollide();
	}
	
	if (x_axis_mouse_when_dragging_start!=-1 && x_axis_mouse_when_dragging_over != -1)
	{
		trline.setActive(false);
		if (theta_angle == -2 && velocity == 0) {
			theta_angle = starting_trajectory_angle
			(x_axis_mouse_when_dragging_start, y_axis_mouse_when_dragging_start,
				x_axis_mouse_when_dragging_over, y_axis_mouse_when_dragging_over);
			velocity = createVelocity(x_axis_mouse_when_dragging_start, y_axis_mouse_when_dragging_start,
				x_axis_mouse_when_dragging_over, y_axis_mouse_when_dragging_over, velocitymultiplier);
			m_pos_x_start = m_pos_x;
			m_pos_y_start = m_pos_y;
			
		}

		std::vector<float> point = *get_X_Y_axis(theta_angle,m_pos_x_start, m_pos_y_start,m_pos_x,m_pos_y,
			x_axis_mouse_when_dragging_start, y_axis_mouse_when_dragging_start,
			x_axis_mouse_when_dragging_over, y_axis_mouse_when_dragging_over, velocity);
		m_pos_x = point[0];
		m_pos_y = point[1];

	}

	trline.update(dt);

	if (m_pos_y - m_height >= GameState::getInstance()->getCanvasHeight()) 
		GameState::getInstance()->init();;

	for (auto p_gob : current_level->m_noncollidable_objects) {
		Box* ob = dynamic_cast<Box*>(p_gob);
		if (this->intersect(*ob) && ob->isActive()) {
			if (dynamic_cast<Power*>(ob) != nullptr) {
				dynamic_cast<Power*>(ob)->justcollided = true;
				dynamic_cast<Power*>(ob)->setActive(false);
			}
		}
	}

	for (auto p_gob : current_level->m_collidable_objects) {
		Box* ob = dynamic_cast<Box*>(p_gob);
		if (!startscore) {
			if (dynamic_cast<Nail*>(ob) != nullptr) {				
				if (ob->getPosy() > this->getPosy()) startscore = true;
			}
		}
		if (ob) {
			if (this->intersect(*ob)) {
				if (dynamic_cast<Wall*>(ob) != nullptr) {
					PcollisionSoundEffect->init();
					GameState::getInstance()->start_game = true;
					if (startscore) {
						points++;
					}
				}

				readyToCollide();
				m_pos_x += this->intersectSideways(*ob);
				if (dynamic_cast<Nail*>(ob) != nullptr) {
					PspikesSoundEffect->init();
					GameState::getInstance()->init();
					break;
				}

			}
		}
	}

	
}

void Player::init()
{	
	for (Sound* sound : GameState::getInstance()->getLevel()->m_sounds) {
		if (sound->getAsset() == "collision_sound.mp3") PcollisionSoundEffect = sound;
		if (sound->getAsset() == "spikes_sound_effect.mp3") PspikesSoundEffect = sound;
	}

	Box::init();
	trline.init();
	startscore = false;

	m_pos_x = GameState::getInstance()->getCanvasWidth() / 2.0f;
	m_pos_y = GameState::getInstance()->getCanvasHeight()*0.8f;

	offset_x = m_pos_x - GameState::getInstance()->getLevel()->getPosx();
	offset_y = m_pos_y - GameState::getInstance()->getLevel()->getPosy();

	m_brush_box.fill_opacity = 1.0f;
	m_brush_box.outline_opacity = 0.0f;
	m_brush_box.texture = GameState::getInstance()->getFullAssetPath("player.png");

	m_brush_box.outline_opacity = 0.0f;
	
}

void Player::draw()
{
	Box::draw();	
	trline.draw();


	gp::drawRect(m_pos_x,m_pos_y,
		m_width * 1.1f, m_height * 1.1f,m_brush_box);

}
